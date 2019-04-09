##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## 	Makefile
##

MAKER		= @make --no-print-directory -C

CPP		= g++

MKDIR		= mkdir

RM		= rm -rf

core_game_graph:
		$(RM) games
		$(RM) lib
		$(MKDIR) games
		$(MKDIR) lib
		$(MAKER) core_src
		$(MAKER) games_src
		$(MAKER) graphicals_src

all:		core_game_graph

core:
		$(MAKER) core_src

games:
		$(RM) games
		$(MKDIR) games
		$(MAKER) games_src

graphicals:
		$(RM) lib
		$(MKDIR) lib
		$(MAKER) graphicals_src

clean:
		$(MAKER) core_src clean
		$(MAKER) games_src clean
		$(MAKER) graphicals_src clean

fclean:		clean
		$(MAKER) core_src fclean
		$(MAKER) games_src fclean
		$(MAKER) graphicals_src fclean
		$(RM) games
		$(RM) lib

re:		fclean all

.PHONY:	core_game_graph all core games graphicals_src clean fclean re
