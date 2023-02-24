#include <iostream>																				// 	Разработать объектно-ориентированную программу для поиска точки из любого заданного 
#include <cmath>																				//	набора точек на плоскости, суммарное расстояние которой до остальных точек этого 	
																								//	набора будет минимально. Декартовые координаты всех точек должны быть указаны 
using namespace std;																			//	парами целых чисел в аргументах командной строки вызова программы. Координаты
																								//	полученной точки должны отображаться строкой стандартного вывода. В программе 	
//-----------------------------------------------------------------------------------			//	должен быть реализован класс точки с приватными полями ее декартовых координат,	
																								//	публичными методами доступа к ним и конструктором инициализации их значений. 
class Point {																					//	Вычисление расстояния между парами любых точек должна обеспечивать внешняя 
	private	:																					//	функция. Кроме того, в программе должно быть предусмотрено динамическое 
		double x;																				//	распределение памяти для всех заданных точек и массива их адресов.
		double y;	
	public :
		Point (double x, double y);
		double Get_X ();
		double Get_Y ();
};

//-----------------------------------------------------------------------------------

Point :: Point (double x, double y)
{
	this->x = x;
	this->y = y;
}
double Point :: Get_X ()
{
	return x;
}
double Point :: Get_Y ()
{
	return y;
}

//-----------------------------------------------------------------------------------

double Distance (Point* a, Point* b)
{
	double l;
	l = sqrt(pow((b->Get_X() - a->Get_X()), 2) + pow((b->Get_Y() - a->Get_Y()), 2));
	return l;
}

//-----------------------------------------------------------------------------------


int main ()
{
	Point* p;
	int i, j, n; 
	double min_dist, a, b, ll;
	cin >> n;
	Point **array_points = new Point*[n];
	min_dist = 1000;
	for (i = 0; i < n; i++) {
		cin >> a >> b;
		array_points[i] = new Point(a, b);
	}
/*	for (i =0; i < n; i++){
		cout << array_points[i]->Get_X() << ' ' << array_points[i]->Get_Y() << endl;
	}
*/
	for (i = 0; i < n; i++) {
		ll = 0;
		for (j = 0; j < n; j++){
			if (i == j) continue;
			else ll += Distance (array_points[i], array_points[j]);
		}
		if (ll < min_dist){
			min_dist = ll;
			p = array_points[i];
		}
	}
	cout << min_dist << endl;
	cout << p->Get_X() << ' ' << p->Get_Y() << endl;
	for (i = 0; i < n; i++) delete array_points[i];
	delete []array_points;
	return 0;
	
}