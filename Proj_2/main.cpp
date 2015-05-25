#include <iostream>
#include <time.h>
#include <windows.h>
#include "Player.h"



using namespace std;


/*
columnCenter e lineCenter foram criadas com um prop�sito meramente est�tico
A primeira imprime linhas vazias at� +/- o centro da consola e a segunda imprime a string "s" no
centro da linha em que se encontra o cursor.
*/
void columnCenter()
{
	for(int  i = 0; i < 10;i++)
		cout << endl;
}
void lineCenter(string s)
{
	int l=s.size();
	int pos=(int)((80-l)/2);
	for(int i=0;i<pos;i++)
	cout<<" ";
 
	cout<<s;
}




struct topScore
			{
				float score;
				string name;
				int boardSize,shipArea;
			};


/*
"firstToPlay" determina aleat�riamente qual dos jogadores �
o player de index 1 (primeiro a jogar) e qual o jogador de index 2.
Imprime no fim da sua execu��o uma mensagem do ecr� qual dos dois � o primeiro.
*/
void firstToPlay(Player &a,Player &b)
{
	srand(time(NULL));
	int randomNumber = rand() %2 + 1;

	columnCenter();
	if (randomNumber == 1)
	{	
		a.giveIndex(1);
		b.giveIndex(2);
		lineCenter( a.getName() + " is the first one to play");
	}
	if (randomNumber == 2)
	{
		b.giveIndex(1);
		a.giveIndex(2);
		lineCenter( b.getName() + " is the first one to play");
	}

}

/*
	A fun��o "playing" corresponde a uma jogada em que o jogador "a" est� a atacar
	o jogador "b". Faz uso da fun��o "clock" para calcular o tempo que a jogada demora
	a ser executada. O tempo total � guardado na vari�vel "end" que � devolvida pela fun��o
	para que possa ser posteriormente calculada a pontua��o do jogador em "game".
	Em primeiro lugar � impresso na consola o tabuleiro de "b". De seguida a fun��o espera
	pela introdu��o das coordenadas para a cria��o da bomba "theBomb" que ir� ser enviada.
	Caso as coordenadas n�o estejam no formato [A-Z][a-z] em que z representa limite do tabuleiro
	que poder� ir at� Z/z, � apresentada uma mensagem de erro e requesitada uma nova introdu��o
	de valores at� que estes sejam v�lidos.
	Depois de validar as coordenadas inseridas, � criada a bomba, estando sujeita a desvios de 
	rota, e � atacado o tabuleiro de b.
*/
float playing(Player &a, Player &b)
{
	//neste cen�rio, "a" est� a atacar "b"
	float begin = clock(); //regista o in�cio da jogada
	Position<char> bombCoordinates;
	bool valid = 1;


	system("cls");
	columnCenter();
	lineCenter("GET READY");
	cout << endl;
	lineCenter(a.getName());
	Sleep(1500);
	do
	{
		char maxLin = b.getBoard().getMaxLine() + 65;
		char maxCol = b.getBoard().getMaxColumn() + 97;
		system("cls");
		cout << endl << endl;
		cout << b.getName() << "'S BOARD" << endl;
		
		cout << "COORDINATES [A - ";
		cout << maxLin;
		cout << "][a - ";
		cout << maxCol;
		cout << "]	";

		string typedCoordinates;
		cin >> typedCoordinates;
		/*
		Usando "c_str" transformamos a string "typedCoordinates" num array
		facilitando o acesso idividual a cada letra introduzida.
		*/
		bombCoordinates.lin = typedCoordinates.c_str()[0];
		bombCoordinates.col = typedCoordinates.c_str()[1];

		if((b.getBoard().getMaxLine() < int(bombCoordinates.lin) - 65) || (b.getBoard().getMaxColumn() < int(toupper(bombCoordinates.col)) - 65) || (bombCoordinates.lin < 65) || (bombCoordinates.lin > 90) || (bombCoordinates.col < 97) || (bombCoordinates.col > 122) ) 
		{
			valid = 0;
			system("cls");
			columnCenter();
			lineCenter("ERROR");
			cout << endl;
			lineCenter("Invalid coordinates");
			Sleep(1500);
		}
		
	}while (!valid);

	float end = (clock() - begin ) / (float) CLOCKS_PER_SEC; //guarda na variavel end o tempo decorrido at� ao fim da jogada


	Bomb theBomb(bombCoordinates, b.getBoard().getMaxLine(),b.getBoard().getMaxColumn());
	system("cls");
	columnCenter();
	lineCenter("BOMB FELLL IN");
	cout << endl << endl;
	lineCenter(" ");
	cout << theBomb.getTargetPosition().lin;
	cout << theBomb.getTargetPosition().col << endl;
	Sleep(1500);

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


/*
A fun��o "game" corresponde ao conjunto de todas as jogadas, sequenciais do jogo.
P1 � o primeiro a jogar. No final de cada jogada � verificado se o advers�rio
foi derrotado (isDefeated). Caso se verifique, o �ltimo a jogar � copiado
para a vari�vel winner e a soma dos seus tempos (retirada da soma de todos os 
retornos da fun��o "playing" de cada vez que o jogador fazia uma jogada) � guardada em 
"winnerMoves". No fim � calculado o score pela f�rmula  Moves * AreaOcupada / AreaTotal,
� impresso na consola o nome e a pontua��o do vencedor e o seu score � comparado com
o top ten de scores do jogo com "addToTop".
*/
void game(Player &P1,Player &P2)
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
	string score_str;
	score = winnerMoves * winner.getShipArea() / winner.getBoardSize();
	score_str = to_string(score);

	system("cls");
	columnCenter();
	lineCenter("WINNER");
	cout << endl;
	lineCenter(winner.getName());
	Sleep(1500);

	system("cls");
	columnCenter();
	lineCenter("SCORE");
	cout << endl;
	lineCenter(score_str);
	Sleep(1500);

	winner.giveScore(score);
	addToTop(winner);
}

