#ifndef BDO_HPP_
#define BDO_HPP_

#include <iostream>
#include "libxl.h"

namespace bdo
{
	typedef enum {XLS, XML} typeBook;

	typedef struct
	{
		int row;
		int col;
		bool isSet = false;
		char value[500];
	} cell;

	typedef struct
	{
		int size;
		cell **cells;
	} rowCells;

	libxl::Book *newBook(typeBook);
	void loadSheet(libxl::Book *, const char *, int);
	libxl::Sheet *getSheet(libxl::Book *, int);

	bool getValueCell(libxl::Sheet *, cell *);
	int findNumRow(libxl::Sheet *, cell *);

	rowCells findRow(libxl::Sheet *, cell *);
	void freeRowCells(bdo::rowCells);


}

#endif
