#include "Player.h"

//construtor por defeito
Player::Player()
{

}

//construtor que recebe o nome e o ficheiro de tabuleiro
Player::Player(string playerName, string boardFilename)
{
	Board playerBoard(boardFilename);
	board = playerBoard;
	name = playerName;
}


/*
Apenas foi criada para que se pudesse fazer o overload o que, no mais produz c�digo mais limpo.
Para imprimir o tabuleiro de P1 basta  "cout << P1;" (ap�s ter sido feio o overloading umas linhas mais abaixo)
*/
void Player::showBoard() const
{
	
	Board toDisplay = board;
	cout << toDisplay;
}


/*
	Recebe uma bomb e ataca o tambuleiro mas antes tenta mover todos os navios.
*/
bool Player::attackBoard(const Bomb &b)
{
	board.moveShips();
	return board.attack(b);
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

	
	for (int i = 0; i < ships.size(); i++)
	{
		if (ships[i].isDestroyed())
			ships.erase(ships.begin() + i);
	}

	board.giveShips(ships);
	board.fillBoard();

	if(ships.size() == 0)
		return 1;
	else
		return 0;

}








/*
Overloading do operador "<<" para a classe "Player".
� semelhan�a do que acontece com a classe "Board", apenas � chamada uma fu��o
sendo essa a �nica que imprime informa��o no ecr�. Neste caso � a fu��o "showBoard"
.*/
ostream& operator<< (ostream &out, Player someone)
{
	someone.showBoard();
	return out;

}




//Apenas para distinguir o jogador que faz a primeira jogada
void Player::giveIndex(int number)
{
	index = number;
}

/*
Atribui ao jogador a sua pontua��o
*/
void Player::giveScore(float number)
{
	score = number;
}




/*
	Todas as fun��es que se seguem limitam-se a retornar valores
	de vari�veis privadas.
*/
string Player::getName()
{
	return name;
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

