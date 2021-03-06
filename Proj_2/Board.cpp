#include "Board.h"
#include <algorithm>
#include <iomanip>
#include <windows.h>

/*
Semelhantes �s duas primeiras fun��es definidas no main.cpp
T�m como fun��o auxiliar na impress�o do tabuleiro. A sua finalidade � apenas
est�tica.
*/
void columnCenterBoard()
{
	for(int  i = 0; i < 4;i++)
		cout << endl;
}
void lineCenterBoard(int colMax)
{
	
	int pos=(int)((80 - colMax)/2);
	for(int i=0;i<pos;i++)
	cout<<" ";
 
}

Board::Board()
{

}


Board::Board(const string &filename)
{
	ifstream ficheiroconfig;							// Abre o ficheiro com as configura��es com o 
	ficheiroconfig.open("board_files/" + filename);		// nome gravado em "nome_ficheiro"
														// para leitura em "ficheiroconfig".

	

	string descarta,linesStr,columnsStr;	
	getline(ficheiroconfig, linesStr, ' '); 
	getline(ficheiroconfig, descarta, ' ');
	getline(ficheiroconfig, columnsStr);


	numLines = atoi(linesStr.c_str());	//".c_str()" passa uma string para um array de chars.
	numColumns = atoi(columnsStr.c_str());	// A fun��o "atoi" retorna um inteiro a partir de um array de chars



	board.resize(numLines);				// Redimensiona os vectores que constituem a estrutura
	for (int i = 0; i < numLines; i++)	// a ser impressa no ecr� que traduz o tabuleiro 
		board[i].resize(numColumns);



	string orientation,posChar,symbol,color,size;

	while (!ficheiroconfig.eof())						
	{	
		getline(ficheiroconfig, symbol, ' ');				
		getline(ficheiroconfig, size, ' ');						
		getline(ficheiroconfig, posChar, ' ');
		getline(ficheiroconfig, orientation, ' ');		
		getline(ficheiroconfig, color);				

		unsigned int sizeInt,colorInt;
		sizeInt = atoi(size.c_str());			// Mais uma vez, convertemos os n�meros (que est�o em formato
		colorInt = atoi(color.c_str());			// "string") para o formato "inteiro"

		Position<char> position;
		position.lin = posChar.c_str()[0];
		position.col = posChar.c_str()[1];

		Ship defaultShip(symbol.c_str()[0],position,orientation.c_str()[0],sizeInt,colorInt);

		ships.push_back(defaultShip);
	}

	ficheiroconfig.close();	 //J� nao iremos necessitar mais do ficheiro de configura��o. Fecha-se o mesmo.

	fillBoard();

}


#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

void setColor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); if (background_color == BLACK)
	SetConsoleTextAttribute(hCon, color); else
	SetConsoleTextAttribute(hCon, color | background_color*16+color);
} 



void Board::fillBoard()
{
	for(unsigned int i = 0; i < board.size(); i++)
	{
		for(unsigned int ii = 0; ii < board[i].size(); ii++)
		{
			board[i][ii].type = -1;
			board[i][ii].index = 0;
		}

	}

	for(unsigned int i = 0; i < ships.size(); i++)
	{
		Position<char> shipPositionChar = ships[i].getPosition();
		Position<int> shipPostion;
		shipPostion.lin = int(shipPositionChar.lin) - 64;
		shipPostion.col = int(toupper(shipPositionChar.col)) -64; 

		if(ships[i].getOrientation() == 'H')
			for(unsigned int z = 0; z < ships[i].getSize(); z++)
			{
				board[shipPostion.lin - 1][shipPostion.col + z - 1].type = i;
				board[shipPostion.lin - 1][shipPostion.col + z - 1].index = z;
			}
		if(ships[i].getOrientation() == 'V')
			for(unsigned int w = 0; w < ships[i].getSize(); w++)
			{
				board[shipPostion.lin + w - 1][shipPostion.col - 1].type = i;
				board[shipPostion.lin + w - 1][shipPostion.col - 1].index = w;

			}
	}
}

bool Board::putShip(const Ship &s)
{
	Position<char> shipPositionChar = s.getPosition();
	Position<int> shipPostion;
		shipPostion.lin = int(shipPositionChar.lin) - 65;
		shipPostion.col = int(toupper(shipPositionChar.col)) -65;

		if(shipPostion.lin > numLines || shipPostion.col > numColumns)
			return 0;

		if(s.getOrientation() == 'H')
		{
			if(shipPostion.col + s.getSize()  > numColumns)
				return 0;
			for(unsigned int z = 0; z < s.getSize(); z++)
			{
				if(board[shipPostion.lin][shipPostion.col + z].type != -1)
					return 0;
			}
		}

		if(s.getOrientation() == 'V')
		{
			if(shipPostion.lin + s.getSize()  > numLines)
				return 0;

			for(unsigned int z = 0; z < s.getSize(); z++)
			{
				if(board[shipPostion.lin + z][shipPostion.col].type != -1)
					return 0;
			}
		}

			/*		Caso o navio "s" n�o esteja numa posi��o inv�lida (fora dos limites do tabuleiro ou
			sobreposto em rela��o a outro navio j� colocado) adiciona-se o mesmo ao vetor "ships"
			e � chamada a fun��o "fillboard" para que seja feita a atualiza��o do vetor de vetores
			"boards" em rela��o a "ships". Na pr�tica, o index do novo navio, "s" � adicionado nas posi��es
			corretas em "boards"						*/
			ships.push_back(s);
			fillBoard();
			return 1;
}

