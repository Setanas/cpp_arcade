/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Sfml function
*/

/*
** Keyboard:
** touches ascii a-z 0-9
** flèches directionelles 1-4 gauche 1 droite 2 haut 3 bas 4
*/

#include <iostream>
#include <sstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <unistd.h>

#include "../include/Sfml.hpp"

Sfml::Sfml(): _name("sfml")
{
}

Sfml::~Sfml()
{
}

const std::string	Sfml::getName() const
{
	return _name;
}


Keys_inp_t 		Sfml::getKey(bool all)
{
	Keys_inp_t	key{false, 0, false};

	while (_window.pollEvent(_event)) {
		if (_event.type == sf::Event::KeyReleased)
		{
			checkAlphanumericKey(key, _event.key.code);
			checkSpecialKey(key, _event.key.code, all);
		}
		if (_event.type == sf::Event::Closed) {
			key.value = -1;
			key.valid = false;
			_window.close();
		}
	}
	return (key);
}

void	Sfml::checkAlphanumericKey(Keys_inp_t &key, int keyCode)
{
	if (keyCode >= sf::Keyboard::A && keyCode <= sf::Keyboard::Z) {
		key.value = keyCode + 'a';
		key.valid = true;
	} else if (keyCode >= sf::Keyboard::Num0
		&& keyCode <= sf::Keyboard::Num9) {
		key.value = keyCode + 22;
		key.valid = true;
	}
}
void			Sfml::checkSpecialKey(Keys_inp_t &key, int keyCode,
	bool all)
{
	static bool	firstTime = true;

	if (keyCode >= sf::Keyboard::Left && keyCode <= sf::Keyboard::Down
		&& all == true) {
		key.value = keyCode - 70;
		key.valid = true;
	} else if (keyCode == sf::Keyboard::Enter && firstTime == false) {
		key.value = '\n';
		key.valid = true;
	}
	if (keyCode == sf::Keyboard::Escape) {
		key.value = 27;
		key.valid = true;
	}
	if (firstTime == true) {
		firstTime = false;
	}
}

int	Sfml::switchOn()
{
	if (_font.loadFromFile("./assets/arcade.ttf") != true) {
		return (84);
	}
	_titleText.setFont(_font);
	_window.create(sf::VideoMode(1600, 800), "SFML");
	_userBox.setSize(sf::Vector2f(600, 50));
	_userBox.setFillColor(sf::Color::Blue);
	_userBox.setOutlineColor(sf::Color::Red);
	_userBox.setOutlineThickness(THICKNESS);
	_userBox.setPosition(500, 50);
	_boxes.setSize(sf::Vector2f(300, 300));
	_boxes.setFillColor(sf::Color::Transparent);
	_boxes.setOutlineColor(sf::Color::Red);
	_boxes.setOutlineThickness(THICKNESS);
	return (0);
}

void	Sfml::switchOff()
{
	_window.close();
}

void					Sfml::displayPause()
{
	static sf::RectangleShape	menuBox(sf::Vector2f(200,
	100));

	menuBox.setFillColor(sf::Color::Black);
	menuBox.setOutlineColor(sf::Color::White);
	menuBox.setOutlineThickness(THICKNESS);
	menuBox.setPosition(725, 375);
	_window.draw(menuBox);
	displayText({16, "Pause", {780, 405}, sf::Color::White});
}

void				Sfml::displayBox(BoxData_t &data)
{
	std::stringstream	score;

	score << data.score;
	displayUsernameBox(data.username);
	displayLibBox(data.graphsLibNames, data.graphsLibIt,
	sf::Vector2f(95, 125));
	displayText({16, "Graphicals Library", {100, 145}, sf::Color::Blue});
	displayLibBox(data.gamesLibNames, data.gamesLibIt,
	sf::Vector2f(95, 445));
	displayText({16, "Games Library", {100, 465}, sf::Color::Blue});
	_boxes.setPosition(1205, 125);
	_window.draw(_boxes);
	displayText({16, "Score", {1310, 145}, sf::Color::Blue});
	displayText({12, score.str(), {1350, 275}, sf::Color::White});
	_window.display();
	_window.clear();
}

void	Sfml::displayLibBox(nameTab graphsLibNames, size_t graphsLibIt,
	sf::Vector2f position)
{
	float			posY = position.y + 70;

	_boxes.setPosition(position);
	_window.draw(_boxes);
	for (size_t it = 0; it < graphsLibNames.size(); it++) {
		if (it == graphsLibIt) {
			displayText({12, graphsLibNames[it],
			{position.x + 15, posY}, sf::Color::Green});
		} else {
			displayText({12, graphsLibNames[it],
			{position.x + 15, posY}, sf::Color::White});
		}
		posY += 35;
	}
}

