//
// EPITECH PROJECT, 2018
// Nibbler
// File description:
// Nibbler
//

#ifndef	Nibbler_HPP_
# define Nibbler_HPP_

#include <vector>
#include <list>
#include "Entity.hpp"
#include "Keys.hpp"
#include "IGame.hpp"

class Nibbler : public IGame
{
public:
	Nibbler();
	~Nibbler();
	virtual void				initEntity();
	// Getters
	virtual map_str				getMap() const;
	virtual const std::string		getName() const;
	virtual int				getScore() const;
	virtual const ent_list			&getEntity() const;
	// Methods
	virtual void				action(const Keys_inp_t &key);
	virtual bool				endOfGame();
	virtual std::vector<std::string>	getSprites(void) const;
private:
	void			movePlayer(float x, float y);
	void			moveTail();
	void			addTail();
	bool			checkCollider(ent_list::iterator it);
	bool				testSnakeCollider(size_t playerX, size_t playerY,
										std::vector<ent_list::iterator> itList);
	bool				testWallCollider(size_t playerX,
	size_t playerY);
	bool				multipleTestForCheckEnd(ent_list::iterator tmpIt,
											std::vector<ent_list::iterator> itList);
	int			_tmpDir;
	int			score;
	bool		isEnd;
	ent_list	_entity;
};

#endif
