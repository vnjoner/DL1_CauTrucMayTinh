#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
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





Qint::Qint() {
    a1 = 0;
    a2 = 0;
    a3 = 0;
    a4 = 0;
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

static int size1 = 0;/*  bien static dung` de nhan biet size cua mang bool*[], su dung kq ez hon */

/*    ham CONVERT he 10 -> 2    */

bool* StringDecToBin(string dec) {
    string kqString = "";
    if (dec == "0") {//neu bang 0 thi ngung
        return 0;
    }
    else {
        while (dec != "0") {//khi dang khac 0
            kqString = CHECKTanCungLe(dec) + kqString;
            dec = chiaHai(dec);
        }
    }
    bool *kq = new bool[kqString.size()];
    size1 = (int)kqString.size();//cap nhat size vao bien static de tien. su dung ket qua
    
    for (int i = 0; i < kqString.size(); i++) {
        kq[i] = kqString[i] - '0';
    }
    return kq;
}

void Qint::QintToBinary(bool bit[]) {// đổi từ 4 int ra dãy nhị phân, lưu thông qua tham chiếu bit[],
    //vd  123.32.2.12 -> bit[]={0,0,1,1,0,0,0,0,........./0,0,1,0,0,0,0,0......./0,0,0,0,0,1,0,0......../,1,1,0,1,1,1,1,0........}
    int i = 127;
    int b1 = abs(a1), b2 = abs(a2), b3 = abs(a3), b4 = abs(a4);
    while (b1 != 0) {
        bit[i--] = (b1 % 2 == 0 ? 0 : 1);
        b1 /= 2;
    }
    if (a1 < 0)
        bit[96] = 1;
    i = 95;
    while (b2 != 0) {
        bit[i--] = (b2 % 2 == 0 ? 0 : 1);
        b2 /= 2;
    }
    if (a2 < 0)
        bit[64] = 1;
    i = 63;
    while (b3 != 0) {
        bit[i--] = (b3 % 2 == 0 ? 0 : 1);
        b3 /= 2;
    }
    if (a3 < 0)
        bit[32] = 1;
    i = 31;
    while (b4 != 0) {
        bit[i--] = (b4 % 2 == 0 ? 0 : 1);
        b4 /= 2;
    }
    if (a4 < 0)
        bit[0] = 1;
}

void Qint::BinToQint(bool * bit)// dùng để lưu dãy nhị phân vào trong 4 int
{
    this->a4 = 0;
    for (int i = 1; i < 32; i++)
    {
        if (bit[i] == 1) {
            this->a4 += pow(2, 31 - i);
        }
    }
    if (bit[0] == 1)
        this->a4 *= -1;
    this->a3 = 0;
    for (int i = 33; i < 64; i++)
    {
        if (bit[i] == 1) {
            this->a3 += pow(2, 63 - i);
        }
    }
    if (bit[32] == 1)
        this->a3 *= -1;
    this->a2 = 0;
    for (int i = 65; i < 96; i++)
    {
        if (bit[i] == 1) {
            this->a2 += pow(2, 95 - i);
        }
    }
    if (bit[64] == 1)
        this->a2 *= -1;
    this->a1 = 0;
    for (int i = 97; i < 128; i++)
    {
        if (bit[i] == 1) {
            this->a1 += pow(2, 127 - i);
        }
    }
    if (bit[96] == 1)
        this->a1 *= -1;
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
    return Qint();
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
    return Qint();
}

Qint Qint::operator~()
{
    bool a[128] = { 0 };
    this->QintToBinary(a);
    for (int i = 0; i < 128; i++)
    {
        a[i] = (a[i] + 1) % 2;
    }
    return *this;
}


string BinToDec(bool *bit) {// Đáng lí ra type trả về là Qint và cắt thành 4 để
    //lưu trong 4 int, nhưng không đủ, có gì hỏi thì giải thích cho
    vector<int> temp;
    string a;
    int arr[40] = { 0 };
    int memo, dummy;
    if (bit[0] == 1)
        arr[0] = 1;
    temp.push_back(1);
    for (int i = 1; i < 127; i++)
    {
        memo = 0;
        for (int j = 0; j < temp.size(); j++)
        {
            int dummy = temp[j];
            temp[j] = (temp[j] * 2 + memo) % 10;
            memo = (dummy * 2 + memo) / 10;
        }
        if (memo != 0) {
            temp.push_back(memo);
        }
        memo = 0;
        if (bit[i] == 1) {
            for (int k = 0; k < temp.size(); k++)
            {
                dummy = arr[k];
                arr[k] = (arr[k] + temp[k] + memo) % 10;
                memo = (dummy + temp[k] + memo) / 10;
            }
            if (temp.size() < 40)
                arr[temp.size()] += memo;
        }
    }
    for (int i = 39; i >= 0; i--) {
        if (arr[i] != 0) {
            for (int j = 0; j <= i; j++)
            {
                a = (char)(arr[j] + 48) + a;
            }
            break;
        }
    }
    if (bit[127] == 1)
        a = '-' + a;
    return a;
}

Qint Qint::operator << (Qint a) {
    bool *dummy = NULL;
    this->QintToBinary(dummy);
    bool *dummy2 = NULL;
    a.QintToBinary(dummy2);
    int b = 0;
    for (int i = 0; i < 128; i++)
        if (dummy[i] == 1) {
            for (int j = i; j < 128; j++)
                b += pow(2, i);
            break;
        }
    for (int i = 0; i < 128; i++) {
        if (dummy[i] == 1) {
            for (int j = i; j < 128; j++)
                dummy[j - b] = dummy[j];
            for (int j = b; j >= 0; j--) {
                dummy[127 - b] = 0;
            }
            break;
        }
    }
    this->BinToQint(dummy);
    return *this;
}

Qint Qint::operator >> (Qint a) {
    bool *dummy = NULL;
    this->QintToBinary(dummy);
    bool *dummy2 = NULL;
    a.QintToBinary(dummy2);
    int b = 0;
    for (int i = 0; i < 128;i++)
        if (dummy[i] == 1) {
            for (int j = i; j < 128; j++)
                b += pow(2, i);
            break;
        }
    for (int i = b; i < 128; i++) {
        dummy[127 - i - b] = dummy[127 -i];
    }
    for (int i = 0; i < b; i++)
        dummy[i] = 0;
    this->BinToQint(dummy);
    return *this;
}

Qint Qint::Qint_rol() {
    bool *dummy = NULL;
    this->QintToBinary(dummy);
    bool kq[128] = { 0 };
    kq[127] = dummy[0];
    for (int i =1; i < 128; i++) {
        kq[127 - i] = dummy[127 - i + 1];
    }
    this->BinToQint(kq);
    return *this;
}

Qint Qint::Qint_ror() {
    bool *dummy = NULL;
    this->QintToBinary(dummy);
    bool kq[128] = { 0 };
    kq[0] = dummy[127];
    for (int i = 1; i < 128; i++) {
        kq[i] = dummy[i - 1];
    }
    this->BinToQint(kq);
    return *this;
}



string toBinary(unsigned long long n) {
    string kq;
    while (n != 0) {
        kq = (n % 2 == 0 ? "0" : "1") + kq;
        n /= 2;
    }
    return kq;
}

/*   ham cong hai so he 2, tra ve string   */
string addBinary(string a, string b) {
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
    
    while (index > 0 || s == 1) {
        //thuc hien tinh toan va` tinh carry tu` phan tu indexth -> 0th
        s = s + (getBit(a, index) + getBit(b, index));
        kq = (char)(s % 2 + '0') + kq;
        s /= 2;
        index--;
    }
    return kq;
}

/*  ham dao bit tu 0 -> 1, va nguoc lai, 1 -> 0 (operator -)  */
void DaoBit(string &s) {
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
    
    /* operator dung ham cong ben ngoai, nhan vao 2 string, tra ve 1 string, sau do chuyen sang Qint */
    /* s1,s2 la 2 string nhan vao, s1_1..4, s2_1..4 la 2 string con de check xem a1, a2, a3, a4 co ton tai khong */
    
    Qint kq;
    string s1, s2;
    if (this->a4) {
        string s1_1 = toBinary(this->a4);
        s1 = s1_1;
    }
    if (this->a3) {
        string s1_2 = toBinary(this->a3);
        s1 += s1_2;
    }
    if (this->a2) {
        string s1_3 = toBinary(this->a2);
        s1 += s1_3;
    }
    if (this->a1) {
        string s1_4 = toBinary(this->a1);
        s1 += s1_4;
    }
    if (x.a4) {
        string s2_1 = toBinary(x.a4);
        s2 = s2_1;
    }
    if (x.a3) {
        string s2_2 = toBinary(x.a3);
        s2 += s2_2;
    }
    if (x.a2) {
        string s2_3 = toBinary(x.a2);
        s2 += s2_3;
    }
    if (x.a1) {
        string s2_4 = toBinary(x.a1);
        s2 += s2_4;
    }
    
    string kqstring = addBinary(s1, s2); // tinh toan
    
    bool *kqbool = new bool[kqstring.size()];//mang kq
    
    for (int i = (int)kqstring.size() - 1; i > 0; i--) {
        kqbool[i] = kqstring[i] - '0';//chuyen thanh char
    }
    
    kq.BinToQint(kqbool);
    return kq;
}


Qint Qint::operator-(Qint x) {
    
    /* operator - theo quy tac chuyen so thu 2 sang dang bu` 2's sau do thuc hien phep cong nhu thuong le*/
    /* cac buoc thuc hien giong nhu operator + */
    
    Qint kq;
    string s1, s2;
    if (this->a4) {
        string s1_1 = toBinary(this->a4);
        s1 = s1_1;
    }
    if (this->a3) {
        string s1_2 = toBinary(this->a3);
        s1 += s1_2;
    }
    if (this->a2) {
        string s1_3 = toBinary(this->a2);
        s1 += s1_3;
    }
    if (this->a1) {
        string s1_4 = toBinary(this->a1);
        s1 += s1_4;
    }
    if (x.a4) {
        string s2_1 = toBinary(x.a4);
        s2 = s2_1;
    }
    if (x.a3) {
        string s2_2 = toBinary(x.a3);
        s2 += s2_2;
    }
    if (x.a2) {
        string s2_3 = toBinary(x.a2);
        s2 += s2_3;
    }
    if (x.a1) {
        string s2_4 = toBinary(x.a1);
        s2 += s2_4;
    }
    
    //a+(~b + 1)
    DaoBit(s2); //dao bit
    s2 = addBinary(s2, "1"); //cong them 1 thanh dang bu 2
    
    string kqstring = addBinary(s1, s2); //cong nhau ra kq
    kqstring.erase(kqstring.begin());
    
    bool *kqbool = new bool[kqstring.size()];
    
    for (int i = 0; i < kqstring.size(); i++) {
        kqbool[i] = kqstring[i] - '0';
    }
    
    kq.BinToQint(kqbool);
    
    return kq;
}


bool *StringHexToBin(char *hex)
{
    long int i = 0;
    while (hex[i])
    {
        switch (hex[i])
        {
            case '0':
                cout << "0000";
                break;
            case '1':
                cout << "0001";
                break;
            case '2':
                cout << "0010";
                break;
            case '3':
                cout << "0011";
                break;
            case '4':
                cout << "0100";
                break;
            case '5':
                cout << "0101";
                break;
            case'6':
                cout << "0110";
                break;
            case '7':
                cout << "0111";
                break;
            case '8':
                cout << "1000";
                break;
            case '9':
                cout << "1001";
                break;
            case 'a':
            case'A':
                cout << "1010";
                break;
            case 'B':
            case 'b':
                cout << "1011";
                break;
            case 'C':
            case 'c':
                cout << "1100";
                break;
            case 'D':
            case 'd':
                cout << "1101";
                break;
            case 'E':
            case 'e':
                cout << "1110";
                break;
            case 'F':
            case 'f':
                cout << "1111";
                break;
            default:
                cout << "\nkhong ton tai he so co 2" << endl;
                cout << hex[i];
                break;
        }
        i++;
    }
    bool* kq = new bool[strlen(hex)];
    int size = (int)strlen(hex);
    for (int i = 0; i< size; i++) {
        kq[i] = hex[i] - '0';
    }
    return kq;
}

string ConvertCharToString(char *ch)
{
    std::string str(ch);
    return ch;
}
char *ConvertboolToChar(bool *b)
{
    char *kq = new char(sizeof(b));
    for (int i = 0; i < sizeof(b); i++)
    {
        kq[i] = b[i] + '0';
    }
    return kq;
}
string ConvertBoolToString(bool *b)
{
    return ConvertCharToString(ConvertboolToChar(b));
}
char *BinToHex(bool *bit)
{
    string BinaryString = ConvertBoolToString(bit);
    string HexaString = "";
    for (int i = 0; i < BinaryString.length(); i += 4)
    {
        string str = BinaryString.substr(i, i + 4);
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
            HexaString += "8";
        else if (str == "1001")
            HexaString += "9";
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
    char *Hexa = new char[HexaString.length()];
    for (int i = 0; i < sizeof(Hexa); i++)
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
                bit2[127 - j]  = opr1[c][opr2[c].length() - 1 - j] - '0';
            b1.BinToQint(bit1);
            b2.BinToQint(bit2);
            b1.PrintQint();//in bộ nhớ của opr1
            b2.PrintQint();//in bộ nhớ của opr2
        }
        
        
        if (p1[c] == "16") {
            char hex1[32] = { 0 };
            char hex2[32] = { 0 };
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
        //    kq = b1 * b2;
        //if (sign[c] == "/")
        //    kq = b1 / b2;
        if (sign[c] == "<<")
            kq = b1 << b2;
        if (sign[c] == ">>")
            kq = b1 >> b2;
        if (sign[c] == "ror")
            kq = b1.Qint_ror();
        if (sign[c] == "rol")
            kq = b1.Qint_rol();
        
        bool kqbit[128] = { 0 };
        kq.QintToBinary(kqbit);
        kq.PrintQint();//in bộ nhớ của Qint
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






int main() {
    //ifstream is;
    //string s[100];
    //string opr1[100];
    //string opr2[100];
    //string sign[100];
    ////int size = 0;
    //string p1[100], p2[100];
    //int z = 0;
    
    
    
    //is.open("input.txt", ios::in);
    
    //while (!is.eof()) {
    //    getline(is, s[z]);
    //    z++;
    //}
    //is.close();
    
    
    //for (int c = 0; c < z; c++) {
    //    int i;
    //    if (s[c][0] == '2' && s[c][1] == ' ') {
    //        p1[c] = s[c][0];
    //        if (s[c][3] == ' ' && s[c][2] == '2') {
    //            p2[c] = s[c][2];
    //            i = 4;
    //        }
    //        else {
    //            if (s[c][1] == ' ' && s[c][2] == '1' && s[c][4] == ' ' && (s[c][3] == '0' | s[c][3] == '6')) {
    //                p2[c] = s[c][2];
    //                p2[c] += s[c][3];
    //                i = 5;
    //            }
    //            else {
    //                i = 2;
    //            }
    //        }
    //    }
    
    //    if (s[c][0] == '1' && s[c][2] == ' ') {
    //        p1[c] += s[0][0];
    //        p1[c] += s[c][1];
    //        if (s[c][2] == ' ' && s[c][3] == '2' && s[c][4] == ' ' ) {
    //            p2[c] += s[c][3];
    //            i = 5;
    //        }
    //        else {
    //            if (s[c][2] == ' ' && s[c][5] == ' ' && s[c][3] == '1' && ( s[c][3] == '6' | s[c][3] == '0')) {
    //                p2[c] += s[c][3];
    //                p2[c] += s[c][2];
    //                i = 6;
    //            }
    //            else {
    //                i = 3;
    //            }
    //        }
    //    }
    
    //    if (s[c][i] == '~') {
    //        sign[c] = s[c][i];
    //        i += 2;
    //        cout << "sign: " << sign[c] << endl;
    //    }
    
    
    //    for (i; s[c][i] != ' ' && i < s[c].length(); i++) {
    //        opr1[c] += s[c][i];
    //    }
    //    cout << "opr1: ";
    //    cout << opr1[c] << endl;
    //    i++;
    //    if (i >= s[c].length())
    //        continue;
    //    for (i; s[c][i] != ' '&& i < s[c].length(); i++) {
    //        sign[c] += s[c][i];
    //    }
    //    cout << "sign: " << sign[c] << endl;
    //    i++;
    //    if (i >= s[c].length())
    //        continue;
    //    for (i; i < s[c].length(); i++) {
    //        opr2[c] += s[c][i];
    //    }
    //    cout << "opr2: " << opr2[c] << endl << endl;
    //}
    
    
    
    ofstream os;
    ifstream is;
    QintFile(is, os);
}



