#include "Bomb.h"
#include <time.h>


/*
O construtor da bomba chama a fun��o "randomizePosition" simulando assim o defeito que a pr�pria poderia ou nao ter. 
*/
Bomb::Bomb(Position<char> targetPosition,int numLines, int numColumns)
{
	targetPos_char = randomizePosition(targetPosition, numLines , numColumns);
	targetColumn = targetPos_char.col;
	targetLine = targetPos_char.lin;
}

/*
	Esta fun��o recebecomo argumentos a posi��o introduzida pelo jogador e os 
	limites do tabuleiro do jogador adevers�rio. A bomba pode mover-se aleat�riamente
	uma casa em rela��o � sua posi��o original, excepto se se encontrar nos limites do
	tabuleiro. Nesses casos tem um n�mero limitado de op��es. Essa limita��o � feita 
	com as condi��es "if" em que, caso a movimenta��o da bomba em determinada dire��o
	implique a sua saida dos limites do tabuleiro, essa mesma dire��o passar� a corresponder
	� posi��o original.
*/
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

/*
	Retorna a posi��o final onde a bomba cai.
*/
Position<char> Bomb::getTargetPosition() const
{
	return targetPos_char;
}