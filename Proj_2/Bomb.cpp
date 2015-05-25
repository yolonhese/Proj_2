#include "Bomb.h"
#include <time.h>



Bomb::Bomb(Position<char> targetPosition,int numLines, int numColumns)
{
	targetPos_char = randomizePosition(targetPosition, numLines , numColumns);
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


Position<char> Bomb::randomizePosition(Position<char> position, int numLines , int numColumns)
{
	Position<char> north,south,east,west;
	north = position;
	south = position;
	east = position;
	west = position;

	if(position.lin != 'A')
		north.lin = position.lin - 1;

	south.lin = position.lin + 1;

	east.col = position.col + 1;

	if(position.col != 'a')
		west.col = position.col - 1;


	if((int)south.lin > (numLines + 64) )
		south = position;

	if((int)east.col > (numColumns + 96) )
		east = position;


	srand (time(NULL));
	int randomNumber;
	randomNumber = rand() %5 + 1;

	switch(randomNumber)
	{
		case 1:
			return position;
			break;
		case 2:
			return north;
			break;
		case 3:
			return south;
			break;
		case 4:
			return east;
			break;
		case 5:
			return west;
			break;
	}


}


Position<char> Bomb::getTargetPosition() const
{
	return targetPos_char;
}