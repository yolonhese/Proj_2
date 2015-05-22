#include "Bomb.h"

using namespace std;





class Ship
{
	public:
		Ship(char symbol, PositionChar position, char orientation, unsigned int size, unsigned int color);
		PositionInt convertPositionChartoInt(PositionChar position);
		PositionChar convertPositionInttoChar(PositionInt position);
		void setPosition(PositionChar position,char orientation);
		bool move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax); // moves the boat (SEE NOTES)
		bool moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax); // moves the ship randomly
		bool attack(size_t partNumber); //partNumber = {0,1,�, size-1}
		bool isDestroyed() const; // checks whether the ship is destroyed
		void show() const; // shows the attributes of the ship (for debugging)
		PositionChar getPosition() const;
		char getOrientation() const;
		unsigned int getSize() const;
		char getSymbol() const;
		unsigned int getColor() const;
	private:
		char symbol; // 'P' = "porta-avi�es"; 'F' = "fragata"; � (portuguese names)
		PositionChar posChar; // coordinates of the upper left corner of the ship
		char orientation; // 'H' = horizontal; 'V' = vertical
		unsigned int size; // number os cells occupied by the ship, on the board
		unsigned int color; // color code: o=BLACK, 1=BLUE, � (see annex of 1st proj.)
		string status;
};