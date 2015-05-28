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
Bomb(Position<char> targetPosition, int numLines , int numColumns); //construtor

Position<int> convertPositionChartoInt(Position<char> position);//auxiliar
Position<char> convertPositionInttoChar(Position<int> position);//auxiliar

Position<char> randomizePosition(Position<char> position, int numLines , int numColumns);//atribui à bomba uma posição random no raio de uma célula


Position<char> getTargetPosition() const;//retorna targetPos_char



private:
Position<char> targetPos_char;
char targetLine, targetColumn;
int maxLines, maxColumns;
};