//
// EPITECH PROJECT, 2018
// Pacmanr
// File description:
// Pacmanr
//

#include <unistd.h>

#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <ncurses.h>
#include "Entity.hpp"
#include "Keys.hpp"
#include "Pacman.hpp"

Pacman::Pacman() : _tmpDir(0)
{
}

Pacman::~Pacman()
{
}

void				Pacman::initEntity()
{
	_entity.clear();
	_entity.push_back({4, 2, 1, false, 3});
	_entity.push_back({4, 9, 1, false, 3});
	_entity.push_back({4, 13, 1, false, 3});
	_entity.push_back({23, 2, 1, false, 3});
	_entity.push_back({25, 13, 1, false, 3});
	_entity.push_back({20, 13, 2, false, 1});
	_entity.push_back({21, 13, 2, false, 1});
	_entity.push_back({22, 13, 2, false, 1});
	_entity.push_back({23, 13, 2, false, 1});

}

map_str				Pacman::getMap() const
{
	map_str		map;
	std::string 	line;
	std::ifstream	myfile("./Patern/mapNipper");

	if (myfile.is_open()) {
	 	while (std::getline(myfile, line)) {
	 		map.push_back(line);
		}
		myfile.close();
	}
	return map;
}

const std::string		Pacman::getName() const
{
	std::string		name("Nipper");

	return name;
}

int				Pacman::getScore() const
{
	return score;
}

const ent_list			&Pacman::getEntity() const
{
	return _entity;
}

bool	Pacman::checkCollider(ent_list::iterator it)
{
	std::list<struct Entity_s>::iterator	tmpIt;
	int										x = it->posx;
	int										y = it->posy;

	tmpIt = _entity.begin();
	while (tmpIt != _entity.end()) {
		if (tmpIt->type == 3 &&
		(tmpIt->posx == x && tmpIt->posy == y)) {
			_entity.erase(tmpIt);
			addTail();
			return true;
		}
		tmpIt++;
	}
	return false;
}

void	Pacman::addTail()
{
	std::list<struct Entity_s>::iterator it = _entity.end();

	it--;
	_entity.push_back({it->posx, it->posy, it->sprite,
	it->specialState, 1});
}

void	Pacman::movePlayer(float x, float y)
{
	std::list<struct Entity_s>::iterator it;
	int				     oldPosX;
	int				     oldPosY;
	int				     newPosX;
	int				     newPosY;

	it = _entity.begin();
	while (it != _entity.end() && it->type != 1) {
		it++;
	}
	oldPosX = it->posx;
	oldPosY = it->posy;
	newPosX = it->posx + x;
	newPosY = it->posy + y;
	if (oldPosX + 1 == newPosX || oldPosY + 1 == newPosY ||
	oldPosX - 1 == newPosX || oldPosY - 1 == newPosY ) {
		moveTail();
	}
	it->posx += x;
	it->posy += y;
	if(checkCollider(it))
		score++;
}

void	Pacman::moveTail()
{
	std::list<struct Entity_s>::iterator it = _entity.end();
	std::list<struct Entity_s>::iterator stock;
	std::stringstream	toto;

	it--;
	while (it != _entity.begin() && it->type == 1) {
		stock = it;
		it--;
		if (it->type == 1) {
			stock->posx = it->posx;
			stock->posy = it->posy;
		}
	}
}

void				Pacman::action(const Keys_inp_t &key)
{
	if (key.value != -1 && key.valid == true) {
		_tmpDir = key.value;
	}
	switch (_tmpDir) {
		case 1 :
			movePlayer(-0.01, 0);
			break;
		case 2 :
			movePlayer(0.01, 0);
			break;
		case 3 :
			movePlayer(0, -0.01);
			break;
		case 4 :
			movePlayer(0, 0.01);
			break;
		default :
			break;
	}
}

bool				Pacman::testWallCollider(size_t playerX,
size_t playerY)
{
	map_str							_map = getMap();

	for(size_t i = 0; i < _map.size(); i++) {
		for(size_t x = 0; x < _map[i].size(); x++) {
			if (_map[i][x] == '0' && playerX == x && playerY == i)
				return true;
		}
	}
	return false;
}

bool				Pacman::testSnakeCollider(size_t playerX, size_t playerY,
											std::vector<ent_list::iterator> itList)
{
	for (size_t i = 0; i < itList.size(); i++) {
		if (playerX == itList[i]->posx && playerY == itList[i]->posy)
			return true;
	}
	return false;
}

bool				Pacman::multipleTestForCheckEnd(ent_list::iterator tmpIt,
												std::vector<ent_list::iterator> itList)
{
	int									playerX = tmpIt->posx;;
	int									playerY = tmpIt->posy;

	if (testWallCollider(playerX, playerY))
		return true;
	if (testSnakeCollider(playerX, playerY, itList))
		return true;
	return false;
}

bool				Pacman::endOfGame()
{
	size_t								nbrObject = 0;
	bool								_isFirst = true;
	std::vector<ent_list::iterator>		itList;
	ent_list::iterator 					tmpIt;

	for (ent_list::iterator it = _entity.begin(); it != _entity.end(); it++) {
		if (it->type == 3)
			nbrObject++;
		if (it->type == 1 && _isFirst) {
			tmpIt = it;
			_isFirst = false;
		} else
			itList.push_back(it);
	}
	if (multipleTestForCheckEnd(tmpIt, itList))
		return true;
	if (nbrObject > 0)
			return false;
	return true;
}

std::vector<std::string>	Pacman::getSprites(void) const
{
	std::vector<std::string> sprite;

	sprite.push_back("./ressources/Nibbler/Wall.png");
	sprite.push_back("./ressources/Nibbler/apple.png");
	sprite.push_back("./ressources/Nibbler/head.png");
	sprite.push_back("./ressources/Nibbler/body.png");
	return sprite;
}

extern "C" IGame*	create() {
	return new Pacman;
}

extern "C" void		destroy(IGame* ptr) {
	delete ptr;
}
