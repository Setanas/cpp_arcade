//
// EPITECH PROJECT, 2018
// graphic
// File description:
// ncurses
//

#ifndef NCURSES_HPP_
	#define NCURSES_HPP_

	#include <vector>
	#include <list>
	#include <string>
	
	#include "Entity.hpp"
	#include "Keys.hpp"
	#include "BoxData.hpp"
	#include "IGraphic.hpp"

	class Ncurses : public IGraphic
	{
	public:
		Ncurses();
		~Ncurses();
		// Getter
		virtual const std::string	getName() const;
		virtual Keys_inp_t		getKey(bool all);
		// Switch
		virtual int	switchOn();
		virtual void	switchOff();
		// Display functions
		virtual void	displayPause();
		virtual int	loadSprites(map_str &paths);
		virtual void	displayBox(BoxData_t &data);
		virtual void	displayMenu(BoxData_t &data, int menuIt);
		virtual void	displayUsername(std::string &name);
		virtual void	displayGame(const ent_list &dent, map_str &map, int gamesLibIt);
		void		displayLogo(std::string logoName);
	private:
		void	printBox(int x, int y, int nbrX, int nbrY);
		void	printData(BoxData_t &data);
		int	switchKey(int ch);

		std::vector<std::string>	_spriteMap;
	};

#endif /* !NCURSES_HPP_ */
