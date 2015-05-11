#include "Ship.h"
#include <time.h>

Ship::Ship(char symbol, PositionChar position, char orientation, unsigned int size, unsigned int color)
{
	this->symbol = symbol;
	posChar = position;
	this->orientation = orientation;
	this->size = size;
	this->color = color;

}

PositionInt Ship::convertPositionChartoInt(PositionChar position)
{
	PositionInt convertedPosition;
	char x,y;
	int coordinate;

	x = position.col;
	y = position.lin;

	x = toupper(x);
	coordinate = x;
	coordinate = coordinate-64;

	convertedPosition.col = coordinate;

	coordinate = y;
	coordinate = coordinate-64;

	convertedPosition.lin = coordinate;

	return convertedPosition;
}

PositionChar Ship::convertPositionInttoChar(PositionInt position)
{
	PositionChar convertedPosition;
	char x,y;

	x = position.col + 64;
	y = position.lin + 64;

	convertedPosition.col = tolower(x);
	convertedPosition.lin = y;

	return convertedPosition;



}


bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{

	switch(direction)
	{
		case 110:
			posChar.lin = posChar.lin - 1;
			break;
		case 115:
			posChar.lin = posChar.lin + 1;
			break;
		case 119:
			posChar.col = posChar.col - 1;
			break;
		case 101:
			posChar.col = posChar.col + 1;
			break;
		case 111:
			break;
	}


	if (rotate)
	{
		if (orientation == 'H')
			orientation = 'V';
		else
			orientation = 'H';
	}

	if (lineMin > convertPositionChartoInt(posChar).lin || columnMin > convertPositionChartoInt(posChar).col)
		return false;


	if (orientation == 'H')
		if((convertPositionChartoInt(posChar).col + size - 1) > columnMax)
			return false;
	else
		if((convertPositionChartoInt(posChar).lin + size - 1) > lineMax)
			return false;

	return true;
}

bool Ship::moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{
	
	
	bool rotate;
	char direction;

	srand (time(NULL));
	int randomNumber;
	randomNumber = rand() %5 + 1;

	switch(randomNumber)
	{
		case 1:
			direction = 'n';
			break;
		case 2:
			direction = 's';
			break;
		case 3:
			direction = 'e';
			break;
		case 4:
			direction = 'w';
			break;
		case 5:
			direction = 'o';
			break;
	}

	srand (time(NULL));
	randomNumber = rand() %2 + 1;

		switch(randomNumber)
	{
		case 1:
			rotate = true;
			break;
		case 2:
			rotate = false;
			break;
	}

	return	move( direction, rotate, lineMin, columnMin, lineMax, columnMax);

}



