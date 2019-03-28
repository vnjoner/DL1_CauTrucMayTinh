#include "bai1.h"


Qint Qint::operator = (Qint x) {
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

Qint::Qint() {
	a1 = 0;
	a2 = 0;
	a3 = 0;
	a4 = 0;
}

Qint::~Qint() {

}

bool Qint::operator == (Qint x)
{
	if (this->a1 == x.a1 && this->a2 == x.a2 && this->a3 == x.a3 && this->a4 == x.a4)
		return true;
	return false;
}
bool Qint::operator >= (Qint x)
{
	if (*this < x) {
		return false;
	}
	return true;
}
bool Qint::operator <= (Qint x)
{
	if (*this > x)
		return false;
	return true;
}
bool Qint::operator > (Qint x)
{
	if (*this < x && !(*this == x))
		return false;
	return true;
}
bool Qint::operator < (Qint x)
{
	if (*this == x) return false;
	bool a[128] = { 0 };
	bool b[128] = { 0 };
	x.QintToBinary(b);
	this->QintToBinary(a);

	for (int i = 1; i < 128; i++) {
		if (a[i] > b[i] && a[0] == 0) {
			return false;
		}
		if (a[i] < b[i] && a[0] == 1)
			return false;
	}
	return true;
}

/* ham chuyen doi string index kieu (char*) sang kieu int*/
int getBit(const string &s, int index) {
	if (index >= 0) {
		return (s[index] - '0');//-48
	}
	return 0;
}

/*   utility check xem (string s) co ket thuc bang (string target) hay khong  */
bool IS_EndWithTarget(const string &s, const string &target) {
	//(danh cho function chuyen 10 sang 2)
	if (s.size() >= target.size() && s.compare(s.size() - target.size()/*bat dau*/, target.size()/*length kiem tra*/, target/*chuoi can kiem tra*/) == 0) {
		return true;
	}
	return false;
}

/*   ham check tan cung cua 1 string (he 10) co la so le hay khong   */
string CHECKTanCungLe(string s) {// tan cung la so le thi tra ve "1", else "0" (danh cho chuyen 10 sang 2)
	if (IS_EndWithTarget(s, "1") || IS_EndWithTarget(s, "3") || IS_EndWithTarget(s, "5") || IS_EndWithTarget(s, "7") || IS_EndWithTarget(s, "9")) {
		return "1";
	}
	return "0";
}

/***** chia 2, type string, khong dung phep toan ****/
string chiaHai(string s) {
	string soCongTiepTheo = "0";
	for (int i = 0; i < s.size(); i++) {
		string soCong = soCongTiepTheo;//cap nhat so cong
		if (getBit(s, i) % 2 != 0) {//neu s[i] le
			soCongTiepTheo = "5"; //cong 5
		}
		else {
			soCongTiepTheo = "0"; //khong cong
		}
		s[i] = getBit(s, i) / 2 + stoi(soCong) + '0';
	}
	s.erase(0, s.find_first_not_of('0'));
	return s;
}

/*    ham CONVERT he 10 -> 2    */

bool* StringDecToBin(string dec) {
    string kqString = "";
    bool *kq;
    if (dec == "0") {//neu bang 0 thi ngung
        kq = new bool[128];
        for (int i = 0; i < 128; i++){
            kq[i] = 0;
        }
        return kq;
    }
    else {
        while (dec != "0") {//khi dang khac 0
            kqString = CHECKTanCungLe(dec) + kqString;
            dec = chiaHai(dec);
        }
    }
    kq = new bool[128];
    while (kqString.size() < 128){
        kqString = "0" + kqString;
    }
    for (int i = (int)kqString.size() - 1; i >= 0; i--) {
        kq[i] = kqString[i] - '0';
    }
    return kq;
}

void Qint::QintToBinary(bool bit[]) {// đổi từ 4 int ra dãy nhị phân, lưu thông qua tham chiếu bit[],
									 //vd  123.32.2.12 -> bit[]={0,0,1,1,0,0,0,0,........./0,0,1,0,0,0,0,0......./0,0,0,0,0,1,0,0......../,1,1,0,1,1,1,1,0........}
	int i = 127;
	int b1 = a1, b2 = a2, b3 = a3, b4 = a4;
	while (b1 != 0) {
		bit[i--] = (b1 % 2 == 0 ? 0 : 1);
		b1 /= 2;
	}

	i = 95;
	while (b2 != 0) {
		bit[i--] = (b2 % 2 == 0 ? 0 : 1);
		b2 /= 2;
	}
	i = 63;
	while (b3 != 0) {
		bit[i--] = (b3 % 2 == 0 ? 0 : 1);
		b3 /= 2;
	}
	i = 31;
	while (b4 != 0) {
		bit[i--] = (b4 % 2 == 0 ? 0 : 1);
		b4 /= 2;
	}
}

void Qint::BinToQint(bool * bit)// dùng để lưu dãy nhị phân vào trong 4 int
{
	this->a4 = 0;
	for (int i = 0; i < 32; i++)
	{
		if (bit[i] == 1) {
			this->a4 += pow(2, 31 - i);
		}
	}
	this->a3 = 0;
	for (int i = 32; i < 64; i++)
	{
		if (bit[i] == 1) {
			this->a3 += pow(2, 63 - i);
		}
	}
	this->a2 = 0;
	for (int i = 64; i < 96; i++)
	{
		if (bit[i] == 1) {
			this->a2 += pow(2, 95 - i);
		}
	}
	this->a1 = 0;
	for (int i = 96; i < 128; i++)
	{
		if (bit[i] == 1) {
			this->a1 += pow(2, 127 - i);
		}
	}
}
Qint Qint::operator&(Qint x)
{
	Qint temp;
	bool a[128] = { 0 };
	bool b[128] = { 0 };
	bool c[128] = { 0 };
	this->QintToBinary(a);
	x.QintToBinary(b);
	for (int i = 0; i < 128; i++)
	{
		c[i] = a[i] * b[i];
	}
	temp.BinToQint(c);
	return temp;
}

Qint Qint::operator|(Qint x)
{
	Qint temp;
	bool a[128] = { 0 };
	bool b[128] = { 0 };
	bool c[128] = { 0 };
	this->QintToBinary(a);
	x.QintToBinary(b);
	for (int i = 0; i < 128; i++)
	{
		if (!(a[i] == 0 && b[i] == 0))
			c[i] = 1;
	}
	temp.BinToQint(c);
	return temp;
}
Qint Qint::operator ^(Qint x)
{
	Qint temp;
	bool a[128] = { 0 };
	bool b[128] = { 0 };
	bool c[128] = { 0 };
	this->QintToBinary(a);
	x.QintToBinary(b);
	for (int i = 0; i < 128; i++)
	{
		c[i] = abs(a[i] - b[i]);
	}
	temp.BinToQint(c);
	return temp;
}

Qint Qint::operator~()
{
	bool a[128] = { 0 };
	this->QintToBinary(a);
	for (int i = 0; i < 128; i++)
	{
		a[i] = (a[i] + 1) % 2;
	}
	this->BinToQint(a);
	return *this;
}


string BinToDec(bool *bit) {// Đáng lí ra type trả về là Qint và cắt thành 4 để 
							//lưu trong 4 int, nhưng không đủ, có gì hỏi thì giải thích cho
	int temp[40] = { 0 };
	string a;
	int arr[40] = { 0 };
	int memo, dummy;
	if (bit[127] == 1)
		arr[39] = 1;
	temp[39] = 1;
	for (int i = 126; i >0; i--)
	{
		memo = 0;
		for (int j = 39; j >= 0; j--)
		{
			int dummy = temp[j];
			temp[j] = (temp[j] * 2 + memo) % 10;
			memo = (dummy * 2 + memo) / 10;
		}
		memo = 0;
		if (bit[i] == 1) {
			for (int k = 39; k >= 0; k--)
			{
				dummy = arr[k];
				arr[k] = (arr[k] + temp[k] + memo) % 10;
				memo = (dummy + temp[k] + memo) / 10;
			}
		}
	}
	for (int i = 0; i <40; i++) {
		if (arr[i] != 0) {
			for (int j = i; j < 40; j++)
			{
				a = a + (char)(arr[j] + 48);
			}
			break;
		}
	}
	if (bit[0] == 1)
		a = '-' + a;
	return a;
}


Qint Qint::operator << (Qint a) {
	bool dummy[128] = { 0 };
	this->QintToBinary(dummy);
	bool dummy2[128] = { 0 };
	a.QintToBinary(dummy2);
	int b = 0;
	for (int i = 0; i < 128; i++)
		if (dummy2[i] == 1) {
			for (int j = 127; j >= i; j--)
				if (dummy2[j] == 1)
					b += pow(2, 127 - j);
			break;
		}
	for (int i = 0; i < 128; i++) {
		if (dummy[i] == 1) {
			for (int j = i; j < 128; j++)
				dummy[j - b] = dummy[j];
			for (int j = b - 1; j >= 0; j--) {
				dummy[127 - j] = 0;
			}
			break;
		}
	}
	this->BinToQint(dummy);
	return *this;
}

Qint Qint::operator >> (Qint a) {
	bool dummy[128] = { 0 };
	this->QintToBinary(dummy);
	bool dummy2[128] = { 0 };
	a.QintToBinary(dummy2);
	bool dummy3[128] = { 0 };
	int b = 0;
	for (int i = 0; i < 128; i++)
		if (dummy2[i] == 1) {
			for (int j = 127; j >= i; j--)
				if (dummy2[j] == 1)
					b += pow(2, 127 - j);
			break;
		}
	for (int i = 0; i < 128; i++) {
		if (dummy[i] == 1) {
			for (int j = i; j < 128; j++) {
				dummy3[j + b] = dummy[j];
				if (j + b == 127)
					break;
			}
			break;
		}
	}
	this->BinToQint(dummy3);
	return *this;
}

Qint Qint::Qint_rol() {
	bool dummy[128] = { 0 };
	this->QintToBinary(dummy);
	bool kq[128] = { 0 };
	kq[127] = dummy[0];
	for (int i = 1; i < 128; i++) {
		kq[127 - i] = dummy[127 - i + 1];
	}
	this->BinToQint(kq);
	return *this;
}

Qint Qint::Qint_ror() {
	bool dummy[128] = { 0 };
	this->QintToBinary(dummy);
	bool kq[128] = { 0 };
	kq[0] = dummy[127];
	for (int i = 1; i < 128; i++) {
		kq[i] = dummy[i - 1];
	}
	this->BinToQint(kq);
	return *this;
}

string tobinary(unsigned long long n) {
	string kq;
	while (n != 0) {
		kq = (n % 2 == 0 ? "0" : "1") + kq;
		n /= 2;
	}
	while (kq.size() < 32) {
		kq = "0" + kq;
	}
	return kq;
}

/*   ham cong hai so he 2, tra ve string   */
string addbinary(string a, string b) {
	while (a.size() > b.size()) { // them so 0 cho ngang size
		b = "0" + b;
	}

	while (a.size() < b.size()) { //them so 0 cho ngang size
		a = "0" + a;
	}

	//lay index = length max vi index string kq se chay tu max ve 0
	int index = (int)a.size() - 1 > (int)b.size() - 1 ? (int)a.size() - 1 : (int)a.size() - 1;
	int s = 0;

	string kq = "";// khoi tao bien luu ket qua

	while (index >= 0 || s == 1) {
		//thuc hien tinh toan va` tinh carry tu` phan tu indexth -> 0th
		s = s + (getBit(a, index) + getBit(b, index));
		kq = (char)(s % 2 + '0') + kq;
		s /= 2;
		index--;
		if (kq.size() >= 128) {
			break;
		}
	}
	return kq;
}

/*  ham dao bit tu 0 -> 1, va nguoc lai, 1 -> 0 (operator -)  */
void daobit(string &s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '1') {
			s[i] = '0';
		}
		else if (s[i] == '0') {
			s[i] = '1';
		}
	}
}

