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
	
	Board toDisplay = board; //tive de criar uma variavel "toDisplay" porque o overloading nao funcionava com o board. Será por ser private??
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
"isDefeated" é uma função booleana que foi criada com o propósito de verificar se
o jogador foi derrotado (se toda a sua frota foi afundada). Para isso obtém-se o vetor
dos navios colocados no tabuleiro do jogador e verifica-se um a um o seu estado ("isDestroid").
Caso ainda não tenha sido afundado "liveShips" incrementa. Se "liveShips" for 0, então a sua frota está
completamente destruída e a função retorna 1.
*/
bool Player::isDefeated()
{
	vector<Ship> ships;
	ships = board.getShips();

	int liveShips = 0; //numero de navios que ainda não estão destruídos;
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
Retorna a área total ocupada pelos navios no tabuleiro associado ao jogador.
*/
int Player::getShipArea()
{
	return board.getShipArea();
}

/*
Atribui ao jogador a sua pontuação
*/
void Player::giveScore(float number)
{
	score = number;
}

/*
Devolve a potuação do jogador. Isto apenas é usado no caso do mesmo ser vencedor.
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
À semelhança do que acontece com a classe "Board", apenas é chamada uma fução
sendo essa a única que imprime informação no ecrã. Neste caso é a fução "showBoard"
.*/
ostream& operator<< (ostream &out, Player manoel)
{
	manoel.showBoard();
	return out;

}
