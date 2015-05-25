#include <iostream>
#include <string>
#include <vector>
#include <fstream>

template <typename T>
struct Position
{
	T lin, col;
};


class Bomb
{
public:
Bomb(Position<char> targetPosition, int numLines , int numColumns);
Position<char> getTargetPosition() const;
Position<int> convertPositionChartoInt(Position<char> position);
Position<char> convertPositionInttoChar(Position<int> position);
Position<char> randomizePosition(Position<char> position, int numLines , int numColumns);




void show() const; // shows the attributes of the bomb (for debugging)
private:
Position<char> targetPos_char;
char targetLine, targetColumn;
int maxLines, maxColumns;
};