Qint Qint::operator+(Qint x) {

	/* operator dung ham cong ben ngoai, nhan vao 2 string, tra ve 1 string, sau do chuyen sang qint */

	Qint kq;

	string s1 = tobinary(a4) + tobinary(a3) + tobinary(a2) + tobinary(a1);
	string s2 = tobinary(x.a4) + tobinary(x.a3) + tobinary(x.a2) + tobinary(x.a1);

	string kqstring = addbinary(s1, s2); // tinh toan


	bool *kqbool = new bool[128];//mang kq
	memset(kqbool, 0, 128);


	for (int i = 0; i < 128; i++) {
		kqbool[i] = kqstring[i] - '0';//chuyen thanh char
	}

	kq.BinToQint(kqbool);
	return kq;
}


Qint Qint::operator-(Qint x) {
	//
	//    /* operator - theo quy tac chuyen so thu 2 sang dang bu` 2's sau do thuc hien phep cong nhu thuong le*/
	//    /* cac buoc thuc hien giong nhu operator + */
	//
	Qint kq;

	string s1 = tobinary(a4) + tobinary(a3) + tobinary(a2) + tobinary(a1);
	string s2 = tobinary(x.a4) + tobinary(x.a3) + tobinary(x.a2) + tobinary(x.a1);
	//
	//
	bool *kqbool;


	if (x > *this) { // tru am thi nguoc lai
		daobit(s2);

		s2 = addbinary(s2, "1");

		string kqstring = addbinary(s1, s2); // tinh toan

		string somot("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");

		kqstring = addbinary(kqstring, somot);
		daobit(kqstring);
		kqstring[0] = '1';

		kqbool = new bool[128];//mang kq

							   //
		for (int i = 127; i >= 0; i--) {
			kqbool[i] = kqstring[i] - '0';//chuyen thanh char
		}
	}
	else if (*this == x) {//tru bang nhau mang kq chac chan se = 0
		kqbool = new bool[128];//mang kq

		for (int i = 0; i < 128; i++) {
			kqbool[i] = 0;
		}
	}
	else { //x be hon *this thi tru binh thuong
		daobit(s2);

		s2 = addbinary(s2, "1");
		//
		string kqstring = addbinary(s1, s2);


		kqbool = new bool[128];//mang kq

							   //
		for (int i = (int)kqstring.size() - 1; i >= 0; i--) {
			kqbool[i] = kqstring[i] - '0';//chuyen thanh char
		}
	}

	kq.BinToQint(kqbool);
	delete[] kqbool;
	return kq;
}

