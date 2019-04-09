/*
** EPITECH PROJECT, 2018
** ARCADE
** File description:
**	Project main function
*/

#include <iostream>
#include <fstream>      // std::ifstream
#include "../../inc/Core.hpp"

static int	checkUsage(int ac, const char **av)
{
	if (ac != 2) {
		std::cerr << "! : Bad usage" << std::endl;
		std::cout << "USAGE: ./arcade PATH_TO_GRAPHICAL_LIBRARY" << std::endl;
		return 84;
	}
	std::ifstream	file(av[1]);

	if (!file) {
		std::cerr << "! : " << av[1] << " : file not found" << std::endl;
		return 84;
	}
	return 0;
}

int		main(int ac, const char **av)
{
	std::cout << "Welcome in Arcade..." << std::endl;
	if (checkUsage(ac, av) != 0) {
		return 84;
	}
	// std::string	pathToDefaultGraphsLib = av[1];

	Core	Core(av[1]);

	Core.RunArcade();

	std::cout << "Quitting Arcade..." << std::endl;
	return 0;
}
