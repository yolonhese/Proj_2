#include "Player.h"

Player::Player(string playerName, string boardFilename)
{
	Board playerBoard(boardFilename);
	board = playerBoard;
	name = playerName;
}

void Player::showBoard() const
{
	board.display();
}

Bomb Player::getBomb(PositionChar bombTarget) const
{
	Bomb createdBomb(bombTarget);
	return createdBomb;
}

void Player::attackBoard(const Bomb &b)
{
	board.moveShips();
	board.attack(b);
}