bool *StringHexToBin(char *hex)
{
	string BinaryString = "";
	for (int i = 0; i <32; i++)
	{
		if (hex[i] == '0')
			BinaryString += "0000";
		else if (hex[i] == '1')
			BinaryString += "0001";
		else if (hex[i] == '2')
			BinaryString += "0010";
		else if (hex[i] == '3')
			BinaryString += "0011";
		else if (hex[i] == '4')
			BinaryString += "0100";
		else if (hex[i] == '5')
			BinaryString += "0101";
		else if (hex[i] == '6')
			BinaryString += "0110";
		else if (hex[i] == '7')
			BinaryString += "0111";
		else if (hex[i] == '8')
			BinaryString += "1000";
		else if (hex[i] == '9')
			BinaryString += "1001";
		else if (hex[i] == 'a' || hex[i] == 'A')
			BinaryString += "1010";
		else if (hex[i] == 'b' || hex[i] == 'B')
			BinaryString += "1011";
		else if (hex[i] == 'c' || hex[i] == 'C')
			BinaryString += "1100";
		else if (hex[i] == 'd' || hex[i] == 'D')
			BinaryString += "1101";
		else if (hex[i] == 'e' || hex[i] == 'E')
			BinaryString += "1110";
		else if (hex[i] == 'f' || hex[i] == 'F')
			BinaryString += "1111";
	}
	bool *kq = new bool[128];
	memset(kq, 0, 128);

	for (int j = 0; j < 128; j++)
	{
		kq[j] = BinaryString[j] - '0';
	}

	return kq;
}


