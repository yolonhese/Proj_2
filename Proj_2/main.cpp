#include <iostream>
#include <time.h>
#include <windows.h>
#include "Player.h"




using namespace std;

void centrar(string s)//Funçao que centra o texto do menu
{
	int l=s.size();
	int pos=(int)((80-l)/2);
	for(int i=0;i<pos;i++)
	cout<<" ";
 
	cout<<s;
}

int menu()
{
        string Menu[4] = {"Start Game", "Create Board", "TOP10", "Exit"};
        int pointer = 0;
       
        while(true)
        {
                system("cls");
               
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                centrar("Menu");
                cout<<endl<<endl;
               
                for (int i = 0; i < 4; ++i) //Trocar a cor para opcao selecionada
                {
                        if (i == pointer)
                        {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                                centrar(Menu[i]);
                                        cout << endl;
                        }
                        else
                        {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                                centrar(Menu[i]);
                                        cout << endl;
                        }
                }
               
                while(true) //Detectar setas
                {
                        if (GetAsyncKeyState(VK_UP) != 0)
                        {
                                pointer -= 1;
                                if (pointer == -1)
                                {
                                        pointer = 2;
                                }
                                break;
                        }
                        else if (GetAsyncKeyState(VK_DOWN) != 0)
                        {
                                pointer += 1;
                                if (pointer == 4)
                                {
                                        pointer = 0;
                                }
                                break;
                        }
                        else if (GetAsyncKeyState(VK_RETURN) != 0)
                        {
                                switch (pointer)
                                {
                                        case 0:
                                        {
                                                cout << "\n\n\nStarting new game...";
                                                Sleep(1000);
                                        } break;
                                        case 1:
                                        {
                                                cout << "\n\n\nThis is the options...";
                                                Sleep(1000);
                                        } break;
                                        case 2:
                                        {
                                                return 0;
                                        } break;
                                }
                                break;
                        }
                }
               
                Sleep(150);
        }
       
        return 0;
}

struct topScore
			{
				float score;
				string name;
				int boardSize,shipArea;
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


float playing(Player &a, Player &b)
{
	//neste cenário, "a" está a atacar "b"
	float begin = clock(); //regista o início da jogada
	Position<char> bombCoordinates;
	bool valid = 1;
	
	do
	{
		cout << "Take a look at " << b.getName() << "'s board" << endl;
		cout << b << endl;
		cout << "Insert the coordinates for the bomb (LineColumn): ";

		string typedCoordinates;
		cin >> typedCoordinates;
		/*
		Usando "c_str" transformamos a string "typedCoordinates" num array
		facilitando o acesso idividual a cada letra introduzida.
		*/
		bombCoordinates.lin = typedCoordinates.c_str()[0];
		bombCoordinates.col = typedCoordinates.c_str()[1];
		if((b.getBoard().getMaxLine() < int(bombCoordinates.lin) - 64) && (b.getBoard().getMaxColumn() < int(toupper(bombCoordinates.col)) - 64))
		{
			valid = 0;
			system("cls");
			cout << "Please enter valid coordiates" << endl;
			Sleep(100);
			system("cls");
		}
		
	}while (!valid);
	float end = (clock() - begin ) / (float) CLOCKS_PER_SEC; //guarda na variavel end o tempo decorrido até ao fim da jogada


	Bomb theBomb(bombCoordinates);
	cout << "The bomb will be dropped in the position ";
	cout << theBomb.getTargetPosition().lin;
	cout << theBomb.getTargetPosition().col << endl;

	b.attackBoard(theBomb);

	return end;

}


void addToTop(Player someone)
{
	ifstream log("topTen.log");
	
	if(!log.good())
	{
		ofstream log("topTen.log");

		log << someone.getScore();
		log << " ";
		log << someone.getName();
		log << " ";
		log << someone.getBoardSize();
		log << " ";
		log << someone.getShipArea();
		log << endl;

		log.close();
	}
	else
	{
		vector<topScore> highScores;
		while(!log.eof())
		{
			string score_str,name,boardSize_str,shipArea_str;
			getline(log, score_str , ' ');
			getline(log, name , ' ');
			getline(log, boardSize_str , ' ');
			getline(log, shipArea_str);

			float score;
			int boardSize,shipArea;
			score = atof(score_str.c_str());
			boardSize = atoi(boardSize_str.c_str());
			shipArea = atoi(shipArea_str.c_str());

			topScore defaultTop;
			defaultTop.score = score;
			defaultTop.name = name;
			defaultTop.boardSize = boardSize;
			defaultTop.shipArea = shipArea;

			highScores.push_back(defaultTop);
		}
		topScore someoneScore;
		someoneScore.score = someone.getScore();
		someoneScore.name = someone.getName();
		someoneScore.boardSize = someone.getBoardSize();
		someoneScore.shipArea = someone.getShipArea();
		log.close();
		for(int i = 0; i < highScores.size() ; i++)
		{
			if(someoneScore.score < highScores[i].score)
			{
				highScores.insert(highScores.begin()+i,someoneScore);
				break;
			}
		}

		while (highScores.size() > 10)
		{
			highScores.pop_back();
		}

		ofstream freshLog("topTen.log" , ofstream::trunc);

		for(int i = 0; i < highScores.size() ; i++)
		{
			freshLog << highScores[i].score;
			freshLog << " ";
			freshLog << highScores[i].name;
			freshLog << " ";
			freshLog << highScores[i].boardSize;
			freshLog << " ";
			freshLog << highScores[i].shipArea;
			freshLog << endl;
		}

		freshLog.close();
	}



}


void Game(Player &P1,Player &P2)
{
	float p1Moves = 0,p2Moves = 0,winnerMoves;
	Player winner,looser;
	while (true)
	{
		p1Moves = p1Moves + playing(P1,P2);
		if(P2.isDefeated())
		{
			winner = P1;
			looser = P2;
			winnerMoves = p1Moves;
			break;
		}
		p2Moves = p2Moves + playing(P2,P1);
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

	cout << "The winner is " << winner.getName() << endl << " with " << score << " points!";

	winner.giveScore(score);
	addToTop(winner);
}




int main()
{

	string p1Name,p2Name,boardFileName;

	cout << "PLAYER 1" << endl;
	cout << "Name: ";
	//cin >> p1Name;
	cout << "Board configuration file name: ";
	//cin >> boardFileName;
	//Player P1(p1Name,boardFileName);
	Player P1("simao","conf.tab");

	cout << "PLAYER 2" << endl;
	cout << "Name: ";
	//cin >> p2Name;
	cout << "Board configuration file name: ";
	//cin >> boardFileName;
	//Player P2(p2Name,boardFileName);
	Player P2("reis","conf.tab");
	firstToPlay(P1,P2);
	if(P1.getIndex() == 1)
		Game(P1,P2);
	else
		Game(P2,P1);

	 

	system("pause");




	return 0;
}