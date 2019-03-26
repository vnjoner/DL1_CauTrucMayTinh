#pragma once
#include <iostream>
using namespace std;

//phần thập phân lưu theo tp4 tp3 tp2 tp1 (vd 100 2 130 100 => tp4 = 100, tp2 = 2, tp3 = 130, tp4 = 100 )
//các biết lưu từ phải sang trái ( 3 = 100 -> a[0] = 1 và 0.625 = 0.101 -> a[16] = 1)


class Qfloat {
private:
	unsigned short nguyen;
	unsigned int tp1, tp2, tp3;
	unsigned short tp4;
public:

	Qfloat();
	~Qfloat();
	Qfloat operator =(Qfloat x);
	
	void BinToQfloat(bool *bit);
	void QfloatToBin(bool *bit);
};

string BinToDec(bool *bit);
bool *DecToBin(string dec);

void ScanQfloat(Qfloat &x);
void PrintQfloat(Qfloat x);
