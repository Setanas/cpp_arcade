/*
** EPITECH PROJECT, 2018
** ARCADE
** File description:
**	Core implementation
*/

#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include <algorithm>
#include <unistd.h>
#include "../../inc/Keys.hpp"
#include "../../inc/Core.hpp"

/*
** Ctor
*/
Core::Core(const char *libPath) : _pathToDefaultGraphsLib(libPath), _exitStatus(0), _isRunning(true), _key({false, 0, false}), _menuIt(0), _menuMode('m'), _canExit(false)
{
	std::cout << "Entering Core CTOR..." << std::endl;
	//
	std::cout << "=>Core created !" << std::endl;
}

/*
** Dtor
*/
Core::~Core()
{
	std::cout << "Entering Core DTOR..." << std::endl;
	//
	std::cout << "=>Core deleted !" << std::endl;
}

/*
** Init Core.
*/
int	Core::InitCore()
{
	if (InitBoxData() != 0) {
		std::cerr << "! : An error occurs when initializing BoxData structure" << std::endl;
		return 84;
	}
	_graphsLibraries = OpenGraphslibraries();
	if (this->_exitStatus != 0) {
		return 84;
	}
	_gamesLibraries = OpenGameslibraries();
	if (this->_exitStatus != 0) {
		return 84;
	}
	if (LoadGraphsInstances() != 0) {
		return 84;
	}
	if (LoadGamesInstances() != 0) {
		return 84;
	}
	LoadAllSprites();
	return 0;
}

void					Core::LoadAllSprites()
{
	unsigned int			i = 0, k = 0;
	std::vector<std::string>	sprite;

	while (i < _gamesInstances.size()) {
		_gamesInstances[i]->initEntity();
		sprite = _gamesInstances[i]->getSprites();
		while (k < _graphsInstances.size()) {
			_graphsInstances[k]->loadSprites(sprite);
			k = k + 1;
		}
		k = 0;
		i = i + 1;
	}
}

/*
** Init BoxData
*/
int	Core::InitBoxData(void)
{
	std::cout << "Initializing BoxData structure..." << std::endl;
	this->_boxData.graphsLibNames = LoadGraphsLibsNames();
	if (this->_exitStatus != 0) {
		std::cerr << "! : An error occurs when loading graphics libraries names" << std::endl;
		return 1;
	}
	if (_pathToDefaultGraphsLib.find("ncurses") != std::string::npos) {
		this->_boxData.graphsLibIt = 0;
	} else if (_pathToDefaultGraphsLib.find("sdl") != std::string::npos) {
		this->_boxData.graphsLibIt = 1;
	} else {
		this->_boxData.graphsLibIt = 2;
	}
	this->_boxData.gamesLibNames = LoadGamesLibsNames();
	if (this->_exitStatus != 0) {
		std::cerr << "! : An error occurs when loading games libraries names" << std::endl;
		return 1;
	}
	this->_boxData.gamesLibIt = 0;
	this->_boxData.username = "";
	this->_boxData.score = 0;
	std::cout << "=>BoxData structure initialiazed !" << std::endl;
	return 0;
}

