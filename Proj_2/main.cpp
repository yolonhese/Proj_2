#include <iostream>
#include <time.h>
#include "Player.h"



using namespace std;

struct playerLog
{

	string name;
	int boardSize;


};


/*
"firstToPlay" determina aleatóriamente qual dos jogadores é
o player de index 1 (primeiro a jogar) e qual o jogador de index 2.
Imprime no fim da sua execução uma mensagem do ecrã qual dos dois é o primeiro.
*/
void firstToPlay(Player &a,Player &b)
{
	srand(time(NULL));
	int randomNumber = rand() %2 + 1;

	
	if (randomNumber == 1)
	{	
		a.giveIndex(1);
		b.giveIndex(2);
		cout << a.getName() + " is the first one to play" << endl;
	}
	if (randomNumber == 2)
	{
		b.giveIndex(1);
		a.giveIndex(2);
		cout << b.getName() + " is the first one to play" << endl;
	}

}

void playing(Player &a, Player &b)
{
	//neste cenário, "a" está a atacar "b"
	cout << "Take a look at " << b.getName() << "'s board" << endl;
	cout << b << endl;
	cout << "Insert the coordinates for the bomb (LineColumn): ";

	string typedCoordinates;
	cin >> typedCoordinates;
	/*
	Usando "c_str" transformamos a string "typedCoordinates" num array
	facilitando o acesso idividual a cada letra introduzida.
	*/
	PositionChar bombCoordinates;
	bombCoordinates.lin = typedCoordinates.c_str()[0];
	bombCoordinates.col = typedCoordinates.c_str()[1];

	Bomb theBomb(bombCoordinates);

	cout << "The bomb will be dropped in the position ";
	cout << theBomb.getTargetPosition().lin;
	cout << theBomb.getTargetPosition().col << endl;

	b.attackBoard(theBomb);

}

void Game(vector<playerLog> topTen, Player &P1,Player &P2)
{
	int p1Moves,p2Moves,winnerMoves;
	Player winner,looser;
	while (true)
	{
		playing(P1,P2);
		p1Moves++;
		if(P2.isDefeated())
		{
			winner = P1;
			looser = P2;
			winnerMoves = p1Moves;
			break;
		}
		playing(P2,P1);
		p2Moves++;
		if(P1.isDefeated())
		{
			winner = P2;
			looser = P1;
			winnerMoves = p2Moves;
			break;
		}
	}

	float score;
	score = winnerMoves * winner.getShipArea() / winner.getBoardSize();
	//nao tenho a certeza se o professor queria dizer: winnerMoves * ( winner.getShipArea() / winner.getBoardSize() )

	cout << "The winner is " << winner.getName() << endl << " with " << score << " points!";





}




int main()
{

	/*string p1Name,p2Name,boardFileName;

	cout << "PLAYER 1" << endl;
	cout << "Name: ";
	cin >> p1Name;
	cout << "Board configuration file name: ";
	cin >> boardFileName;
	Player P1(p1Name,boardFileName);

	cout << "PLAYER 2" << endl;
	cout << "Name: ";
	cin >> p2Name;
	cout << "Board configuration file name: ";
	cin >> boardFileName;
	Player P2(p2Name,boardFileName);

	Player backupPlayer;*/

	Board b("conf.tab");

	cout << b;

	 

	system("pause");




	return 0;
}