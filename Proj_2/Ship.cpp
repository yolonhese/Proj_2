#include "Ship.h"
#include <time.h>

/*
	Construtor da classe Ship.
	A �nica particularidade a apontar ser� a forma como se atribui
	um valor a "status". � uma string que tem o mesmo comprimento do navio
	e constituida pela repeti��o do s�mbolo do memso.
*/
Ship::Ship(char symbol, Position<char> position, char orientation, unsigned int size, unsigned int color)
{
	this->symbol = toupper(symbol);
	posChar = position;
	this->orientation = orientation;
	this->size = size;
	this->color = color;
	string stat(size,symbol);
	status = stat;
}



/*
	Esta fun��o foi criada apenas para simplificar a leitura e debugging do c�digo na fun��o
	"move". Recebe uma vari�vel do tipo Position<char> e retorna a mesma convertida
	em Position<int>
*/
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


/*
	A fun��o "move" tal como o nome indica move (tenta mover) o navio na dire��o indicada
	e/ou roda-lo, tendo em conta o valor de "rotate". � criada inicialmente uma "backupPosition" que
	� alterada ao longo da fun��o tendo em conta os argumentos. Caso esta n�o saia dos limites do tabuleiro
	(tambem recebidos como argumentos) ent�o altera-se a "positionChar" e a fun��o retorna 1. Caso contr�rio,
	"positionChar" n�o sofre qualquer tipo de altera��o e a fun��o retona 0.
*/

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


/*
	"moveRand" obt�m aleat�riamente valores para os argumentos "direction" e "rotate" recebidos pela fun��o "move".
	Em seguida chama esta mesma fun��o com os argumentos obtidos e retorna o seu valor.
*/
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

/*
	Esta fun��o recebe como argumento o n�mero correspondente � pe�a do navio
	que est� a ser atacada. Caso esta esteja dentro dos limites da dimens�o do mesmo,
	acede-se � pe�a (uma das letras da string "status") e substitui-se por a mesma letra
	mas min�scula com a fun��o "tolower". Caso nao perten�a a estes limites a fun��o retorna
	falso e "status" permanece inalterado.
*/
bool Ship::attack(size_t partNumber)
{
	if (partNumber >= 0 && partNumber <= size)
	{
		if(islower(status[partNumber-1]))
			return false;
		status[partNumber-1] = tolower(status[partNumber-1]);
		return true;
	}
	else
		return false;

}

/*
	Verifica se metade ou acima de metade de "status" do navio
	s�o letras min�sculas. Caso se verifique, a fun��o retorna 
	true significando que o mesmo foi destruido.
*/
bool Ship::isDestroyed() const
{
	int i = 0,lower = 0;

	while(i < size)
	{
		if(islower(status.c_str()[i]))
			lower++;
		i++;
	}

	float half = size/2.0;

	if(lower >= half)
		return true;
	else
		return false;


}




/*
	Todas as fun��es que se seguem limitam-se a retornar valores
	de vari�veis privadas.
*/
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

string Ship::getStatus() 
{
	return status;
}
