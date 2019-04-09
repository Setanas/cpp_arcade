##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile
##

NAME		= arcade

CPP		= g++

RM		= rm -f

CP		= cp

CPPFLAGS	= -W -Wall -Wextra

CPPFLAGS	+= -I./

LDFLAGS		+= -ldl

FILE		= Main.cpp	\
		  Core.cpp

SRC		= $(addprefix ./src/, $(FILE))

OBJ		= $(SRC:.cpp=.o)

$(NAME):	$(OBJ)
		$(CPP) $(OBJ) -o $(NAME) $(LDFLAGS)
		$(CP) $(NAME) ../

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ../$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
