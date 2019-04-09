//
// EPITECH PROJECT, 2018
// arcade
// File description:
// BoxData
//

#ifndef BOXDATA_HPP_
	#define BOXDATA_HPP_

	#include <vector>
	#include <string>

	using nameTab = std::vector<std::string>;

	typedef struct		BoxData_s {
		nameTab	graphsLibNames;
		int		graphsLibIt;
		nameTab	gamesLibNames;
		int		gamesLibIt;
		std::string	username;
		int		score;
	}			BoxData_t;

#endif /* !BOXDATA_HPP_ */
