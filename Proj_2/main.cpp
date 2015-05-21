#include <iostream>
#include <time.h>
#include "Player.h"



using namespace std;

struct playerLog
{

	string name;
	int boardSize;


};

//teste branch reesre

Player firstToPlay(Player a,Player b)
{
	srand(time(NULL));
	int randomNumber = rand() %2 + 1;

	
	if (randomNumber == 1)
	{	
		return a;
	}
	if (randomNumber == 2)
	{
		return b;
	}

}

void Game(vector<playerLog> topTen, Player &P1,Player &P2)
{






}




int main()
{

	string p1Name,p2Name,boardFileName;

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

	Player backupPlayer;
	backupPlayer = firstToPlay(P1,P2);


	

	 

	system("pause");




	return 0;
}