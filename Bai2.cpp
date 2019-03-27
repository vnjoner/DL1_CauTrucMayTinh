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

//PHAN CUA BHUY MOI ADD VAO
//START HERE
bool IS_EndWithTarget(const string &s, const string &target){
    //(danh cho function chuyen 10 sang 2)
    if (s.size() >= target.size() && s.compare(s.size() - target.size()/*bat dau*/, target.size()/*length kiem tra*/, target/*chuoi can kiem tra*/) == 0){
        return true;
    }
    return false;
}

/*   ham check tan cung cua 1 string (he 10) co la so le hay khong   */
string CHECKTanCungLe(string s){// tan cung la so le thi tra ve "1", else "0" (danh cho chuyen 10 sang 2)
    if (IS_EndWithTarget(s, "1") || IS_EndWithTarget(s, "3") || IS_EndWithTarget(s, "5") || IS_EndWithTarget(s, "7") || IS_EndWithTarget(s, "9")){
        return "1";
    }
    return "0";
}

/***** chia 2, type string, khong dung phep toan ****/
string chiaHai(string s)
{
    string kq;
    
    int index = 0;
    int temp = s[index] - '0';
    while (temp < 2)
        temp = temp * 10 + (s[++index] - '0');
    
    // Lien tuc lay temp chia 2
    // Sau moi lan chia, tmp them 1 chu so
    while (s.size() > index){
        // luu kq
        kq += (temp / 2) + '0';
        temp = (temp % 2) * 10 + s[++index] - '0';
    }
    
    if (kq.length() == 0)
        return "0";
    
    return kq;
}

/*    ham CONVERT he 10 -> 2 NGUYEN   */
string StringDecToBin(string dec){
    string kqString = "";
    
    int flag = 0;
    if (dec[0] == '-'){
        flag = 1;
        dec.erase(dec.begin());
    }
    
    if (dec == "0"){//neu bang 0 thi ngung
        return 0;
    }
    else {
        while (dec != "0"){//khi dang khac 0
            kqString = CHECKTanCungLe(dec) + kqString;
            dec = chiaHai(dec);
        }
    }
    while (kqString.size() < 15){
        kqString = "0" + kqString;
    }
    
    if (flag == 1){
        kqString = "1" + kqString;
    }
    
    return kqString;
}

/*DESCLAIMER: Ham nhan 2, ham chi dung khi parse vao cac string so trong khoang (0, 1)*/
string nhanHai(string decFloat){
    string kq;
    
    int tmp = 0;
    int index = (int)decFloat.size() - 1; //5
    int carry = 0;
    
    
    while (index >= 0){
        if (decFloat[index] == '.'){
            index--;
            continue;
        }
        tmp = decFloat[index] - '0'; //5
        tmp *= 2;
        
        if (index == 0 && tmp >= 10){
            kq += tmp % 10 + carry + '0';
            kq += tmp / 10 + '0';
            break;
        }
        
        
        kq += tmp % 10 + carry + '0';
        if (tmp >= 10){
            carry = 1;
        }
        else {
            carry = 0;
        }
        index--;
    }
    reverse(kq.begin(), kq.end());
    kq.insert(1, ".");
    
    return kq;
}

