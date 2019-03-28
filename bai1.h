#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Qint
{
private:
	int a1, a2, a3, a4;
public:
	//hung
	Qint();
	~Qint() {};
	Qint operator = (Qint x) {
		if (this == &x)
			return *this;
		else {
			this->a1 = x.a1;
			this->a2 = x.a2;
			this->a3 = x.a3;
			this->a4 = x.a4;
		}
		return *this;
	}

	// binh
	Qint operator+(Qint x);
	Qint operator-(Qint x);
	//Qint operator*(Qint x);// hung

	//Qint operator / (Qint x);// quang huy

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
//void PrintQint(Qint x) {};// anh huy
void QintFile(ifstream &is, ofstream &os);


//nhap
bool* StringDecToBin(string dec);//binh xong
bool* StringHexToBin(char* hex);// anh huy

								//xuat
char * BinToHex(bool *bit);//anh huy
string BinToDec(bool *bit); //vanhuy
