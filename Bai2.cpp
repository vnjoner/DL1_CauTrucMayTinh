#include "Bai2.h"

Qfloat::Qfloat() {
	nguyen = 0;
	tp4 = 0;
	tp3 = 0;
	tp2 = 0;
	tp1 = 0;
}

Qfloat::~Qfloat() {
}

Qfloat::operator=(const Qfloat &x) {
	if (this == &x) {
		return *this
	}
	this->nguyen = x.nguyen;
	this->tp4 = x.tp4;
	this->tp3 = x.tp3;
	this->tp2 = x.tp2;
	this->tp1 = x.tp1;
	return *this;
}

void Qfloat::BinToQfloat(bool *bit) {
	int i = 127;
	while (i >= 96) {
		tp1 += bit[i] * pow(2, 127 - i);
		i--;
	}
	while (i >= 64) {
		tp2 += bit[i] * pow(2, 127 - i);
		i--;
	}
	while (i >= 32) {
		tp3 += bit[i] * pow(2, 127 - i);
		i--;
	}
	while (i >= 16) {
		tp4 += bit[i] * pow(2, 127 - i);
		i--;
	}
	while (i >= 0) {
		nguyen += bit[i] * pow(2, 127 - i);
		i--;
	}
}

void Qfloat::QfloatToBin(bool *bit) {
	int dummytp1 = tp1, dummytp2 = tp2, dummytp3 = tp3;
	short dummynguyen = nguyen, dummytp4 = tp4;
	int i = 127;
	while (i >= 96) {
		bit[i] = (dummytp1 % 2)  ? 1 : 0;
		dummytp1 /= 2;
		i--;
	}
	while (i >= 64) {
		bit[i] = (dummytp2 %2 ) ? 1 : 0;
		dummytp2 /= 2;
		i--;
	}
	while (i >= 32) {
		bit[i] = (dummytp3 % 2) ? 1 : 0;
		dummytp3 /= 2;
		i--;
	}
	while (i >= 16) {
		bit[i] = (dummytp4 % 2) ? 1 : 0;
		dummytp4 /= 2;
		i--;
	}
	while (i >= 0) {
		bit[i] = (dummynguyen %2) ? 1 : 0;
		dummynguyen /= 2;
		i--;
	}
}






