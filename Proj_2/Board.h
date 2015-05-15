#include <iostream>
#include "Ship.h"


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
	private:
		int numLines, numColumns,area; // redundant info …
		vector<Ship> ships; // ships that are placed on the board
		vector<vector<int>> board; // each element indicates
		// the index of a ship in the 'ships' vector
		// (in the range 0..ships.size()-1) ;
};