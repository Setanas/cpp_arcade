//
// EPITECH PROJECT, 2018
// arcade
// File description:
// keys
//

#ifndef KEYS_HPP_
	#define KEYS_HPP_

	// enum	key_value_e {
	// 	KEY_VAL_UP,
	// 	KEY_VAL_DOWN,
	// 	KEY_VAL_LEFT,
	// 	KEY_VAL_RIGHT,
	// 	KEY_VAL_VALIDE,
	// 	KEY_VAL_CANCEL,
	// 	KEY_VAL_PAUSE,
	// 	KEY_VAL_EXIT,
	// 	KEY_VAL_GRAPH_NEXT,
	// 	KEY_VAL_GRAPH_PREV,
	// 	KEY_VAL_GAME_NEXT,
	// 	KEY_VAL_GAME_PREV,
	// 	KEY_VAL__MAX
	// };

	typedef struct	Keys_inp_s {
		bool	valid;
		int	value;
		bool	shift;
	}		Keys_inp_t;

#endif /* !KEYS_HPP_ */
