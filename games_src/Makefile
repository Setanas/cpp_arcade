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
		$(MAKER) nibbler_src
		$(MAKER) pacman_src

clean:
		$(MAKER) nibbler_src clean
		$(MAKER) pacman_src clean

fclean:		clean
		$(MAKER) nibbler_src fclean
		$(MAKER) pacman_src fclean

re:		fclean all

.PHONY:		all clean fclean re
