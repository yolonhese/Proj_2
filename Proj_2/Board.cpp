#include "Board.h"
#include <algorithm>
#include <iomanip>
#include <windows.h>

/*
Semelhantes às duas primeiras funções definidas no main.cpp
Têm como função auxiliar na impressão do tabuleiro. A sua finalidade é apenas
estética.
*/
void columnCenterBoard()
{
	for(int  i = 0; i < 4;i++)
		cout << endl;
}

/*
	Construtor default. Permitea criação de variáveis do tipo Board sem qualquer tipo
	de argumentos.
*/
Board::Board()
{

}

/*
	Contrutor da classe Board. Recebe como argumento um ficheiro
	criado pelo primeiro trabalho prático, modificado. Abre o ficheiro
	em modo de leitura e recolhe a infomação relativa aos navios(tamanho,tipo,posição...)
	e relativa ao tamanho do tabuleiro.
*/
Board::Board(const string &filename)
{
	ifstream ficheiroconfig;							// Abre o ficheiro com as configurações com o 
	ficheiroconfig.open("board_files/" + filename);		// nome gravado em "nome_ficheiro"
														// para leitura em "ficheiroconfig".

	

	string descarta,linesStr,columnsStr;	
	getline(ficheiroconfig, linesStr, ' '); 
	getline(ficheiroconfig, descarta, ' ');
	getline(ficheiroconfig, columnsStr);


	numLines = atoi(linesStr.c_str());	
	numColumns = atoi(columnsStr.c_str());	



	board.resize(numLines);				// Redimensiona os vectores que constituem a estrutura
	for (int i = 0; i < numLines; i++)	// a ser impressa no ecrã que traduz o tabuleiro 
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
		sizeInt = atoi(size.c_str());			
		colorInt = atoi(color.c_str());			

		Position<char> position;
		position.lin = posChar.c_str()[0];
		position.col = posChar.c_str()[1];

		Ship defaultShip(symbol.c_str()[0],position,orientation.c_str()[0],sizeInt,colorInt);

		ships.push_back(defaultShip);
	}

	ficheiroconfig.close();	

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



/*
	"fillBoard" é como uma função refresh. Começa por limpar o tabuleiro preenchendo-o com
	 -1 (mar) e, de seguida coloca cada um dos navios presentes no vector "ships". "type"
	 é um indicatvo para a posição do navio no vetor e "block" representa o número da parcela do navio
	 Eg. PPP é composto por 3 parcelas
*/
void Board::fillBoard()
{
	for(unsigned int i = 0; i < board.size(); i++)
	{
		for(unsigned int ii = 0; ii < board[i].size(); ii++)
		{
			board[i][ii].type = -1;
			board[i][ii].block = 0;
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
				board[shipPostion.lin - 1][shipPostion.col + z - 1].block = z;
			}
		if(ships[i].getOrientation() == 'V')
			for(unsigned int w = 0; w < ships[i].getSize(); w++)
			{
				board[shipPostion.lin + w - 1][shipPostion.col - 1].type = i;
				board[shipPostion.lin + w - 1][shipPostion.col - 1].block = w;

			}
	}
}


/*
	Grande parte de "putShip" passa por verificar se o navio "s", tendo em conta as suas
	características pode ou não ser colocado no tabuleiro. Para isso verifica-se se a posição
	de onde este se extende está fora dos limites. De seguida verifica-se se excede o numero 
	de linhas ou colunas máximo do tabuleiro ou se trespassa uma posição já ocupada por outra
	embarcação, tendo em conta se está na horizontal ou na vertical. Caso esteja em posição ilegal,
	a função retorna 0 caso contrário, é feito o push_back para o vector "ships" e chama-se a função
	refresh "fillBoard()" que atualiza o tabuleiro já com o novo navio e retorna 1.
*/
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

		
			ships.push_back(s);
			fillBoard();
			return 1;
}


/*
	"moveShips" tenta mover todos os navios do tabuleiro um a um. Para podermos testar a colocação do navio
	em todo o espaço disponivel inclusivé o espaço ocupado anteriormente pelo próprio temos de o retirar do vector
	"ships" e fazer um refresh ao tabuleiro com "fillboard". Começamos pelo último navio n vector e usamos a função
	"pop_back". No final da iteração para o primeiro navio rodamos o vetor de modo a podermos fazer "pop_back" do navio seguinte.
	Repete-se o processo até que voltemos à posição inicial. 
	 Uma vez que por vezes o processo de colocação aleatória do navio é demasiado demorado, limitamos cada um a 20 tentativas após
	 as quais o navio fica na posição original.
	*/
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

/*
	A função attack  tal como o nome indica, recebe uma bomba como argumento procura no tabuleiro o barco a o bloco a atacar e 
	retorna o valor da função "attack" de Ship. Caso a posição a ser atacada já o tenha sido, retorna 0, caso contrário retorna 1.
*/
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

	return ships[shipIndex].attack(partNumber);

}


/*
	Imprime o tabuleiro na consola. Imprime as coordenadas a uma cor diferente os navios com a cor correspondente e 
	e os blocos já destruídos de cada navio a preto para facilitar a distinção.
*/
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
				if(islower( status.c_str()[board[i][ii].block] ) )
				{
					setColor(BLACK, LIGHTGRAY);
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


//Permite alterar o vector "ships" fora da classe. É usada quando queremos fazer desaparecer os navios depois de destruidos.
void Board::giveShips(vector<Ship> s)
{
	ships = s;
}




/*
Aqui fazemos o overloading do operador "<<"
Uma vez que a única função que imprime no ecrã é 
a função "display", é tambem a úica a ser chamada. */
ostream& operator<< (ostream &out, Board &toDisplay)
{
	toDisplay.display();
	return out;

}




/*
	Todas as funções que se seguem limitam-se a retornar valores
	de variáveis privadas.
*/
vector<Ship> Board::getShips()
{
	return ships;
}

/*
Retorna a área do tabuleiro.
*/
int Board::getSize()
{
	return numLines * numColumns;
}

/*
A função retorna a área total ocupada pelos navios no tabuleiro.
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







