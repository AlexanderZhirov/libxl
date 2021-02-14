#include "bdo.hpp"
#include "key.hpp"
#include <cstring>

libxl::Book *bdo::newBook(bdo::typeBook type)
{
	libxl::Book *book = nullptr;

	switch (type)
	{
		case XLS: book = xlCreateBook(); break;
		case XML: book = xlCreateXMLBook(); break;
	}

	if (!book)
	{
		std::cout << book->errorMessage() << std::endl;
		exit(-1);
	}

	libxl::setKey(book);

	return book;
}

void bdo::loadSheet(libxl::Book *book, const char *path, int index)
{
	if (!book->loadSheet(path, index))
	{
		std::cout << book->errorMessage() << std::endl;
		exit(-2);
	}
}

libxl::Sheet *bdo::getSheet(libxl::Book *book, int index)
{
	libxl::Sheet* sheet = book->getSheet(0);

	if (!sheet)
	{
		std::cout << book->errorMessage() << std::endl;
		exit(-3);
	}

	return sheet;
}

bool bdo::getValueCell(libxl::Sheet *sheet, bdo::cell *cell)
{
	const char *value = sheet->readStr(cell->row, cell->col);

	if (value)
	{
		strcpy(cell->value, value);
		cell->isSet = true;
	}

	return cell->isSet;
}

int bdo::findNumRow(libxl::Sheet *sheet, bdo::cell *cell)
{
	for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
	{
		for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
		{
			const char* string = sheet->readStr(row, col);

			if (string && strstr(string, cell->value))
				return row;
		}
	}

	return (-1);
}

bdo::rowCells bdo::findRow(libxl::Sheet *sheet, bdo::cell *cell)
{
	bdo::rowCells rowCells;
	rowCells.cells = (bdo::cell **)malloc(sizeof(bdo::cell *) * sheet->lastCol());
	rowCells.size = sheet->lastCol();

	for (int row = sheet->firstRow(); row < sheet->lastRow(); ++row)
	{
		for (int col = sheet->firstCol(); col < sheet->lastCol(); ++col)
		{
			const char* string = sheet->readStr(row, col);

			if (string && strstr(string, cell->value))
			{
				for (int i = 0; i < sheet->lastCol(); ++i)
				{
					bdo::cell *newCell = (bdo::cell *)malloc(sizeof(bdo::cell));

					newCell->col = i;
					newCell->row = row;

					const char* value = sheet->readStr(row, i);

					if (value)
					{
						strcpy(newCell->value, value);
						newCell->isSet = true;
					}

					rowCells.cells[i] = newCell;
				}

				return rowCells;
			}
		}
	}

	return rowCells;
}

void bdo::freeRowCells(bdo::rowCells rowCells)
{
	for (int i = 0; i < rowCells.size; ++i)
	{
		free(rowCells.cells[i]);
	}
	free(rowCells.cells);
}

















