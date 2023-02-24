#include<iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>

using namespace std;

#define ZERO 48
#define NINE 57


int StringToInt (char* str, int i)
{
	int j = i;
	int answ = 0;
	int jj, pos;
	int arr[5];
	while ((str[j] >= ZERO) && (str[j]<= NINE)){
		arr[j - i] = str[j] - ZERO;
		j++;
	 }
	pos = j;
	j = j - i - 1;
	for (jj = 0; jj < pos - i; jj++){
		answ += arr[jj]*pow(10, j);
		j--;
	}
	if (i == 1) answ *= -1;
	return answ;
}
int Order (int a)
{
	int x, i;
	for (x = a, i = 0; x > 0; x /=10, i++) {};
	return i;
}

class Fraction {
	private:
		int nom;
		int denom;
	public:
		Fraction (char* str);
		Fraction (int n, int d) {
			nom = n;
			denom = d;
		};
		Fraction operator- (int b);
		operator int();
		void reduce ();
		int Get_Nom();
		int Get_Denom();
};

Fraction :: Fraction (char* str)
{
	int i, a, b;
	if (str[0] == '-') {
		a = StringToInt(str, 1);
		i = Order(-1*a);
		b = StringToInt(str, i + 2);
	} else {
		a = StringToInt(str, 0);
		i = Order(a);
		b = StringToInt(str, i + 1);
	}
	this->nom = a;
	this->denom = b;
}

Fraction Fraction :: operator- (int b) {
	int new_nom;
	new_nom = this->nom - (this->denom)*b;
	return Fraction(new_nom, this->denom);
}
Fraction :: operator int () {
	int x;
	x = nom/denom;
	return x;
} 

void Fraction :: reduce() {
	int a, b;
	a = nom;
	b = denom;
	while ((a != 0) && (b != 0)){
		if (a > b) a =  a % b;
		else b = b % a;
	}
	nom /= (a + b);
	denom /= (a + b);
}
int Fraction :: Get_Nom ()
{
	return nom;
}
int Fraction :: Get_Denom ()
{
	return denom;
}

int main (int argc, char* argv[])
{
	
	if (argc < 2)
		return (puts("Don`t input data\n"));
	Fraction x(argv[1]);
	int y;
	y = (int) x;
	Fraction z = x-y;
	z.reduce();
	cout << x.Get_Nom() << "/"<< x.Get_Denom()<< " - " << y << " = ";
	cout << z.Get_Nom() <<  "/" << z.Get_Denom() << endl;
	return 0;
}
	