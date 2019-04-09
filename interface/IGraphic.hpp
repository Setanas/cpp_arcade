//
// EPITECH PROJECT, 2018
// IGraphics
// File description:
// IGraphics
//

#ifndef IGRAPHIC_HPP_
	#define IGRAPHIC_HPP_

	#include <vector>
	#include <list>
	#include <string>
	
	#include "../inc/Entity.hpp"
	#include "../inc/Keys.hpp"
	#include "../inc/BoxData.hpp"

	class 					IGraphic
	{
	public:
		virtual ~IGraphic() {};
		// Getter
		virtual const std::string	getName() const = 0;
		virtual Keys_inp_t		getKey(bool all) = 0;
		// Switch
		virtual int			switchOn() = 0;
		virtual void			switchOff() = 0;
		// Display functions
		virtual void			displayPause() = 0;
		virtual int			loadSprites(map_str &paths) = 0;
		virtual void			displayBox(BoxData_t &data) = 0;
		virtual void			displayMenu(BoxData_t &data, int menuIt) = 0;
		virtual void			displayUsername(std::string &name) = 0;
		virtual void			displayGame(const ent_list &dent, map_str &map, int gamesLibIt) = 0;
	};

	typedef IGraphic	*graphsLibCreate_t();
	typedef void 		*graphsLibDestroy_t(IGraphic *);

#endif /* !IGRAPHIC_HPP */