char *BinToHex(bool *bit)
{
	string BinaryString;
	for (int i = 0; i < 128; i++) {
		BinaryString += bit[i] + '0';
	}
	string HexaString = "";
	string str;
	for (int i = 0; i < 128; i += 4)
	{
		str = BinaryString.substr(i, 4);
		if (str == "0000")
			HexaString += "0";
		else if (str == "0001")
			HexaString += "1";
		else if (str == "0010")
			HexaString += "2";
		else if (str == "0011")
			HexaString += "3";
		else if (str == "0100")
			HexaString += "4";
		else if (str == "0101")
			HexaString += "5";
		else if (str == "0110")
			HexaString += "6";
		else if (str == "0111")
			HexaString += "7";
		else if (str == "1000")
			HexaString += '8';
		else if (str == "1001")
			HexaString += '9';
		else if (str == "1010")
			HexaString += "A";
		else if (str == "0000")
			HexaString += "B";
		else if (str == "1100")
			HexaString += "C";
		else if (str == "1101")
			HexaString += "D";
		else if (str == "1110")
			HexaString += "E";
		else if (str == "1111")
			HexaString += "F";
	}
	char *Hexa = new char[32];
	memset(Hexa, '0', 32);
	for (int i = 0; i < 32; i++)
	{
		Hexa[i] = HexaString[i];
	}
	return Hexa;
}

