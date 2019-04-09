//
// EPITECH PROJECT, 2018
// graphic
// File description:
// graphic
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <unistd.h>
#include <ncurses.h>

#include "Ncurses.hpp"
#include "Entity.hpp"
#include "Keys.hpp"
#include "BoxData.hpp"

Ncurses::Ncurses()
{
}

Ncurses::~Ncurses()
{
}

const std::string	Ncurses::getName() const
{
	std::string	userName;

	userName += "Name";
	return userName;
}

int	Ncurses::switchKey(int ch)
{
	switch(ch) {
		case KEY_LEFT :
			ch = 1;
			break;
		case KEY_RIGHT :
			ch = 2;
			break;
		case KEY_UP :
			ch = 3;
			break;
		case KEY_DOWN :
			ch = 4;
			break;
		default :
			break;
	}
	return ch;
}

Keys_inp_t		Ncurses::getKey(bool all)
{
	int		ch = 0;
	Keys_inp_t	key= {false, -2, false};

	ch = 0;
	ch = getch();
	if (all && ch > -1){
		ch = switchKey(ch);
		key.valid = true;
		key.value = ch;
		key.shift = false;
	} else if (!all && ch > -1 &&
		((ch >= '0' && ch <= '9') ||(ch >= 'a' && ch <= 'z') ||
		(ch >= 'A' && ch <= 'Z') || ch == 10)) {
		key.valid = true;
		key.value = ch;
		key.shift = false;
	}
	return key;
}

int	Ncurses::switchOn()
{
	static bool firstTime = true;

	if (firstTime) {
		initscr();
		switchOff();
		firstTime = false;
	}
	initscr();
	nodelay(stdscr, true);
	start_color();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	return 0;
}

void	Ncurses::switchOff()
{
	endwin();
}

void	Ncurses::displayPause()
{
	clear();
	mvprintw(30, 90, "PAUSE !");
}

void	Ncurses::printBox(int x, int y, int nbrX, int nbrY)
{
	mvprintw(x, y, "+---------------------------------------+");
	mvprintw(x + 9, y, "+---------------------------------------+");
	for (int i = x + 1; i < x + 9; ++i) {
		mvprintw(i, nbrX, "|");
		mvprintw(i, nbrY, "|");
	}
}

void				Ncurses::printData(BoxData_t &data)
{
	int			graphLenth = data.graphsLibNames.size();
	int			gamesLenth = data.gamesLibNames.size();
	std::stringstream	ss;

	ss << data.score;
	mvprintw(16, 19, "Lib :");
	for(int i = 0; i < graphLenth; i++) {
		mvprintw(i + 18, 19, "%s", data.graphsLibNames[i].c_str());
		mvprintw(i + 18, 16, "  ");
	}
	mvprintw(36, 19, "Games :");
	for(int i = 0; i < gamesLenth; i++) {
		mvprintw(i + 38, 19, "%s", data.gamesLibNames[i].c_str());
		mvprintw(i + 38, 16, "  ");
	}
	if (data.graphsLibIt >= 0 && data.graphsLibIt < graphLenth)
		mvprintw(18 + data.graphsLibIt, 16, "->");
	if (data.graphsLibIt >= 0 && data.graphsLibIt < gamesLenth)
		mvprintw(38 + data.gamesLibIt, 16, "->");
	mvprintw(20, 160, "score : %s", ss.str().c_str());
	displayUsername(data.username);
}

void	Ncurses::displayBox(BoxData_t &data)
{
	printBox(15, 0, 0, 40);
	printBox(35, 0, 0, 40);
	printBox(15, 150, 150, 190);
	mvprintw(0, 55, "+---------------------------" \
	"----------------------------------------------------+");
	mvprintw(10, 55, "+--------------------------" \
	"-----------------------------------------------------+");
	for (int i = 1; i < 10; ++i) {
		mvprintw(i, 55, "|");
		mvprintw(i, 135, "|");
	}
	mvprintw(13, 55, "+--------------------------" \
	"-----------------------------------------------------+");
	mvprintw(50, 55, "+--------------------------" \
	"-----------------------------------------------------+");
	for (int i = 14; i < 50; ++i) {
		mvprintw(i, 55, "|");
		mvprintw(i, 135, "|");
	}
	printData(data);
}

void			Ncurses::displayLogo(std::string logoName)
{
	std::string	line;
	std::ifstream	myfile(logoName);
	int		x = 14;

	if (myfile.is_open())
	{
		while (std::getline(myfile,line)) {
			mvprintw(x, 58,"%s", line.c_str());
			x++;
		}
		myfile.close();
	}
	refresh();
}

void	Ncurses::displayMenu(
	__attribute__((unused)) BoxData_t &data, int menuIt)
{
	clear();
	usleep(500);
	for (size_t i = 30; i <= 40; i += 2) {
		mvprintw(i, 92, "  ");
	}
	mvprintw(30 + (2 * menuIt), 92, "->");
	mvprintw(30, 95, "Play");
	mvprintw(32, 95, "PreviousLib");
	mvprintw(34, 95, "NextLib");
	mvprintw(36, 95, "PreviousGame");
	mvprintw(38, 95, "NextGame");
	mvprintw(40, 95, "Exit");
}

void			Ncurses::displayUsername(std::string &name)
{
	static bool	needToClear = true;

	mvprintw(5, 60, "UserName = ");
	if (name == "") {
		mvprintw(5, 71, "Put your Username");
	} else {
		if (needToClear) {
			mvprintw(5, 71, "                 ");
			needToClear = false;
		}
		mvprintw(5, 71, "%s", name.c_str());
	}
}

int	Ncurses::loadSprites(__attribute__((unused)) map_str &paths)
{
	for (int i = 0; i < 5; i++) {
		switch(i) {
			case 0 :
				_spriteMap.push_back("#");
				break;
			case 1 :
				_spriteMap.push_back("P");
				break;
			case 2 :
				_spriteMap.push_back("E");
				break;
			case 3 :
				_spriteMap.push_back("O");
				break;
			case 4 :
				_spriteMap.push_back(".");
				break;
			default :
				break;
		}
	}
	return 0;
}

void					Ncurses::displayGame(
	const ent_list &dent, map_str &map,
	__attribute__((unused))int gamesLibIt)
{
	std::vector<std::string>	tmpMap(map);
	int				limit = map.size();
	int				i = 0;
	int				x = 15;
	auto				it  = dent.begin();
	std::stringstream		ss;

	usleep(5000);
	while(it != dent.end()) {
		ss << it->type;
		tmpMap[it->posy][it->posx] = _spriteMap[it->type][0];
		it++;
	}
	while (i < limit) {
		mvprintw(x, 83, "%s", tmpMap[i].c_str());
		x++;
		i++;
	}
}

extern "C" IGraphic*	create() {
	return new Ncurses;
}

extern "C" void		destroy(IGraphic* ptr) {
	delete ptr;
}
