##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile
##

NAME		= lib_arcade_ncurses.so

CPP		= g++

RM		= rm -f

CP		= cp

CPPFLAGS	= -W -Wall -Wextra

CPPFLAGS	+= -shared -fpic

CPPFLAGS	+= -I./include -I../../inc/ -I../../interface

FILE		= Ncurses.cpp

SRC		= $(addprefix ./src/, $(FILE))

OBJ		= $(SRC:.cpp=.o)

LDFLAGS	= -lncurses	

$(NAME):	$(OBJ)
		$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
		$(CP) $(NAME) ../../lib/

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ../../lib/$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
