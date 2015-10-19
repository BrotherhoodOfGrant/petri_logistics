#include "stdafx.h"
#include "Matrix.h"

double Matrix::get_value(int col, int row)
{
	return memory[count_row*col+row];
}

void Matrix::set_value(int col, int row, double value)
	{
		memory[count_row*col+row]=value;
}