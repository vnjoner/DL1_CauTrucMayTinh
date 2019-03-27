#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include<cmath>
using namespace std;

class Qint
{
private:
	int a1, a2, a3, a4;
public:
	//hung
	Qint();
	~Qint();

	// binh
	Qint operator+(Qint x);
	Qint operator-(Qint x);
	Qint operator*(Qint x);// hung

	Qint operator / (Qint x);// quang huy

	bool operator == (Qint x);
	bool operator >= (Qint x);
	bool operator <= (Qint x);
	bool operator > (Qint x);
	bool operator < (Qint x);

	// van huy
	Qint operator &(Qint x);
	Qint operator | (Qint x);
	Qint operator ^(Qint x);
	Qint operator ~();

	//hung
	friend ostream &operator <<(ostream &os, Qint &a)
	{
		os << a.a4 << a.a3 << a.a2 << a.a1 << ;
	}
	Qint operator >> (Qint a);
	Qint Qint_rol();
	Qint Qint_ror();
};

//
//void ScanQint(Qint &x) {};
//void PrintQint(Qint x) {};// anh huy
//void ScanQintFile(ifstream &is, Qint &x) {};//hung
//
//
////nhap
//bool* StringDecToBin(string dec) {}; //binh xong
//bool* StringHexToBin(char* hex) {};//anh huy
//
////Trung gian
//Qint BinToQint(bool* bit) {};
//bool* QintToBin(Qint x) {};
//
////xuat
//char * BinToHex(bool bit[]) {}; // anh huy
//string BinToDec(bool bit[]) {};// van huy