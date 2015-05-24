#include "Ship.h"
#include <time.h>


Ship::Ship(char symbol, Position<char> position, char orientation, unsigned int size, unsigned int color)
{
	this->symbol = toupper(symbol);
	posChar = position;
	this->orientation = orientation;
	this->size = size;
	this->color = color;
	string stat(size,toupper(symbol));
	status = stat;
}

Position<int> Ship::convertPositionChartoInt(Position<char> position)
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

Position<char> Ship::convertPositionInttoChar(Position<int> position)
{
	Position<char> convertedPosition;
	char x,y;

	x = position.col + 64;
	y = position.lin + 64;

	convertedPosition.col = tolower(x);
	convertedPosition.lin = y;

	return convertedPosition;



}

Position<char> Ship::getPosition() const
{
	return posChar;
}

char Ship::getOrientation() const
{
	return orientation;
}

unsigned int Ship::getSize() const
{
	return size;
}

char Ship::getSymbol() const
{
	return symbol;
}

unsigned int Ship::getColor() const
{
	return color;
}

bool Ship::move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax)
{
	Position<char> backupPosition = posChar;
	char backupOrientation = orientation;
	switch(direction)
	{
		case 110:
			backupPosition.lin = backupPosition.lin - 1;
			break;
		case 115:
			backupPosition.lin = backupPosition.lin + 1;
			break;
		case 119:
			backupPosition.col = backupPosition.col - 1;
			break;
		case 101:
			backupPosition.col = backupPosition.col + 1;
			break;
		case 111:
			break;
	}


	if (rotate)
	{
		if (backupOrientation == 'H')
			backupOrientation = 'V';
		else
			backupOrientation = 'H';
	}

	if (lineMin > convertPositionChartoInt(backupPosition).lin || columnMin > convertPositionChartoInt(backupPosition).col)
		return false;

	if (backupOrientation == 'H')
		if((convertPositionChartoInt(backupPosition).col + size - 1) > columnMax)
			return false;
	else
		if((convertPositionChartoInt(backupPosition).lin + size - 1) > lineMax)
			return false;

	posChar = backupPosition;
	orientation = backupOrientation;
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

bool Ship::attack(size_t partNumber)
{
	if (partNumber >= 0 && partNumber <= size)
	{
		status[partNumber-1] = tolower(status[partNumber-1]);
		return true;
	}
	else
		return false;

}

bool Ship::isDestroyed() const
{
	int i = 0,lower = 0;

	while(i < size)
	{
		if(islower(status[i]))
			lower++;
		i++;
	}

	float half = size/2;

	if(lower >= half)
		return true;
	else
		return false;


}

void Ship::giveStatus(string newStatus)
{
	status = newStatus;
}

string Ship::getStatus() const
{
	return status;
}


void Ship::show() const
{
	cout <<"Simbolo: " <<symbol << endl;
	cout << "Linha de Inicio: " << posChar.lin<< endl;
	cout << "Coluna de Inicio: " << posChar.col << endl;
	cout << "Orientacao: " << orientation << endl;
	cout << "Tamanho: " << size << endl;
	cout << "Codigo da cor: " << color << endl;
	cout << "Estado do Navio: " << status << endl;
	
}