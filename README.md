# cpp_arcade

cpp_arcade is one of the second year project in Epitech. <br/>
The goal of this project is to create library of games/graphics which we can switch during the game. <br/>
We only managed to make one game on 2 and two graphicals library on 3. <br/>
We have a snake library, sfml library and ncurses library. <br/>

![menu](/ressources/github/menu.png)
![snake](/ressources/github/snake.png)
## Getting Started

This game is programmed in C++ on a Linux environment.

### Prerequisites

To compile we are using g++.<br/>
The programm use the ncruses library and the Sfml library.
The Sfml version is the 2.5.1. (PLease use a good version because older version can
cause some problems when trying to destroy sf::text)

### Installing

To install the core, game libraries and graphical libraries please use the Makefile to compile.
 
```
$> make
```

At the end you should have an "arcade" binary in your current folder, game libraries in the folder "games" and graphical libraries in the folder "lib"

If you want to create only the "arcade" binary you can do this :
```
$> make core
```

If you want to create only game libraries you can do this :
```
$> make games
```

If you want to create only graphicals libraries you can do this :
```
$> make graphicals
```

## Running the programm

To run :<br/>

```
$> ./arcade {path_to_graphical_library}
```

For example :
```
$>./arcade lib/lib_arcade_sfml.so 
```

You will arrive on this screen where you will have to enter a nickname then press enter :
![nickname](/ressources/github/nickname.png)

In the menu or in the game you can change the graphical library by pressing "b" for the previous library or by pressing "n".
In the game you can change the game library by pressing "g" for the previous library or by pressing "h".
You can pause the game by pressing "p".
You can reset the game by pressing "r".
You can go to the menu by pressing "m"

## Authors

* **Sébastien Tan** - *Developer* - [Setanas](https://github.com/Setanas)

## Collaborater

* **Guillaume Rault** - *Developer*
* **Rémi correnson** - *Developer*