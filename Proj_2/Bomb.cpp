#include "Bomb.h"
#include <time.h>



Bomb::Bomb(PositionChar targetPosition)
{
	targetPos_char = randomizePosition(targetPosition);
	targetColumn = targetPos_char.col;
	targetLine = targetPos_char.lin;
}

PositionInt Bomb::convertPositionChartoInt(PositionChar position)
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


PositionChar Bomb::convertPositionInttoChar(PositionInt position)
{
	PositionChar convertedPosition;
	char x,y;

	x = position.col + 64;
	y = position.lin + 64;

	convertedPosition.col = tolower(x);
	convertedPosition.lin = y;

	return convertedPosition;



}


PositionChar Bomb::randomizePosition(PositionChar position)
{
	PositionInt  original,north,south,east,west;
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


PositionChar Bomb::getTargetPosition() const
{
	return targetPos_char;
}