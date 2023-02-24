#include <iostream>																				// 	Разработать объектно-ориентированную программу для построения магического квадрата 
																								//	любого нечетного порядка из последовательных натуральных чисел по сиамскому методу 	
																								//	в следующем варианте. Начальное значение 1 необходимо записать в клетку справа от
using namespace std;																			//	центра квадрата. Заполнение следующих клеток последовательными числами должно 
																								//	происходить направо и вверх по диагонали. Если очередная клетка уже занята, то 
//-----------------------------------------------------------------------------------			//	следующее число нужно записать на 2 клетки справа от предыдущего. Когда число 	
																								//	оказывается за границей квадрата, его необходимо перенести внутрь квадрата, изменив
class Magic_square {																			 //	 заграничную координату на порядок квадрата. Результат построения магического квадрата 
	private :																					//	по указанным правилам должен отображаться в поток стандартного вывода. Значение 
		int **square;															           	    //  порядка квадрата должно передаваться программе аргументом командной строки. При 
//		unsigned int i, j;																		//	разработке программы конструктор класса должен обеспечивать динамическое
		int n;																		            //  распределение памяти по защищенному адресу для двумерного массива. Необходимо 
	public :																					 //  предусмотреть компонентные методы для его заполнения и отображения в классе.
		Magic_square(int n);
		~Magic_square();
		void Print();
		void FillinSquare();
};

//-----------------------------------------------------------------------------------

int DefineInterval (int n, int x)
{
	if (x < 0) return -1;
	else {
		if (x >= n) return 1;
		else return 0;
	}
}

int ChangeIndex (int n, int ind)
{
	int sign;
	sign = DefineInterval(n, ind);
	switch (sign) {
		case -1: return ind + n;
		case 1: return n - ind;
		case 0: return ind;
		default: return -100000;
	}	
}

//-----------------------------------------------------------------------------------

Magic_square :: Magic_square(int n)
{
	int i, j;
	this->n = n;
	square = new int* [n];
	for (i = 0; i < n; i++){
		square[i] = new int[n];
		for (j = 0; j < n; j++) {
			square[i][j] = 0;
		}
	}
}

Magic_square :: ~Magic_square() 
{
	int i, j;
	for (i = 0; i < n; i++) delete [] square[i];
	delete [] square;
}

void Magic_square :: FillinSquare()
{
	int i, j, count;
	for (count = 1, i = n/2, j = n/2 + 1; count <= n*n; count++) {
		if (square[i][j] != 0) {
			j = ChangeIndex(n, j - 2);
			square[i][j] = count;
		} else square[i][j] = count;
		i = ChangeIndex(n, i - 1);
		j = ChangeIndex(n, j + 1);
		
	}
}

void Magic_square :: Print()
{
	int i, j;
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++) cout << square[i][j] << ' ';
		cout << endl;
	}
}

//-----------------------------------------------------------------------------

int main (int argc, char* argv[])
{
	int x;
	if (argc != 2)
		return (puts("Put, please, odd integer"));
	x = atoi(argv[1]);
	if (x % 2 == 0) {
		cout << "Error: even number" << endl;
	} else {
		Magic_square p(x);
		p.FillinSquare();
		p.Print();
	}
	return 0;
}