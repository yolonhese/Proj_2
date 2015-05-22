#include <iostream>
#include "Ship.h"
#include <vector>


class Board
{
	public:
		Board();
		Board(const string &filename); // loads board from file 'filename'
		bool putShip(const Ship &s); // adds ship to the board, if possible
		void moveShips(); // tries to randmonly move all the ships of the fleet
		bool attack(const Bomb &b);
		void display() const; // displays the colored board during the game
		void fillBoard(); //fills the board with the index numbers of the "ships" vector
		vector<Ship> getShips();
		int getSize();
		int getShipArea();
		friend ostream& operator<< (ostream &out, Board &toDisplay);
	private:
		int numLines, numColumns; 
		vector<Ship> ships; 
		vector<vector<int>> board;
};