int menu()
{
        string Menu[4] = {"Start Game", "Create Board", "TOP10", "Exit"};
        int pointer = 0;
       
        while(true)
        {
                system("cls");
               
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                lineCenter("Menu");
                cout<<endl<<endl;
               
                for (int i = 0; i < 4; ++i) //Trocar a cor para opcao selecionada
                {
                        if (i == pointer)
                        {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                                lineCenter(Menu[i]);
                                        cout << endl;
                        }
                        else
                        {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                                lineCenter(Menu[i]);
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
											//Este trecho corre quando selecionada a entrada "Start Game"
											string p1Name,p2Name,boardFileName;

											//Cria��o de P1
											system("cls");
											columnCenter();
											lineCenter("P1");
											Sleep(1500);

											system("cls");
											columnCenter();
											lineCenter("NAME");
											lineCenter(" ");
											cin >> p1Name;

											system("cls");
											columnCenter();
											lineCenter("BOARD FILE");
											cout << endl << endl;
											lineCenter(" ");
											cin >> boardFileName;

											/*As linhas seguintes verificam a exist�ncia do ficheiro escolhido pelo jogador.
											Caso n�o exista, � apresentada uma mensagem de erro e � requesitada um novo nome de
											ficheiro. Isto repete-se at� que o nome do ficheiro introduzido seja validado.
											*/
											ifstream isThere;
											isThere.open("board_files/" + boardFileName);
											while(!isThere.good())
											{
												isThere.close();
												system("cls");
												columnCenter();
												lineCenter("ERROR");
												cout << endl << endl;
												lineCenter( "The file you specified does not exist");
												Sleep(1500);
												system("cls");

												columnCenter();
												lineCenter("BOARD FILE");
												cout << endl << endl;
												lineCenter(" ");
												cin >> boardFileName;

												isThere.open("board_files/" + boardFileName);
											}
											isThere.close();

											Player P1(p1Name,boardFileName);

											//Cria��o de P2
											system("cls");
											columnCenter();
											lineCenter("P2");
											Sleep(1500);

											system("cls");
											columnCenter();
											lineCenter("NAME");
											lineCenter(" ");
											cin >> p2Name;
											/*
											Verifica se o nome escolhido por P2 � igual ao de P1.
											Caso seja apresenta uma mensagem de erro at� que seja
											introduzido um nome diferente.
											*/
											while (p2Name == p1Name)
											{
												system("cls");
												columnCenter();
												lineCenter("ERROR");
												cout << endl << endl;
												lineCenter("You must choose a different name from your opponent");
												Sleep(1500);
												system("cls");
												columnCenter();
												lineCenter("NAME");
												lineCenter(" ");
												cin >> p2Name;
											}

											system("cls");
											columnCenter();
											lineCenter("BOARD FILE");
											cout << endl << endl;
											lineCenter(" ");
											cin >> boardFileName;

											/*As linhas seguintes verificam a exist�ncia do ficheiro escolhido pelo jogador.
											Caso n�o exista, � apresentada uma mensagem de erro e � requesitada um novo nome de
											ficheiro. Isto repete-se at� que o nome do ficheiro introduzido seja validado.								
											*/
											isThere.open("board_files/" + boardFileName);
											while(!isThere.good())
											{
												isThere.close();
												system("cls");
												columnCenter();
												lineCenter("ERROR");
												cout << endl << endl;
												lineCenter( "The file you specified does not exist");
												Sleep(1500);
												system("cls");

												columnCenter();
												lineCenter("BOARD FILE");
												cout << endl << endl;
												lineCenter(" ");
												cin >> boardFileName;

												isThere.open("board_files/" + boardFileName);
											}
											isThere.close();

											Player P2(p2Name,boardFileName);

											system("cls");
											columnCenter();
											lineCenter("GAME ON!");
											Sleep(1500);
											system("cls");
											
											//decide quem ser� o primeiro a jogar
											firstToPlay(P1,P2);
											Sleep(1500);
											system("cls");

											//inicia o jogo tendo em conta a ordem dos players (gravada em index)
											if(P1.getIndex() == 1)
												game(P1,P2);
											else
												game(P2,P1);


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




int main()
{

	
menu();
	

	return 0;
}