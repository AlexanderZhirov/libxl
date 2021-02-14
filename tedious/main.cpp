#include <iostream>
#include "bdo.hpp"
#include "parse_args.hpp"

using namespace libxl;

int main(int argc, char *argv[])
{
	args::settings parameters;
	args::parse_args(argc, argv, &parameters);

	Book *iBook = bdo::newBook(bdo::XML);
	bdo::loadSheet(iBook, parameters.iFile, 0);
	Sheet* iSheet = bdo::getSheet(iBook, 0);

	Book *oBook = bdo::newBook(bdo::XLS);
	bdo::loadSheet(oBook, parameters.oFile, 0);
	Sheet* oSheet = bdo::getSheet(oBook, 0);

	for (int i = 2; i < iSheet->lastRow(); ++i)
	{
		bdo::cell srcCell = {.row = i, .col = 10}; // колонка, по которой нужно искать
		if (bdo::getValueCell(iSheet, &srcCell)) // получение данных из конкретной ячейки
		{
			bdo::rowCells rowCells = bdo::findRow(oSheet, &srcCell); // поиск по шаблону

			for (int i = 0; i < oSheet->lastCol(); ++i) // выводим то, что нашли в шаблоне
				std::cout << rowCells.cells[i]->value << ' ';
			std::cout << std::endl;

			bdo::freeRowCells(rowCells); // очищаем найденную строку, освобождаем память
		}
	}

	iBook->release();
	oBook->release();

    return 0;
}






















