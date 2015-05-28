#include <iostream>
#include "Ship.h"
#include <vector>

/*
	Esta talvez tenha sido a altera��o mais significativa
	� estrutura inicial do projecto. A struct "shipsOnBoard"
	foi criada com o intuito de facilitar a impress�o do 
	tabuleiro, mais concretamente dos navios colocados no
	tabuleiro depois de terem sido atingidos. "type" corresponde
	, caso -1, ao mar caso outro valor >=0, ao navio que se encontra
	nessa posi��o no vector "ships". "block" corresponde ao bloco
	do navio em quest�o. Eg. PpP, o segundo bloco foi atingido.
*/
struct shipsOnBoard
{
	int type, block;
};

class Board
{
	public:
		Board();
		Board(const string &filename);

		bool putShip(const Ship &s); 
		void moveShips(); 
		bool attack(const Bomb &b);
		void fillBoard();
		void giveShips(vector<Ship> s);
		
		void display() const; //imprime o tabuleiro

		//retorno de vari�veis private
		int getSize();
		int getShipArea();
		int getMaxLine();
		int getMaxColumn();
		vector<Ship> getShips();


		friend ostream& operator<< (ostream &out, Board &toDisplay); //overload do operador "<<"

	private:
		int numLines, numColumns; 
		vector<Ship> ships; 
		vector<vector<shipsOnBoard>> board;
};