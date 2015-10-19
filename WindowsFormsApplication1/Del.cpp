#include "stdafx.h"
#include "del.h"

void sub_vec(Matrix U0,int row1,Matrix &U1,int row2,double mult)
{
	double a;
	int i;
	for (i=0;i<U0.get_count_col();i++)
	{
		a = U1.get_value(i,row2);
		a = U0.get_value(i,row1);
		U1.set_value(i,row2,(U1.get_value(i,row2)-(U0.get_value(i,row1)*mult)));
		a = U1.get_value(i,row2);
	}
}
void per_str(Matrix &D,int row1, int row2)
{
	int i;
	Matrix U(D);
	for (i=0;i<D.get_count_col();i++)
	{
		D.set_value(i,row1,D.get_value(i,row2));
		D.set_value(i,row2,U.get_value(i,row1));
	}
}

Matrix find_vec(Matrix D, Matrix U0, Matrix U1)
{
	int ite=0;
	int N=20;
	int i,j,k;
	double a;//потом убрать
	double coef;
	bool no_colution=false;

	i=D.get_count_col();
	j=D.get_count_row();

	if (D.get_count_row()>D.get_count_col())
	{
		i=j;
	}

	Matrix D1(j,i); //создаем транспонированную матрицу

	//if (D.get_count_row()>D.get_count_col())
	//{
	//	for(i=D.get_count_col();i<D.get_count_row();i++)
	//	{
	//		for(i=0;i<D.get_count_row();i++)
	//		{
	//			D1.set_value(j,i,0);
	//		}
	//	}
	//}

	sub_vec(U0,0,U1,0,1);//находим u1 = u1 - u0
	i=U1.get_count_col();
	if (D.get_count_row()>D.get_count_col())
	{
		i=D.get_count_row();
	}
	Matrix U2(1,i);
	if (D.get_count_row()>D.get_count_col())
	{
		for(i=U1.get_count_col();i<U2.get_count_row();i++)
		{
			U2.set_value(0,i,0);
		}
	}
	//Matrix U3(U0.get_count_row(),U0.get_count_col());
	for (i=0;i<D1.get_count_col();i++) //находим транспонированную матрицу
	{
		for (j=0;j<D1.get_count_row();j++)
		{
			/*if (j<D.get_count_row())*/
			if (D.get_count_col()>j)
			{
				a = D.get_value(j,i);
				D1.set_value(i,j,D.get_value(j,i));
			}
			else
				D1.set_value(i,j,0);

		}
	}

	/*	if (D.get_count_row()>D.get_count_col())
	{
	for(i=D.get_count_col();i<D.get_count_row();i++)
	{
	for(i=0;i<D.get_count_row();i++)
	{
	D1.set_value(j,i,0);
	}
	}
	}*/

	for (i=0;i<U1.get_count_col();i++) //находим транспонированную матрицу
	{
		U2.set_value(0,i,U1.get_value(i,0));
		//U3.set_value(0,i,U0.get_value(i,0));
	}

	for(i=0;i<U2.get_count_row();i++)//проверка, потом убрать
	{
		a=U2.get_value(0,i);
	}


	for(i=0;i<U2.get_count_row();i++)//проверка, потом убрать
	{
		a=U2.get_value(0,i);
	}

	for(i=0;i<D1.get_count_col();i++) //переставляем строки
	{
		for (j=i;j<D1.get_count_row();j++)
		{
			for (k=j;k<D1.get_count_row();k++)
			{
				if (abs(D1.get_value(i,j))<abs(D1.get_value(i,k)))
				{
					per_str(D1,j,k);
					per_str(U2,j,k);
				}
			}
		}
	}

	for(i=0;i<U2.get_count_row();i++)//проверка, потом убрать
	{
		a=U2.get_value(0,i);
	}

	//Matrix D2(D1);

	for (k=0;k<D1.get_count_col();k++)//метод Гаусса
	{
		coef = D1.get_value(k,k);
		if (coef!=0)
			U2.set_value(0,k,(U2.get_value(0,k)/coef));

		for (i=k;i<D1.get_count_col();i++)//Получаем единичку
		{
			if (coef!=0)
				D1.set_value(i,k,(D1.get_value(i,k)/coef));
		}

		for (i=k+1;i<D1.get_count_row();i++) //вычитаем строки
		{
			if (D1.get_value(k,i)!=0)
			{
				sub_vec(U2,k,U2,i,D1.get_value(k,i));
				sub_vec(D1,k,D1,i,D1.get_value(k,i));

			}


		}
	}


	for(i=0;i<U2.get_count_row();i++)//проверка, потом убрать
	{
		a=U2.get_value(0,i);
	}

	for(i=0;i<D1.get_count_col();i++) //переставляем строки
	{
		for (j=i;j<D1.get_count_row();j++)
		{
			for (k=j;k<D1.get_count_row();k++)
			{
				if (abs(D1.get_value(i,j))<abs(D1.get_value(i,k)))
				{
					per_str(D1,j,k);
					per_str(U2,j,k);
				}
			}
		}
	}

	for(i=0;i<U2.get_count_row();i++)//проверка, потом убрать
	{
		a=U2.get_value(0,i);
	}

	Matrix S(D1.get_count_col(),1); //вектор срабатывания
	//добавлено отсюда
	int COEF = 0;//что приравниваем в начале решения
	Matrix P(D1.get_count_col(),D1.get_count_row()); //создаем копию D1
	for (i=0;i<D1.get_count_col();i++)
	{
		for (j=0;j<D1.get_count_row();j++)
		{
			P.set_value(i,j,D1.get_value(i,j));
		}
	}
	for(ite=0;ite<N;ite++)
	{
		if (COEF!=0)//если ответ уже не получился, то восстанавливаем D1
		{
			for (i=0;i<D1.get_count_col();i++)
			{
				for (j=0;j<D1.get_count_row();j++)
				{
					D1.set_value(i,j,P.get_value(i,j));
				}
			}

		}
		//////////////////до сюда
		for (k=D1.get_count_col()-1;k>-1;k--)//находим решение
		{
			/*for (i=k;i<D1.get_count_col();i++)
			{*/
			a= D1.get_value(k,k);
			if (D1.get_value(k,k)!=0)//если строка ненулевая, то делим...
			{
				coef=U2.get_value(0,k)/D1.get_value(k,k);
				S.set_value(k,0,coef);
			}else                   //...иначе либо нет решений, либо их целая куча
			{
				if(U2.get_value(0,k)!=0)
				{
					no_colution=true;
					break;
				}else
				{
					//изменено с 0 на COEF
					S.set_value(k,0,COEF);
				}
			}
			//}

			if (no_colution==true)
			{
				S.set_value(0,0,-1);
			}

			if (k==0)
				break;
			for (i=k;i<D1.get_count_col();i++)//подставляем известные переменные
			{
				D1.set_value(i,k-1,(D1.get_value(i,k-1)*S.get_value(i,0)));
				coef=U2.get_value(0,k-1)-D1.get_value(i,k-1);
				U2.set_value(0,k-1,coef);
			}

		}
		//////////////////
		//////////////////добавлено отсюда
		bool minus=false;
		if (no_colution==true)
			break;
		for (i=0;i<S.get_count_col();i++)
		{
			if (S.get_value(i,0)<0)
			{
				minus=true;
				break;
			}
		}
		if (minus==false)
			break;
		else
			COEF++;
	}
	/////////////////до сюда
	if (D1.get_count_row()>D1.get_count_col())
	{
		for(i=D1.get_count_col();i<D1.get_count_row();i++)
		{
			a=D1.get_value(D1.get_count_col()-1,i);
			if(D1.get_value(D1.get_count_col()-1,i)==0)
			{
				if(U2.get_value(0,i)!=0)
					no_colution=true;
			}
		}
	}

	if (no_colution==true)
	{
		S.set_value(0,0,-1);
	}
	for(i=0;i<S.get_count_col();i++)//проверка, потом убрать
	{
		a=S.get_value(i,0);
	}


	return S;
}