void	Sfml::displayText(const TextParameter &parameter)
{
	_titleText.setCharacterSize(parameter.fontSize);
	_titleText.setString(parameter.text);
	_titleText.setPosition(parameter.position);
	_titleText.setFillColor(parameter.color);
	_window.draw(_titleText);
}

void	Sfml::displayUsernameBox(std::string &username)
{
	_window.draw(_userBox);
	displayUsername(username);
}

void	Sfml::displayUsername(std::string &username)
{
	static bool		firstTime = true;

	if (firstTime == false && username!= "") {
		displayText({18, username, {600, 65}, sf::Color::Yellow});
	} else {
		displayText({18, "Please Enter Your Name",
		{600, 65}, sf::Color::Yellow});
		firstTime = false;
	}
}

void					Sfml::displayMenu(
	__attribute__((unused)) BoxData_t &data, int menuIt)
{
	static sf::RectangleShape	menuBox(sf::Vector2f(560, 620));
	static sf::RectangleShape	littleMenuBox(sf::Vector2f(520, 75));
	static std::vector<std::string> menuText;
	static bool			firstTime = true;
	float				posY = 210;

	if (firstTime == true) {
		initMenu(menuBox, littleMenuBox, menuText);
		firstTime = false;
	}
	displayMenuBoxes(menuBox, littleMenuBox, menuIt);
	for (size_t it = 0; it < 6; it++) {
		displayText({16, menuText[it], {560, posY}, sf::Color::White});
		posY += 95;
	}
}

void	Sfml::initMenu(sf::RectangleShape &menuBox,
	sf::RectangleShape &littleMenuBox, std::vector<std::string> &menuText)
{
	menuBox.setFillColor(sf::Color::Transparent);
	menuBox.setOutlineColor(sf::Color::White);
	menuBox.setOutlineThickness(THICKNESS);
	menuBox.setPosition(520, 125);
	littleMenuBox.setFillColor(sf::Color::Transparent);
	littleMenuBox.setOutlineThickness(THICKNESS);
	menuText.push_back("Play");
	menuText.push_back("Previous Graphic");
	menuText.push_back("Next Graphic");
	menuText.push_back("Previous Game");
	menuText.push_back("Next Game");
	menuText.push_back("Exit");
}

void		Sfml::displayMenuBoxes(sf::RectangleShape &menuBox,
	sf::RectangleShape &littleMenuBox, size_t menuIt)
{
	float				posY = 180;

	for (size_t it = 0; it < 6; it++) {
		if (it == menuIt) {
			littleMenuBox.setOutlineColor(sf::Color::Green);
		} else {
			littleMenuBox.setOutlineColor(sf::Color::Blue);
		}
		littleMenuBox.setPosition(540, posY);
		posY += 95;
		_window.draw(littleMenuBox);
	}
	_window.draw(menuBox);
}

void	Sfml::displayGame(const ent_list &ent, map_str &map, int gameLibIt)
{
	displayMap(map, gameLibIt);
	displayEntities(ent, gameLibIt);
}

void		Sfml::displayMap(map_str &map, int gameLibIt)
{
	size_t	sizeVector = map.size();
	size_t	sizeString = 0;

	for (size_t it = 0; it < sizeVector; it++) {
		sizeString = map[it].size();
		for (size_t jt = 0; jt < sizeString; jt++) {
			if (map[it][jt] == '0') {
				displaySprite(jt, it, gameLibIt, 0);
			}
		}
	}
}

void		Sfml::displayEntities(const ent_list &ent, int gameLibIt)
{
	auto	it = ent.begin();

	while (it != ent.end()) {
		displaySprite(it->posx, it->posy, gameLibIt, it->sprite);
		it++;
	}
}

void			Sfml::displaySprite(float posX, float posY,
	int gameLibIt, int textureIt)
{
	sf::Sprite	sprite;
	float		newPosX = posX  * 16 + 450;
	float		newPosY = posY  * 16 + 225;

	sprite.setTexture(_textureMap[gameLibIt][textureIt]);
	sprite.setPosition(sf::Vector2f(newPosX,
	newPosY));
	_window.draw(sprite);
}

int	Sfml::loadSprites(std::vector<std::string> &paths)
{
	std::vector<sf::Texture>	textureGame;
	bool				error = false;

	for (size_t it = 0; it != paths.size(); it++) {
		error = fillTextureVector(textureGame, paths[it]);
		if (error == true) {
			return (84);
		}
	}
	_textureMap.push_back(textureGame);
	return (0);
}

bool			Sfml::fillTextureVector(
	std::vector<sf::Texture> &textures, const std::string &path)
{
	sf::Texture	texture;

	if (texture.loadFromFile(path) == false) {
		return (false);
	}
	textures.push_back(texture);
	return (false);
}

extern "C" IGraphic*	create() {
	return new Sfml;
}

extern "C" void		destroy(IGraphic* ptr) {
	delete ptr;
}
