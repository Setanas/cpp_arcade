##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile
##

NAME		= lib_arcade_nibbler.so

CPP		= g++

RM		= rm -f

CP		= cp

CPPFLAGS	= -W -Wall -Wextra

CPPFLAGS	+= -shared -fpic

CPPFLAGS	+= -I./include -I../../inc/ -I../../interface

FILE		= Nibbler.cpp

SRC		= $(addprefix ./src/, $(FILE))

OBJ		= $(SRC:.cpp=.o)

$(NAME):	$(OBJ)
		$(CPP) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
		$(CP) $(NAME) ../../games/

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ../../games/$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
