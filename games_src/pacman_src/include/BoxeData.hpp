//
// EPITECH PROJECT, 2018
// arcade
// File description:
// boxedata
//

#ifndef BOXEDATA_HPP_
	#define BOXEDATA_HPP_

	#include <vector>
	#include <string>

	using name_tab = std::vector<std::string>;

	typedef struct		BoxeData_s {
		name_tab	graphsLibNames;
		int		graphsLibIt;
		name_tab	gamesLibNames;
		int		gamesLibIt;
		std::string	userName;
		int		score;
	}			BoxeData_t;

#endif /* !BOXEDATA_HPP_ */
