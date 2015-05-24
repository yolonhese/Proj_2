#include "Board.h"


class Player
{
	public:
		Player();
		Player(string playerName, string boardFilename);
		void showBoard() const; 
		Bomb getBomb(Position<char> bombTarget) const; 
		void attackBoard(const Bomb &b);
		void giveIndex(int number); // Apenas para definir quem é o primeiro a jogar
		bool isDefeated();
		string getName();
		int getBoardSize();
		Board getBoard();
		int getShipArea();
		void giveScore(float number);
		float getScore();
		int getIndex();
		friend ostream& operator<< (ostream &out, Player manoel);
	private:
		string name; 
		Board board;
		int index; //Indica se o é o primeiro o ou segundo a jogar (1 - primeiro, 2 - segundo)
		float score; //Caso seja vencedor a pontuação ficará guardada nesta variável
};