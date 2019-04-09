//
// EPITECH PROJECT, 2018
// entity
// File description:
// entity
//

#ifndef ENTITY_HPP_
# define ENTITY_HPP_

#include <vector>
#include <iostream>
#include <list>

typedef	enum	entity_type_e {
	ENTT_MAIN,
	ENTT_OBJECT,
	ENTT_NEUTRAL,
	ENTT_ALLY,
	ENTT_ENEMY,
	ENTT__MAX
}		entity_type_t;

typedef struct		Entity_s {
	float		posx;
	float		posy;
	int		sprite;
	bool		specialState;
	int		type;
}			Entity_t;

using ent_list = std::list<Entity_t>;
using map_str = std::vector<std::string>;

#endif /* !ENTITY_HPP */