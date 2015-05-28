#include "Bomb.h"

using namespace std;





class Ship
{
	public:
		Ship(char symbol, Position<char> position, char orientation, unsigned int size, unsigned int color); //construtor da classe
		
		
		Position<int> convertPositionChartoInt(Position<char> position);
		Position<char> convertPositionInttoChar(Position<int> position);
		
		
		void setPosition(Position<char> position,char orientation);
		bool move(char direction, bool rotate, unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax);
		bool moveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax); 
		

		bool attack(size_t partNumber); 
		bool isDestroyed() const; 

		

		//retorno de variáveis private
		Position<char> getPosition() const;
		char getOrientation() const;
		unsigned int getSize() const;
		char getSymbol() const;
		unsigned int getColor() const;
		string getStatus();

	private:
		char symbol; 
		Position<char> posChar; 
		char orientation; 
		unsigned int size; 
		unsigned int color; 
		string status;
};