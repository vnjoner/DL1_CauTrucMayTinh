#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Qint
{
private:
	unsigned int a1, a2, a3, a4;
public:
	Qint();
	~Qint() {};
	Qint operator = (Qint x);

	Qint operator+(Qint x);
	Qint operator-(Qint x);
	Qint operator*(Qint x);

	//Qint operator / (Qint x);// quang huy

	bool operator == (Qint x);
	bool operator >= (Qint x);
	bool operator <= (Qint x);
	bool operator > (Qint x);
	bool operator < (Qint x);

	Qint operator &(Qint x);
	Qint operator | (Qint x);
	Qint operator ^(Qint x);
	Qint operator ~();

	Qint operator <<(Qint a);
	Qint operator >> (Qint a);
	Qint Qint_rol();
	Qint Qint_ror();

	void BinToQint(bool* bit);
	void QintToBinary(bool bit[]);

	void PrintQint() {
		cout << a4 << "  " << a2 << "  " << a3 << "  " << a1 << endl;
	}
};


void ScanQint(Qint &x) {};
void QintFile(ifstream &is, ofstream &os);


//nhap
bool* StringDecToBin(string dec);
bool* StringHexToBin(char* hex);

//xuat
char * BinToHex(bool *bit);
string BinToDec(bool *bit);
