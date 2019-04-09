/*
** EPITECH PROJECT, 2018
** ARCADE
** File description:
**	Core header
*/

#ifndef CORE_HPP_
	#define CORE_HPP_

	#include <iostream>
	#include <vector>

	#include "./BoxData.hpp"
	#include "../interface/IGraphic.hpp"
	#include "../interface/IGame.hpp"

	/*
	** Constantes to define paths to libraries directories.
	*/
	static const std::string	graphsLibDir = "./lib/";
	static const std::string	gamesLibDir = "./games/";

	/*
	** Constantes to define a reference list of libraries to be found in directories.
	*/
	static const std::vector<std::string>	libGraphsNames = {
		"lib_arcade_sfml.so", "lib_arcade_ncurses.so", "lib_arcade_sdl.so"
	};
	static const std::vector<std::string>	libGamesNames = {
		"lib_arcade_nibbler.so", "lib_arcade_pacman.so"
	};

	/*
	** Shorter types definitions (easier to handle).
	*/
	using GraphsLibsOpen = std::vector<void *>;
	using GamesLibsOpen = std::vector<void *>;
	using GraphsLibsInstances = std::vector<IGraphic *>;
	using GamesLibsInstances = std::vector<IGame *>;

	/*
	** Class Core.
	*/
	class				Core
	{
	public:
		Core(const char *libPath);
		~Core();
		int			InitCore();
		int			InitBoxData(void);
		nameTab			LoadGraphsLibsNames(void);
		nameTab			LoadGamesLibsNames(void);
		GraphsLibsOpen		OpenGraphslibraries(void);
		GamesLibsOpen		OpenGameslibraries(void);
		int			LoadGraphsInstances();
		int			LoadGamesInstances();
		IGraphic		*CreateGraphsLibInstance(void *handle, std::string symbol);
		IGame			*CreateGamesLibInstance(void *handle, std::string symbol);
		int			DeleteGraphsInstances();
		int			DeleteGamesInstances();
		int			DestroyGraphsLibInstance(void *handle, std::string symbol, IGraphic *InstanceToDestroy);
		int			DestroyGamesLibInstance(void *handle, std::string symbol, IGame *InstanceToDestroy);
		int			CloseGraphslibraries(void);
		int			CloseGameslibraries(void);
		void			LoadAllSprites();
		//launcher
		int			RunArcade();
		bool			RequestExit();
		void			changeLibIt(int key);
		void			changeGameIt(int key);
		void			changeMenuIT();
		void			menu();
		void			shortcut();
	private:
		std::string		_pathToDefaultGraphsLib;
		BoxData_t		_boxData;
		ent_list		_entity;
		GraphsLibsOpen		_graphsLibraries;
		GamesLibsOpen		_gamesLibraries;
		GraphsLibsInstances	_graphsInstances;
		GamesLibsInstances	_gamesInstances;
		int			_exitStatus;
		bool			_isRunning;
		Keys_inp_t		_key;
		int			_menuIt;
		int			_menuMode;
		bool			_canExit;
	};

#endif /* !CORE_HPP_ */
