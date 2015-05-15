#include "Board.h"
#include <algorithm>

Board::Board(const string &filename)
{
	ifstream ficheiroconfig;				// Abre o ficheiro com as configurações com o 
	ficheiroconfig.open(filename);		// nome gravado em "nome_ficheiro"
											// para leitura em "ficheiroconfig".

	string descarta,linesStr,columnsStr;	 // Lê a primeira linha do ficheiro até encontrar um espaço
	getline(ficheiroconfig, descarta, ' ');  // descarta tudo o que está no meio guardando o contúdo na 
	getline(ficheiroconfig, linesStr, ' '); // variável do tipo string "descarta". Depois do primeiro espaço
	getline(ficheiroconfig, descarta, ' ');  // guarda o primeiro número do ficheiro em "linhasstr", volta a descartar
	getline(ficheiroconfig, columnsStr);     // o que está no meio e guarda o último número em "colunasstr"


	numLines = atoi(linesStr.c_str());	//".c_str()" passa uma string para um array de chars.
	numColumns = atoi(columnsStr.c_str());	// A função "atoi" retorna um inteiro a partir de um array de chars
	area = numColumns * numLines;


	board.resize(numLines + 1);				// Redimensiona os vectores que constituem a estrutura
	for (int i = 0; i < numLines; i++)	// a ser impressa no ecrã que traduz o tabuleiro 
		board[i].resize(numColumns);	// Adiciona uma linha/coluna extra para as coordenadas



	string orientation,posChar,symbol,color,size;

	while (!ficheiroconfig.eof())						//Lê todas as linhas até ao fim do ficheiro
	{	
		getline(ficheiroconfig, symbol, ' ');		// Usamos o mesmo processo
		getline(ficheiroconfig, descarta, ' ');			// mas desta vez com o objectivo de ler as especificações
		getline(ficheiroconfig, size, ' ');		// dos navios descritos no ficheiro de configuração.
	    getline(ficheiroconfig, descarta, ' ');			//			
		getline(ficheiroconfig, posChar, ' ');//
		getline(ficheiroconfig, descarta, ' ');			//
		getline(ficheiroconfig, orientation, ' ');		//
		getline(ficheiroconfig, descarta, ' ');			//
		getline(ficheiroconfig, color);				//

		unsigned int sizeInt,colorInt;
		sizeInt = atoi(size.c_str());			// Mais uma vez, convertemos os números (que estão em formato
		colorInt = atoi(color.c_str());			// "string") para o formato "inteiro"

		PositionChar position;
		position.lin = posChar.c_str[0];
		position.col = posChar.c_str[1];

		Ship defaultShip(symbol.c_str[0],position,orientation.c_str[0],sizeInt,colorInt);

		ships.push_back(defaultShip);
	}

	ficheiroconfig.close();	 //Já nao iremos necessitar mais do ficheiro de configuração. Fecha-se o mesmo.

	fillBoard;
}

void Board::fillBoard()
{
	for(int i = 0; i < board.size; i++)
	{
		for(int ii = 0; ii < board[i].size(); ii++)
		{
			board[i][ii] = -1;
		}

	}

	for(int i = 0; i < ships.size(); i++)
	{
		PositionChar shipPositionChar = ships[i].getPosition;
		PositionInt shipPostion;
		shipPostion.lin = int(shipPositionChar.lin) - 64;
		shipPostion.col = int(toupper(shipPositionChar.col)) -64; 

		if(ships[i].getOrientation == 'H')
			for(unsigned int z = 0; z < ships[i].getSize; z++)
			{
				board[shipPostion.lin][shipPostion.col + z] = i;
			}
		else
			for(unsigned int z = 0; z < ships[i].getSize; z++)
			{
				board[shipPostion.lin + z][shipPostion.col] = i;
			}
	}
}

bool Board::putShip(const Ship &s)
{
	PositionChar shipPositionChar = s.getPosition;
	PositionInt shipPostion;
		shipPostion.lin = int(shipPositionChar.lin) - 64;
		shipPostion.col = int(toupper(shipPositionChar.col)) -64;

		if(shipPostion.lin > numLines || shipPostion.col > numColumns)
			return 0;

		if(s.getOrientation == 'H')
			if(shipPostion.col + numColumns - 1 > numColumns)
				return 0;
			for(unsigned int z = 0; z < s.getSize; z++)
			{
				if(board[shipPostion.lin][shipPostion.col + z] != -1)
					return 0;
			}
		if(s.getOrientation == 'V')
			if(shipPostion.lin + numLines - 1 > numLines)
				return 0;
			for(unsigned int z = 0; z < s.getSize; z++)
			{
				if(board[shipPostion.lin + z][shipPostion.col] != -1)
					return 0;
			}

			/*		Caso o navio "s" não esteja numa posição inválida (fora dos limites do tabuleiro ou
			sobreposto em relação a outro navio já colocado) adiciona-se o mesmo ao vetor "ships"
			e é chamada a função "fillboard" para que seja feita a atualização do vetor de vetores
			"boards" em relação a "ships". Na prática, o index do novo navio, "s" é adicionado nas posições
			corretas em "boards"						*/
			ships.push_back(s);
			fillBoard;
			return 1;
}

void Board::moveShips()
{
	for(int i = 0;i < ships.size; i++)
	{
		rotate(ships.begin(),ships.begin()+1,ships.end());

		Ship defaultShip = ships[ships.size() - 1];
		
		ships.pop_back();
		fillBoard;

		do
		{
			defaultShip.moveRand;
		} while (!putShip(defaultShip));

	}
}

bool Board::attack(const Bomb &b)
{
	PositionInt impactPos,shipPos;
	impactPos.lin = int(b.getTargetPosition().lin) - 64;
	impactPos.col = int(toupper(b.getTargetPosition().col)) -64;

	int partNumber,shipIndex;
	shipIndex = board[impactPos.lin][impactPos.col];
	shipPos.lin = int(ships[shipIndex].getPosition().lin) - 64;
	shipPos.col = int(toupper(ships[shipIndex].getPosition().col)) -64;

	

	if(board[impactPos.lin][impactPos.col] == -1)
		return 0;



	if(ships[shipIndex].getOrientation() == 'H')
		partNumber = (impactPos.col - shipPos.col) + 1;

	if(ships[shipIndex].getOrientation() == 'V')
		partNumber = (impactPos.lin - shipPos.lin) + 1;

	ships[shipIndex].attack(partNumber);
	return 1;
}

