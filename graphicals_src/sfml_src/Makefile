##
## EPITECH PROJECT, 2018
## Arcade
## File description:
## Makefile
##

# TEST		= test_sfml

NAME		= lib_arcade_sfml.so

CPP		= g++

RM		= rm -f

CP		= cp

CPPFLAGS	= -W -Wall -Wextra

CPPFLAGS	+= -shared -fpic

CPPFLAGS	+= -I./include

LDFLAGS		= -lsfml-graphics -lsfml-window -lsfml-system

FILE		= Sfml.cpp

SRC		= $(addprefix ./src/, $(FILE))

OBJ		= $(SRC:.cpp=.o)

$(NAME):	$(OBJ)
		$(CPP) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(NAME)
		$(CP) $(NAME) ../../lib/

# $(TEST):	$(OBJ)
# 		$(CPP) $(LDFLAGS) $(OBJ) -o $(TEST)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) ../../lib/$(NAME)

re:		fclean all

.PHONY:		all clean fclean re
