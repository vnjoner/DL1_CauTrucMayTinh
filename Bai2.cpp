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
	int j;
	j = 31;
	while (j >= 0) {
		if (bit[i] == 1) {
			tp1 += pow(2, 31 - j);
		}
		i--;
		j--;
	}
	j = 31;
	while (i >= 64) {
		if (bit[i] == 1) {
			tp2 += pow(2, 31 - j);
		}
		i--;
		j--;
	}
	j = 31;
	while (i >= 32) {
		if (bit[i] == 1) {
			tp3 += pow(2, 31 - j);
		}
		i--;
		j--;
	}
	j = 15;
	while (i >= 16) {
		if (bit[i] == 1) {
			tp4 += pow(2, 31 - j);
		}
		i--;
		j--;
	}
	j = 15;
	while (i >= 0) {
		if (bit[i] == 1) {
			nguyen += pow(2, 15 - j);
		}
		i--;
		j--;
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






