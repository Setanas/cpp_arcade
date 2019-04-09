//
// EPITECH PROJECT, 2018
// Igame
// File description:
// interface
//

#ifndef	IGAME_HPP_
	#define IGAME_HPP_

	#include <vector>
	#include <list>
	#include "../inc/Entity.hpp"
	#include "../inc/Keys.hpp"

	class 						IGame {
	public:
		// Ctor/Dtor/Init
		virtual					~IGame() {};
		virtual void				initEntity() = 0;
		// Getters
		virtual map_str				getMap() const = 0;
		virtual const std::string		getName() const = 0;
		virtual int				getScore() const = 0;
		virtual const ent_list			&getEntity() const = 0;
		// Methods
		virtual void				action(const Keys_inp_t &key) = 0;
		virtual bool				endOfGame() = 0;
		virtual std::vector<std::string>	getSprites(void) const = 0;
	};

	typedef IGame	*gamesLibCreate_t();
	typedef void	*gamesLibDestroy_t(IGame *);

#endif
