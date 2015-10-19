#include "resource.h"
class Matrix
{
public:
	Matrix(int col, int row)
	{
		memory = new double[col*row];
		count_col=col;
		count_row=row;
	}
	Matrix(double *memory1, int col, int row)
	{
		memory = new double[col*row];
		//не заносилось число столбцов и строк, из-за этого методы работали некорректно, исправлено
		count_col=col;
		count_row=row;
		memory = memory1;

	}
	Matrix(Matrix & rA)
	{
		count_col=rA.count_col;
		count_row=rA.count_row;
		memory = new double[count_col*count_row];
		for(int i=0; i<count_col*count_row; i++)
		{
			memory[i]=rA.memory[i];
		}
	}
	~Matrix()
	{
		delete memory;
	}
	double get_value(int col, int row);
	void set_value (int col, int row, double value);
	int get_count_col()
	{
		return count_col;
	}
	int get_count_row()
	{
		return count_row;
	}
private:
	double *memory;
	int count_col;
	int count_row;
};