bool *DecToBin(string sFLOAT){
    string i_Part = "";//phan nguyen
    string f_Part = "";//phan cham dong
    
    for (int i = 0; i < (int)sFLOAT.find_first_of("."); i++){//truoc dau .
        i_Part += sFLOAT[i];
    }
    //re-use ham stringdectobin ben Qint
    string bin_i_part = StringDecToBin(i_Part);//chuyen nguyen sang bin
    
    for (int i = (int)sFLOAT.find_first_of("."); i < sFLOAT.size(); i++){
        f_Part += sFLOAT[i];//sau dau .
    }
    
    f_Part = "0" + f_Part;//ra dang 0.xx
    
    string bin_f_part = "";
    //chuyen tp sang bin
    while (f_Part != "0"){
        f_Part = nhanHai(f_Part);
        bin_f_part += f_Part[0];
        if (f_Part[0] == '1'){
            f_Part[0] = '0';
        }
        if (bin_f_part.size() == 112){
            break;
        }
    }
    
    string kqreal = bin_i_part + bin_f_part; //kq string
    //chuyen kqstring qua bool
    bool *kq = new bool[128];//convert into bin
    for (int i = 0; i < 128; i++){
        kq[i] = kqreal[i] - '0';
    }
    return kq;
}
//phan comment duoi la fix operator bai 1
//string toBinary(unsigned long long n) {
//    string kq;
//    while (n != 0) {
//        kq = (n % 2 == 0 ? "0" : "1") + kq;
//        n /= 2;
//    }
//    while (kq.size() < 32){
//        kq = "0" + kq;
//    }
//    return kq;
//}
//
///*   ham cong hai so he 2, tra ve string   */
//string addBinary(string a, string b) {
//    while (a.size() > b.size()) { // them so 0 cho ngang size
//        b = "0" + b;
//    }
//
//    while (a.size() < b.size()) { //them so 0 cho ngang size
//        a = "0" + a;
//    }
//
//    //lay index = length max vi index string kq se chay tu max ve 0
//    int index = (int)a.size() - 1 > (int)b.size() - 1 ? (int)a.size() - 1 : (int)a.size() - 1;
//    int s = 0;
//
//    string kq = "";// khoi tao bien luu ket qua
//
//    while (index > 0 || s == 1) {
//        //thuc hien tinh toan va` tinh carry tu` phan tu indexth -> 0th
//        s = s + (getBit(a, index) + getBit(b, index));
//        kq = (char)(s % 2 + '0') + kq;
//        s /= 2;
//        index--;
//    }
//    return kq;
//}
//
///*  ham dao bit tu 0 -> 1, va nguoc lai, 1 -> 0 (operator -)  */
//void DaoBit(string &s) {
//    for (int i = 0; i < s.size(); i++) {
//        if (s[i] == '1') {
//            s[i] = '0';
//        }
//        else if (s[i] == '0') {
//            s[i] = '1';
//        }
//    }
//}
//
//Qint Qint::operator+(Qint x) {
//
//    /* operator dung ham cong ben ngoai, nhan vao 2 string, tra ve 1 string, sau do chuyen sang Qint */
//
//    Qint kq;
//
//    string s1 = toBinary(a4) + toBinary(a3) + toBinary(a2) + toBinary(a1);
//    string s2 = toBinary(x.a4) + toBinary(x.a3) + toBinary(x.a2) + toBinary(x.a1);
//
//    string kqstring = addBinary(s1, s2); // tinh toan
//
//    bool *kqbool = new bool[kqstring.size()];//mang kq
//
//    for (int i = 0; i < kqstring.size(); i++) {
//        kqbool[i] = kqstring[i] - '0';//chuyen thanh char
//    }
//
//    kq.BinToQint(kqbool);
//    return kq;
//}
//
//
//Qint Qint::operator-(Qint x) {
//
//    /* operator - theo quy tac chuyen so thu 2 sang dang bu` 2's sau do thuc hien phep cong nhu thuong le*/
//    /* cac buoc thuc hien giong nhu operator + */
//
//    Qint kq;
//
//    string s1 = toBinary(a4) + toBinary(a3) + toBinary(a2) + toBinary(a1);
//    string s2 = toBinary(x.a4) + toBinary(x.a3) + toBinary(x.a2) + toBinary(x.a1);
//
//    //a+(~b + 1)
//    DaoBit(s2); //dao bit b
//    s2 = addBinary(s2, "1"); //cong them 1 thanh dang bu 2
//
//    string kqstring = addBinary(s1, s2); //cong nhau
//    kqstring.erase(kqstring.begin()); // xoa bit dau = kq
//
//    bool *kqbool = new bool[kqstring.size()];
//
//    for (int i = 0; i < kqstring.size(); i++) {
//        kqbool[i] = kqstring[i] - '0';
//    }
//
//    kq.BinToQint(kqbool);
//    return kq;
//}


//ENDS HERE



