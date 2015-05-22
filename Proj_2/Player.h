#include "Board.h"


class Player
{
	public:
		Player();
		Player(string playerName, string boardFilename);
		void showBoard() const; 
		Bomb getBomb(PositionChar bombTarget) const; 
		void attackBoard(const Bomb &b);
		void giveIndex(int number); // Apenas para definir quem é o primeiro a jogar
		bool isDefeated();
		string getName();
		int getBoardSize();
		int getShipArea();
		friend ostream& operator<< (ostream &out, Player manoel);
	private:
		string name; 
		Board board;
		int index;
};