void QintFile(ifstream &is, ofstream &os) {
	string s[100];
	string opr1[100];
	string opr2[100];
	string sign[100];
	string p1[100], p2[100];
	int z = 0;
	is.open("input.txt", ios::in);

	while (!is.eof()) {
		getline(is, s[z]);
		z++;
	}
	is.close();

	for (int c = 0; c < z; c++) {
		int i;
		if (s[c][0] == '2' && s[c][1] == ' ') {
			p1[c] = s[c][0];
			if (s[c][3] == ' ' && s[c][2] == '2') {
				p2[c] = s[c][2];
				i = 4;
			}
			else {
				if (s[c][1] == ' ' && s[c][2] == '1' && s[c][4] == ' ' && (s[c][3] == '0' | s[c][3] == '6')) {
					p2[c] = s[c][2];
					p2[c] += s[c][3];
					i = 5;
				}
				else {
					i = 2;
				}
			}
		}
		if (s[c][0] == '1' && s[c][2] == ' ') {
			p1[c] += s[0][0];
			p1[c] += s[c][1];
			if (s[c][2] == ' ' && s[c][3] == '2' && s[c][4] == ' ') {
				p2[c] += s[c][3];
				i = 5;
			}
			else {
				if (s[c][2] == ' ' && s[c][5] == ' ' && s[c][3] == '1' && (s[c][3] == '6' | s[c][3] == '0')) {
					p2[c] += s[c][3];
					p2[c] += s[c][2];
					i = 6;
				}
				else {
					i = 3;
				}
			}
		}

		if (s[c][i] == '~') {
			sign[c] = s[c][i];
			i += 2;
		}


		for (i; s[c][i] != ' ' && i < s[c].length(); i++) {
			opr1[c] += s[c][i];
		}
		i++;
		if (i >= s[c].length())
			continue;
		for (i; s[c][i] != ' '&& i < s[c].length(); i++) {
			sign[c] += s[c][i];
		}
		i++;
		if (i >= s[c].length())
			continue;
		for (i; i < s[c].length(); i++) {
			opr2[c] += s[c][i];
		}
	}

	Qint b1;
	Qint b2;
	Qint kq;
	for (int c = 0; c < z; c++) {
		if (p1[c] == "2") {
			bool bit1[128] = { 0 };
			bool bit2[128] = { 0 };
			for (int j = 0; j < opr1[c].length(); j++) {
				bit1[127 - j] = opr1[c][opr1[c].length() - 1 - j] - '0';
			}
			for (int j = 0; j < opr2[c].length(); j++)
				bit2[127 - j] = opr1[c][opr2[c].length() - 1 - j] - '0';
			b1.BinToQint(bit1);
			b2.BinToQint(bit2);
		}


		if (p1[c] == "16") {
			char hex1[32];
			memset(hex1, '0', 32);
			char hex2[32];
			memset(hex2, '0', 32);
			for (int j = 0; j < opr1[c].length(); j++)
				hex1[31 - j] = opr1[c][opr1[c].length() - 1 - j];
			for (int j = 0; j < opr2[c].length(); j++)
				hex2[31 - j] = opr2[c][opr2[c].length() - 1 - j];
			bool *bit1 = StringHexToBin(hex1);
			bool *bit2 = StringHexToBin(hex2);
			b1.BinToQint(bit1);
			b2.BinToQint(bit2);
		}

		if (p1[c] == "10") {
			bool *bit1 = StringDecToBin(opr1[c]);
			bool *bit2 = StringDecToBin(opr2[c]);
			b1.BinToQint(bit1);
			b2.BinToQint(bit2);
		}

		if (sign[c] == "+")
			kq = b1 + b2;
		if (sign[c] == "-")
			kq = b1 - b2;
		//if (sign[c] == "*")
		//	kq = b1 * b2;
		//if (sign[c] == "/")
		//	kq = b1 / b2;
		if (sign[c] == "~")
			kq = ~b1;
		if (sign[c] == "<<")
			kq = b1 << b2;
		if (sign[c] == ">>")
			kq = b1 >> b2;
		if (sign[c] == "ror")
			kq = b1.Qint_ror();
		if (sign[c] == "rol")
			kq = b1.Qint_rol();
		if (sign[c] == "") {
			kq = b1;
		}


		bool kqbit[128] = { 0 };
		kq.QintToBinary(kqbit);

		os.open("output.txt", ios::out);

		if ((p1[c] == "2" && p2[c] == "") | p2[c] == "2") {
			for (int i = 0; i < 128; i++)
				cout << kqbit[i];
		}

		if ((p1[c] == "10" && p2[c] == "") | p2[c] == "10") {
			string kqdec = BinToDec(kqbit);
			cout << kqdec;
		}

		if ((p1[c] == "16" && p2[c] == "") | p2[c] == "16") {
			char *kqhex = BinToHex(kqbit);
			for (int i = 0; i < 32; i++)
				cout << kqhex[i];
		}

		cout << endl;
	}


	os.close();

	return;
}
