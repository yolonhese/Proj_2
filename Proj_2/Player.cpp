#include "Player.h"
Player::Player()
{

}

Player::Player(string playerName, string boardFilename)
{
	Board playerBoard(boardFilename);
	board = playerBoard;
	name = playerName;
}

void Player::showBoard() const
{
	
	Board toDisplay = board; //tive de criar uma variavel "toDisplay" porque o overloading nao funcionava com o board. Ser� por ser private??
	cout << toDisplay;
}

Bomb Player::getBomb(Position<char> bombTarget) const
{
	Bomb createdBomb(bombTarget);
	return createdBomb;
}

void Player::attackBoard(const Bomb &b)
{
	board.moveShips();
	board.attack(b);
}

string Player::getName()
{
	return name;
}

void Player::giveIndex(int number)
{
	index = number;
}

/*
"isDefeated" � uma fun��o booleana que foi criada com o prop�sito de verificar se
o jogador foi derrotado (se toda a sua frota foi afundada). Para isso obt�m-se o vetor
dos navios colocados no tabuleiro do jogador e verifica-se um a um o seu estado ("isDestroid").
Caso ainda n�o tenha sido afundado "liveShips" incrementa. Se "liveShips" for 0, ent�o a sua frota est�
completamente destru�da e a fun��o retorna 1.
*/
bool Player::isDefeated()
{
	vector<Ship> ships;
	ships = board.getShips();

	int liveShips = 0; //numero de navios que ainda n�o est�o destru�dos;
	for (int i = 0; i < ships.size(); i++)
	{
		if (!ships[i].isDestroyed())
			liveShips++;
	}

	if(liveShips == 0)
		return 1;
	else
		return 0;

}

/*
Retorna o tamanho do tabuleiro associado ao player.
*/
int Player::getBoardSize()
{
	return board.getSize();
}

/*
Retorna a �rea total ocupada pelos navios no tabuleiro associado ao jogador.
*/
int Player::getShipArea()
{
	return board.getShipArea();
}

/*
Atribui ao jogador a sua pontua��o
*/
void Player::giveScore(float number)
{
	score = number;
}

/*
Devolve a potua��o do jogador. Isto apenas � usado no caso do mesmo ser vencedor.
*/
float Player::getScore()
{
	return score;
}

Board Player::getBoard()
{
	return board;
}

int Player::getIndex()
{
	return index;
}







/*
Overloading do operador "<<" para a classe "Player".
� semelhan�a do que acontece com a classe "Board", apenas � chamada uma fu��o
sendo essa a �nica que imprime informa��o no ecr�. Neste caso � a fu��o "showBoard"
.*/
ostream& operator<< (ostream &out, Player manoel)
{
	manoel.showBoard();
	return out;

}
