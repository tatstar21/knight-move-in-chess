#include <iostream>

const int MAX_AVAILABLE_MOVES = 8;
const int AMAUNT_CELLS = 64;
const int FIRST_NUMBER_OF_BOARD = 1;
const int LAST_NUMBER_OF_BOARD = 8;
const char FIRST_LETTER_OF_BOARD = 'A';
const char LAST_LETTER_OF_BOARD = 'H';
const int FLAG = -1;

struct Cell
{
	char letter;
	int number;

};

void fillArrayWithAvailableMoves(
	Cell currentPositionOfHorse,
	Cell emptyArrayForAvailableMoves[MAX_AVAILABLE_MOVES],
	Cell arrayOfPassedCells[AMAUNT_CELLS]
);

Cell makeMove(
	Cell arrayWithAvailableMoves[MAX_AVAILABLE_MOVES],
	Cell arrayPassedOfCells[AMAUNT_CELLS]
);

void printPassedMoves(Cell arrayOfPassedCells[AMAUNT_CELLS], int indexOfLastPassedCell);

void horseMove(
	Cell currentPositionOfHorse, 
	Cell arrayOfPassedCells[AMAUNT_CELLS], 
	int indexOfLastPassedCell
);

int main()
{
	setlocale(LC_ALL, "RU");
	std::cout << "Введите координаты клетки поля "
		"(число от 1 до 8 и букву от \"A\" до \"Н\"(латиница)) ";
	int number;
	std::cin >> number;
	char letter;
	std::cin >> letter;
	if (number < FIRST_NUMBER_OF_BOARD || number > LAST_NUMBER_OF_BOARD) {
		std::cerr << "Вы ввели число меньше 1 или больше 8 !\n";
		return -1;
	}
	if (letter < FIRST_LETTER_OF_BOARD || letter > LAST_LETTER_OF_BOARD) {
		std::cerr << "Вы ввели букву не вошедшую в диапазон от \"A\" до \"Н\" !\n";
		return -2;
	}

	Cell currentPositionOfHorse;
	currentPositionOfHorse.letter = letter;
	currentPositionOfHorse.number = number;

	Cell arrayOfPassedCells[AMAUNT_CELLS];
	int indexOfLastPassedCell = 0;

	arrayOfPassedCells[indexOfLastPassedCell].letter = currentPositionOfHorse.letter;
	arrayOfPassedCells[indexOfLastPassedCell].number = currentPositionOfHorse.number;

	indexOfLastPassedCell++;

	horseMove(currentPositionOfHorse, arrayOfPassedCells, indexOfLastPassedCell);

}

void fillArrayWithAvailableMoves(
	Cell currentPositionOfHorse,
	Cell emptyArrayForAvailableMoves[MAX_AVAILABLE_MOVES],
	Cell arrayOfPassedCells[AMAUNT_CELLS]
) {

	static int diffArray[MAX_AVAILABLE_MOVES][2] = {
		{-1, -2}, {+1, -2}, {-2, -1}, {+2, -1},
		{-2, +1}, {+2, +1}, {-1, +2}, {+1, +2}
	};
	for (int ii = 0; ii < MAX_AVAILABLE_MOVES; ii++) {
		emptyArrayForAvailableMoves[ii].letter =
			currentPositionOfHorse.letter + diffArray[ii][0];
		emptyArrayForAvailableMoves[ii].number =
			currentPositionOfHorse.number + diffArray[ii][1];
	}

	for (int ii = 0; ii < MAX_AVAILABLE_MOVES; ii++) {
		if (emptyArrayForAvailableMoves[ii].number > LAST_NUMBER_OF_BOARD ||
			emptyArrayForAvailableMoves[ii].number < FIRST_NUMBER_OF_BOARD ||
			emptyArrayForAvailableMoves[ii].letter < FIRST_LETTER_OF_BOARD ||
			emptyArrayForAvailableMoves[ii].letter > LAST_LETTER_OF_BOARD) {

			emptyArrayForAvailableMoves[ii].number = FLAG;
			emptyArrayForAvailableMoves[ii].letter = FLAG;
		}
	}

	for (int ii = 0; ii < MAX_AVAILABLE_MOVES; ii++) {
		for (int jj = 0; jj < AMAUNT_CELLS; jj++) {
			if (arrayOfPassedCells[jj].letter == emptyArrayForAvailableMoves[ii].letter &&
				arrayOfPassedCells[jj].number == emptyArrayForAvailableMoves[ii].number) {

				emptyArrayForAvailableMoves[ii].number = FLAG;
				emptyArrayForAvailableMoves[ii].letter = FLAG;
			}

		}

	}
}

Cell makeMove(
	Cell arrayWithAvailableMoves[MAX_AVAILABLE_MOVES],
	Cell arrayPassedOfCells[AMAUNT_CELLS]
) {

	Cell availableMovesForNextMove[MAX_AVAILABLE_MOVES];
	int minCounter = INT8_MAX;
	Cell cellWithMinumumAvailableMoves;
	cellWithMinumumAvailableMoves.number = FLAG;
	cellWithMinumumAvailableMoves.letter = FLAG;

	for (int ii = 0; ii < MAX_AVAILABLE_MOVES; ii++) {
		if (arrayWithAvailableMoves[ii].number == FLAG) {
			continue;
		}
		int availebleMovesCounter = 0;
		fillArrayWithAvailableMoves(arrayWithAvailableMoves[ii], availableMovesForNextMove, arrayPassedOfCells);
		for (int jj = 0; jj < MAX_AVAILABLE_MOVES; jj++) {

			if (availableMovesForNextMove[jj].number != FLAG) {
				availebleMovesCounter++;
			}
		}
		if (availebleMovesCounter < minCounter) {
			minCounter = availebleMovesCounter;
			cellWithMinumumAvailableMoves = arrayWithAvailableMoves[ii];
		}
	}
	return cellWithMinumumAvailableMoves;
}


void printPassedMoves(Cell arrayOfPassedCells[AMAUNT_CELLS], int indexOfLastPassedCell) {

	std::cout << "Путь коня: \n";
	for (int ii = 0; ii < indexOfLastPassedCell - 1; ii++) {

		std::cout << arrayOfPassedCells[ii].number
			<< arrayOfPassedCells[ii].letter << "->";

		if ((ii + 1) % 8 == 0)std::cout << "\n";

	}
	std::cout << arrayOfPassedCells[indexOfLastPassedCell - 1].number
		<< arrayOfPassedCells[indexOfLastPassedCell - 1].letter;
}

void horseMove(Cell currentPositionOfHorse, Cell arrayOfPassedCells[AMAUNT_CELLS], int indexOfLastPassedCell) {

	Cell availableMoves[MAX_AVAILABLE_MOVES];

	fillArrayWithAvailableMoves(currentPositionOfHorse, availableMoves, arrayOfPassedCells);
	currentPositionOfHorse = makeMove(availableMoves, arrayOfPassedCells);

	if (currentPositionOfHorse.number == FLAG) {
		printPassedMoves(arrayOfPassedCells, indexOfLastPassedCell);
		return;
	}

	arrayOfPassedCells[indexOfLastPassedCell].letter = currentPositionOfHorse.letter;
	arrayOfPassedCells[indexOfLastPassedCell].number = currentPositionOfHorse.number;
	indexOfLastPassedCell++;

	horseMove(currentPositionOfHorse, arrayOfPassedCells, indexOfLastPassedCell);

}