/*
** Loads avalaible graphics libs names in the dedicated vector.
*/
nameTab			Core::LoadGraphsLibsNames(void)
{
	std::cout << "Getting libraries names..." << std::endl;
	nameTab		libsNames;
	DIR		*dirp = opendir(graphsLibDir.c_str());
	struct dirent	*dp = nullptr;

	if (!dirp) {
		std::cerr << "! : opendir() failure on directory : " << graphsLibDir << std::endl;
		this->_exitStatus = 1;
		return libsNames;
	}
	dp = readdir(dirp);
	if (!dp) {
		std::cerr << "! : readdir() failure on directory : " << graphsLibDir << std::endl;
		this->_exitStatus = 1;
		closedir(dirp);
		return libsNames;
	}
	while (dp) {
		if (std::find(libGraphsNames.begin(), libGraphsNames.end(), dp->d_name) != libGraphsNames.end()) {
			libsNames.push_back(dp->d_name);
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	std::cout << "=>Libraries names found !" << std::endl;
	this->_exitStatus = 0;
	return libsNames;
}

/*
** Loads avalaible games libs names in the dedicated vector.
*/
nameTab			Core::LoadGamesLibsNames(void)
{
	std::cout << "Getting libraries names..." << std::endl;
	nameTab		libsNames;
	DIR		*dirp = opendir(gamesLibDir.c_str());
	struct dirent	*dp = nullptr;

	if (!dirp) {
		std::cerr << "! : opendir() failure on directory : " << gamesLibDir << std::endl;
		this->_exitStatus = 1;
		return libsNames;
	}
	dp = readdir(dirp);
	if (!dp) {
		std::cerr << "! : readdir() failure on directory : " << gamesLibDir << std::endl;
		this->_exitStatus = 1;
		closedir(dirp);
		return libsNames;
	}
	while (dp) {
		if (std::find(libGamesNames.begin(), libGamesNames.end(), dp->d_name) != libGamesNames.end()) {
			libsNames.push_back(dp->d_name);
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	std::cout << "=>Libraries names found !" << std::endl;
	this->_exitStatus = 0;
	return libsNames;
}

/*
** Open graphics libraries in dedicated vector.
*/
GraphsLibsOpen		Core::OpenGraphslibraries(void)
{
	std::cout << "Loading graphics libraries..." << std::endl;
	GraphsLibsOpen	libraries;
	DIR		*dirp = opendir(graphsLibDir.c_str());
	struct dirent	*dp = nullptr;
	void		*handle = nullptr;
	std::string	libraryPath;

	if (!dirp) {
		std::cerr << "! : opendir() failure on directory : " << graphsLibDir << std::endl;
		this->_exitStatus = 1;
		return libraries;
	}
	dp = readdir(dirp);
	if (!dp) {
		std::cerr << "! : readdir() failure on directory : " << graphsLibDir << std::endl;
		this->_exitStatus = 1;
		closedir(dirp);
		return libraries;
	}
	while (dp) {
		if (std::find(libGraphsNames.begin(), libGraphsNames.end(), dp->d_name) != libGraphsNames.end()) {
			std::cout << "Trying to load a lib named : " << dp->d_name << std::endl;
			libraryPath = graphsLibDir + (std::string)dp->d_name;
			handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
			if (handle == nullptr) {
				std::cerr << dlerror() << std::endl;
				this->_exitStatus = 1;
				closedir(dirp);
				return libraries;
			}
			dlerror();
			libraries.push_back(handle);
			std::cout << "=>The lib : " << dp->d_name << " is loaded !" << std::endl;
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	std::cout << "=>Libraries loaded !" << std::endl;
	this->_exitStatus = 0;
	return libraries;
}

/*
** Open games libraries in dedicated vector.
*/
GamesLibsOpen		Core::OpenGameslibraries(void)
{
	std::cout << "Loading games libraries..." << std::endl;
	GraphsLibsOpen	libraries;
	DIR		*dirp = opendir(gamesLibDir.c_str());
	struct dirent	*dp = nullptr;
	void		*handle = nullptr;
	std::string	libraryPath;

	if (!dirp) {
		std::cerr << "! : opendir() failure on directory : " << gamesLibDir << std::endl;
		this->_exitStatus = 1;
		return libraries;
	}
	dp = readdir(dirp);
	if (!dp) {
		std::cerr << "! : readdir() failure on directory : " << gamesLibDir << std::endl;
		this->_exitStatus = 1;
		closedir(dirp);
		return libraries;
	}
	while (dp) {
		if (std::find(libGamesNames.begin(), libGamesNames.end(), dp->d_name) != libGamesNames.end()) {
			std::cout << "Trying to load a lib named : " << dp->d_name << std::endl;
			libraryPath = gamesLibDir + (std::string)dp->d_name;
			handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
			if (handle == nullptr) {
				std::cerr << dlerror() << std::endl;
				this->_exitStatus = 1;
				closedir(dirp);
				return libraries;
			}
			dlerror();
			libraries.push_back(handle);
			std::cout << "=>The lib : " << dp->d_name << " is loaded !" << std::endl;
		}
		dp = readdir(dirp);
	}
	closedir(dirp);
	std::cout << "=>Libraries loaded !" << std::endl;
	this->_exitStatus = 0;
	return libraries;
}

int			Core::LoadGraphsInstances()
{
	IGraphic	*NcursesInstance = nullptr;
	IGraphic	*SdlInstance = nullptr;
	IGraphic	*SfmlInstance = nullptr;

	NcursesInstance = CreateGraphsLibInstance(_graphsLibraries[0], "create");
	if (!NcursesInstance) {
		std::cerr << "! : unable to load ncurses instance" << std::endl;
		return 84;
	}
	SdlInstance = CreateGraphsLibInstance(_graphsLibraries[1], "create");
	if (!SdlInstance) {
		std::cerr << "! : unable to load sdl instance" << std::endl;
		return 84;
	}
	SfmlInstance = CreateGraphsLibInstance(_graphsLibraries[2], "create");
	if (!SfmlInstance) {
		std::cerr << "! : unable to load sfml instance" << std::endl;
		return 84;
	}
	this->_graphsInstances.push_back(NcursesInstance);
	this->_graphsInstances.push_back(SdlInstance);
	this->_graphsInstances.push_back(SfmlInstance);
	return 0;
}

int		Core::LoadGamesInstances()
{
	IGame	*NibblerInstance = nullptr;
	IGame	*PacmanInstance = nullptr;

	NibblerInstance = CreateGamesLibInstance(_gamesLibraries[0], "create");
	if (!NibblerInstance) {
		std::cerr << "! : unable to load nibbler instance" << std::endl;
		return 84;
	}
	PacmanInstance = CreateGamesLibInstance(_gamesLibraries[1], "create");
	if (!PacmanInstance) {
		std::cerr << "! : unable to load pacman instance" << std::endl;
		return 84;
	}
	this->_gamesInstances.push_back(NibblerInstance);
	this->_gamesInstances.push_back(PacmanInstance);
	return 0;
}

int	Core::DeleteGraphsInstances()
{
	std::cout << "Deleting graphs instances..." << std::endl;
	if (DestroyGraphsLibInstance(_graphsLibraries[0], "destroy", _graphsInstances[0]) != 0) {
		std::cerr << "! : unable to destroy ncurses instance" << std::endl;
		return 84;
	}
	if (DestroyGraphsLibInstance(_graphsLibraries[1], "destroy", _graphsInstances[1]) != 0) {
		std::cerr << "! : unable to destroy sdl instance" << std::endl;
		return 84;
	}
	if (DestroyGraphsLibInstance(_graphsLibraries[2], "destroy", _graphsInstances[2]) != 0) {
		std::cerr << "! : unable to destroy sfml instance" << std::endl;
		return 84;
	}
	std::cout << "=>Graphs instances deleted !" << std::endl;
	return 0;
}

int	Core::DeleteGamesInstances()
{
	std::cout << "Deleting games instances..." << std::endl;
	if (DestroyGamesLibInstance(_gamesLibraries[0], "destroy", _gamesInstances[0]) != 0) {
		std::cerr << "! : unable to destroy nibbler instance" << std::endl;
		return 84;
	}
	if (DestroyGamesLibInstance(_gamesLibraries[1], "destroy", _gamesInstances[1]) != 0) {
		std::cerr << "! : unable to destroy pacman instance" << std::endl;
		return 84;
	}
	std::cout << "Games instances deleted" << std::endl;
	return 0;
}


IGraphic			*Core::CreateGraphsLibInstance(void *handle, std::string symbol)
{
	std::cout << "Creating instance graphs" << std::endl;
	IGraphic		*instance = nullptr;
	graphsLibCreate_t	*graphsLibCtor = nullptr;
	const char		*dlsymError = NULL;

	graphsLibCtor = (graphsLibCreate_t *)dlsym(handle, symbol.c_str());
	dlsymError = dlerror();
	if (dlsymError) {
		std::cerr << dlsymError << std::endl;
		return nullptr;
	}
	instance = graphsLibCtor();
	std::cout << "=>Instance created !" << std::endl;
	return instance;
}

IGame				*Core::CreateGamesLibInstance(void *handle, std::string symbol)
{
	std::cout << "Creating instance games" << std::endl;
	IGame			*instance = nullptr;
	gamesLibCreate_t	*gamesLibCtor = nullptr;
	const char		*dlsymError = NULL;

	gamesLibCtor = (gamesLibCreate_t *)dlsym(handle, symbol.c_str());
	dlsymError = dlerror();
	if (dlsymError) {
		std::cerr << dlsymError << std::endl;
		return nullptr;
	}
	instance = gamesLibCtor();
	std::cout << "=>Instance created !" << std::endl;
	return instance;
}

int				Core::DestroyGraphsLibInstance(void *handle, std::string symbol, IGraphic *InstanceToDestroy)
{
	std::cout << "Destroying instance graphs" << std::endl;
	graphsLibDestroy_t	*graphsLibDtor = nullptr;
	const char		*dlsymError = NULL;

	graphsLibDtor = (graphsLibDestroy_t *)dlsym(handle, symbol.c_str());
	dlsymError = dlerror();
	if (dlsymError) {
		std::cerr << dlsymError << std::endl;
		return 84;
	}
	graphsLibDtor(InstanceToDestroy);
	std::cout << "=>Instance deleted !" << std::endl;
	return 0;
}

int				Core::DestroyGamesLibInstance(void *handle, std::string symbol, IGame *InstanceToDestroy)
{
	std::cout << "Destroying instance for games" << std::endl;
	gamesLibDestroy_t	*gamesLibDtor = nullptr;
	const char		*dlsymError = NULL;

	gamesLibDtor = (gamesLibDestroy_t *)dlsym(handle, symbol.c_str());
	dlsymError = dlerror();
	if (dlsymError) {
		std::cerr << dlsymError << std::endl;
		return 84;
	}
	gamesLibDtor(InstanceToDestroy);
	std::cout << "=>Instance deleted !" << std::endl;
	return 0;
}

int			Core::CloseGraphslibraries()
{
	unsigned int	it = 0;

	std::cout << "Closing graphics libraries..." << std::endl;
	if (DeleteGraphsInstances() != 0) {
		return 1;
	}
	for (it = 0; it != (_graphsLibraries.size() - 1); it++) {
		if (dlclose(_graphsLibraries[it]) != 0) {
			std::cerr << dlerror() << std::endl;
			return 1;
		}
	}
	dlerror();
	std::cout << "=>Libraries deleted !" << std::endl;
	return 0;
}

int			Core::CloseGameslibraries()
{
	unsigned int	it = 0;

	std::cout << "Closing games libraries..." << std::endl;
	if (DeleteGamesInstances() != 0) {
		return 1;
	}
	for (it = 0; it != _gamesLibraries.size(); ++it) {
		if (dlclose(_gamesLibraries[it]) != 0) {
			std::cerr << dlerror() << std::endl;
			return 1;
		}
	}
	dlerror();
	std::cout << "=>Libraries deleted !" << std::endl;
	return 0;
}

/*
** launcher
*/
int	Core::RunArcade()
{
	map_str		map;

	_exitStatus = 0;
	if (this->InitCore() != 0) {
		_exitStatus = 84;
	} else {
		_graphsInstances[_boxData.graphsLibIt]->switchOn();
		while (_key.value != 10 && _key.value != -1) {
			_graphsInstances[_boxData.graphsLibIt]->displayBox(_boxData);
			_key = _graphsInstances[_boxData.graphsLibIt]->getKey(false);
			if (_key.value > -1 && _key.value != 10 && _key.valid == true) {
				_boxData.username += _key.value;
			}

		}
		_menuMode = 'm';
		_key.value = 0;
		while ((_key.value != 27 && !_gamesInstances[_boxData.gamesLibIt]->endOfGame()) && !_canExit) {
			if (_menuMode == 'm') {
					_graphsInstances[_boxData.graphsLibIt]->displayMenu(_boxData, _menuIt);
				changeMenuIT();
			} else if ((_menuMode == 'g' || _menuMode == 'p') && !_canExit) {
				_graphsInstances[_boxData.graphsLibIt]->displayGame(_entity, map, 1);
				if (_menuMode == 'g') {
					map = _gamesInstances[_boxData.gamesLibIt]->getMap();
					_gamesInstances[_boxData.gamesLibIt]->action(_key);
					_entity = _gamesInstances[_boxData.gamesLibIt]->getEntity();
				} else {
					_graphsInstances[_boxData.graphsLibIt]->displayPause();
				}
			}
			_graphsInstances[_boxData.graphsLibIt]->displayBox(_boxData);
			_key = _graphsInstances[_boxData.graphsLibIt]->getKey(true);
			shortcut();
		}

	}
	_graphsInstances[_boxData.graphsLibIt]->switchOff();
	if (CloseGraphslibraries() != 0) {
		_exitStatus = 84;
	}
	if (CloseGameslibraries() != 0) {
		_exitStatus = 84;
	}
	return _exitStatus;
}

void	Core::changeLibIt(int _key)
{
	if (_key == 4 && (size_t)_boxData.graphsLibIt < _boxData.graphsLibNames.size() - 1) {
		_graphsInstances[_boxData.graphsLibIt]->switchOff();
		_boxData.graphsLibIt++;
		usleep(100000);
		_graphsInstances[_boxData.graphsLibIt]->switchOn();
	}
	if (_key == 3 && _boxData.graphsLibIt > 0) {
		_graphsInstances[_boxData.graphsLibIt]->switchOff();
		_boxData.graphsLibIt--;
		usleep(10000);
		_graphsInstances[_boxData.graphsLibIt]->switchOn();
	}
}

void	Core::changeGameIt(int _key)
{
	if (_key == 4 && (size_t)_boxData.gamesLibIt < _boxData.gamesLibNames.size() - 1)
		_boxData.gamesLibIt++;
	if (_key == 3 && _boxData.gamesLibIt > 0)
		_boxData.gamesLibIt--;
}

void	Core::changeMenuIT()
{
	if (_key.value == 4 && _menuIt < 5)
	{
		_menuIt++;
	}
	if (_key.value == 3 && _menuIt > 0)
	{
		_menuIt--;
	}
	if (_key.value == 10 && _menuIt == 0)
		_menuMode = 'g';
	if (_key.value == 10 && _menuIt == 1)
		changeLibIt(3);
	if (_key.value == 10 && _menuIt == 2)
		changeLibIt(4);
	if (_key.value == 10 && _menuIt == 3)
		changeGameIt(3);
	if (_key.value == 10 && _menuIt == 4)
		changeGameIt(4);
	if (_key.value == 10 && _menuIt == 5 && _key.value != 'g') {
		_canExit = true;
	}
}

void	Core::shortcut()
{
	switch(_key.value) {
		case 27 :
			_canExit = true;
			break;
		case 'b' :
			changeLibIt(3);
			break;
		case 'n' :
			changeLibIt(4);
			break;
		case 'g' :
			changeGameIt(3);
			break;
		case 'h' :
			changeGameIt(4);
			break;
		case 'r' :
			_gamesInstances[_boxData.gamesLibIt]->initEntity();
			break;
		case 'm' :
			if (_menuMode == 'g') {
				_menuMode = 'm';
				_canExit = false;
				_key.value = 0;
			} else {
				_menuMode = 'm';
			}
			break;
		case 'p' :
			if (_menuMode == 'g') {
				_menuMode = 'p';
			} else {
				_menuMode = 'g';
			}
		default :
			break;
	}
}

/*
** Determines if program should exit.
*/
bool	Core::RequestExit()
{
	return true;
}