void Board::moveShips()
{
	for(int i = 0;i < ships.size(); i++)
	{
		rotate(ships.begin(),ships.begin()+1,ships.end());

		Ship defaultShip = ships[ships.size() - 1], backupShip = defaultShip;
		
		ships.pop_back();
		fillBoard();

		int z = 20;
		do
		{
			defaultShip = backupShip;
			defaultShip.moveRand(1 , 1 , numLines , numColumns);
			if (putShip(defaultShip))
				break;
			z--;
		} while (z >= 0);
		if(z == -1)
		{
			ships.push_back(backupShip);
			fillBoard();
		}

	}
}

bool Board::attack(const Bomb &b)
{
	Position<int> impactPos,shipPos;
	int temporary;

	impactPos.lin =	int(b.getTargetPosition().lin) - 65;
	impactPos.col =	int(b.getTargetPosition().col) - 97;

	int partNumber,shipIndex;
	shipIndex = board[impactPos.lin][impactPos.col].type;
	

	if(board[impactPos.lin][impactPos.col].type == -1)
		return 0;

	shipPos.lin = int(ships[shipIndex].getPosition().lin) - 65;
	shipPos.col = int(ships[shipIndex].getPosition().col) - 97;



	if(ships[shipIndex].getOrientation() == 'H')
		partNumber = (impactPos.col - shipPos.col) + 1;

	if(ships[shipIndex].getOrientation() == 'V')
		partNumber = (impactPos.lin - shipPos.lin) + 1;

	ships[shipIndex].attack(partNumber);
	return 1;
}

void Board::display() const
{
	columnCenterBoard();

	cout << setw(2);
	cout << ' ';
	
	//lineCenterBoard(numLines);
	setColor(YELLOW, BLUE);
	char letter = 97;


	for (int i = 0; i < numColumns; i++)
	{
		cout << setw(2);
		cout << letter;
		letter++;
	}

	letter = 65;

	cout << endl;

	setColor(WHITE, BLACK);

	for (int i = 0; i < numLines; i++)
	{
		//lineCenterBoard(numLines);
		setColor(YELLOW, BLUE);
		cout << setw(2);
		cout << letter;
		letter++;

		for (int ii = 0; ii < numColumns; ii++)
		{
			if(board[i][ii].type == -1)
			{
				setColor(BLUE,LIGHTGRAY);
				cout << setw(2);
				cout << '.';
			}
			else
			{
				Ship shipToPrint = ships[board[i][ii].type] ;
				string status;
				char loweredSymbol;
				setColor(shipToPrint.getColor(), LIGHTGRAY);
				status = shipToPrint.getStatus();
				cout << setw(2);
				if(islower( status.c_str()[board[i][ii].index] ) )
				{
					loweredSymbol = tolower( ships[board[i][ii].type].getSymbol() ) ;
					cout << loweredSymbol;
				}

					
				else
					cout << ships[board[i][ii].type].getSymbol() ;
			}

		}

		
		setColor(WHITE, BLACK);
		cout << endl;
	}



}

/*
"getShips" retorna o vector de navios colocados no tabuleiro
*/
vector<Ship> Board::getShips()
{
	return ships;
}

/*
Retorna a �rea do tabuleiro.
*/
int Board::getSize()
{
	return numLines * numColumns;
}

/*
A fun��o retorna a �rea total ocupada pelos navios no tabuleiro.
Para chegar ao resultado total soma em "totalArea" o tamanho de todos os navios no vetor.
*/
int Board::getShipArea()
{
	int totalArea = 0;
	for(int i = 0; i < ships.size(); i++)
	{
		totalArea = totalArea + ships[i].getSize();
	}

	return totalArea;

}

int Board::getMaxLine()
{
	return numLines - 1;
}

int Board::getMaxColumn()
{
	return numColumns - 1;
}

void Board::changeStatus(int shipPos, string newStatus)
{
	ships[shipPos].giveStatus(newStatus);

}






/*
Aqui fazemos o overloading do operador "<<"
Uma vez que a �nica fun��o que imprime no ecr� � 
a fun��o "display", � tambem a �ica a ser chamada. */
ostream& operator<< (ostream &out, Board &toDisplay)
{
	toDisplay.display();
	return out;

}


