#include "Bomb.h"
#include <time.h>



Bomb::Bomb(Position<char> targetPosition)
{
	targetPos_char = randomizePosition(targetPosition);
	targetColumn = targetPos_char.col;
	targetLine = targetPos_char.lin;
}

Position<int> Bomb::convertPositionChartoInt(Position<char> position)
{
	Position<int> convertedPosition;
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


Position<char> Bomb::convertPositionInttoChar(Position<int> position)
{
	Position<char> convertedPosition;
	char x,y;

	x = position.col + 64;
	y = position.lin + 64;

	convertedPosition.col = tolower(x);
	convertedPosition.lin = y;

	return convertedPosition;



}


Position<char> Bomb::randomizePosition(Position<char> position)
{
	Position<int>  original,north,south,east,west;
	original = convertPositionChartoInt(position);
	north,south,east,west = original;

	north.lin = original.lin + 1;
	south.lin = original.lin - 1;

	east.col = original.col + 1;
	west.col = original.col - 1;

	srand (time(NULL));
	int randomNumber;
	randomNumber = rand() %5 + 1;

	switch(randomNumber)
	{
		case 1:
			return convertPositionInttoChar(original);
			break;
		case 2:
			return convertPositionInttoChar(north);
			break;
		case 3:
			return convertPositionInttoChar(south);
			break;
		case 4:
			return convertPositionInttoChar(east);
			break;
		case 5:
			return convertPositionInttoChar(west);
			break;
	}


}


Position<char> Bomb::getTargetPosition() const
{
	return targetPos_char;
}