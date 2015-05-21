#include <iostream>
#include <string>
#include <vector>
#include <fstream>

/*template <typename T>
struct PositionChar // to store a board position in char format
{ // example: 'B','d'
	T lin, col; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};*/

struct PositionChar // to store a board position in char format
{ // example: 'B','d'
	char lin, col; // ranges: lin - ['A'..'Z']; col - ['a'..'z']
};
//-----------------------------------------------------------------------------
struct PositionInt // to store a board position in unsig. integer format
{ // example: 7,0
	unsigned int lin, col; // ranges: lin - [0..26]; col - [0..26]
};
template <typename T> T sum(T a) {
	return a*2;
}
class Bomb
{
public:
Bomb(PositionChar/*<char>*/ targetPosition);
PositionChar getTargetPosition() const;
PositionInt convertPositionChartoInt(PositionChar position);
PositionChar convertPositionInttoChar(PositionInt position);
PositionChar randomizePosition(PositionChar position);




void show() const; // shows the attributes of the bomb (for debugging)
private:
PositionChar targetPos_char;
char targetLine, targetColumn;
};