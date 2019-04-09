/*
** EPITECH PROJECT, 2018
** Nom_du_Projet
** File description:
**
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "../../../interface/IGraphic.hpp"

# define WINDOWX 1600
# define WINDOWY 800

# define THICKNESS 2.5


struct TextParameter {
	unsigned int	fontSize;
	std::string	text;
	sf::Vector2f	position;
	sf::Color	color;
};

class Sfml: public IGraphic
{
public:
	Sfml();
	~Sfml() override;
	// Getter
	const std::string       getName() const;
	Keys_inp_t	      getKey(bool all);
	// Switch
	int		     switchOn();
	void		    switchOff();
	// Display functions
	void		    displayPause();
	int		     loadSprites(map_str &paths);
	void		    displayBox(BoxData_t &data);
	void		    displayMenu(BoxData_t &data, int menuIt);
	void		    displayUsername(std::string &name);
	void		    displayGame(const ent_list &dent,
				map_str &map, int gamesLibIt);

private:
	void			checkAlphanumericKey(Keys_inp_t &key,
				int keyCode);
	void			checkSpecialKey(Keys_inp_t &key,
				int keyCode, bool all);

	void			displayLibBox(nameTab graphsLibNames,
				size_t graphsLibIt, sf::Vector2f position);
	void			displayText(const TextParameter &parameter);
	void			displayUsernameBox(std::string &usernam);
	void			initMenu(sf::RectangleShape &menuBox,
				sf::RectangleShape &littleMenuBox,
				std::vector<std::string> &menuText);
	void			displayMenuBoxes(sf::RectangleShape &menuBox,
				sf::RectangleShape &littleMenuBox,
				size_t menuIt);
	bool			fillTextureVector(std::vector<sf::Texture>
				&texture, const std::string &path);
	void			displayEntities(const ent_list &ent,
				int gameLibIt);
	void			displayMap(map_str &map,
				int gameLibIt);
	void			displaySprite(float posX, float posY,
				int gameLibIt, int textureIt);
	const std::string       _name;
	std::vector<std::vector<sf::Texture>>   _textureMap;
	sf::RenderWindow			_window;
	sf::Event			       _event;
	sf::Font				_font;
	sf::Text				_titleText;
	sf::RectangleShape		      _userBox;
	sf::RectangleShape		      _boxes;
};

#endif /* !SFML_HPP_ */
