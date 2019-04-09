##
## EPITECH PROJECT, 2018
## ARCADE
## File description:
## 	Makefile
##

MAKER		=	@make --no-print-directory -C

CPP		=	g++

RM		=	rm -rf

all:
		$(MAKER) ncurses_src
		$(MAKER) sdl_src
		$(MAKER) sfml_src

clean:
		$(MAKER) ncurses_src clean
		$(MAKER) sdl_src clean
		$(MAKER) sfml_src clean

fclean:		clean
		$(MAKER) ncurses_src fclean
		$(MAKER) sdl_src fclean
		$(MAKER) sfml_src fclean

re:		fclean all

.PHONY:		all clean fclean re
