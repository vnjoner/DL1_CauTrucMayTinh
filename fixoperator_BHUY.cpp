string toBinary(unsigned long long n) {
    string kq;
    while (n != 0) {
        kq = (n % 2 == 0 ? "0" : "1") + kq;
        n /= 2;
    }
    while (kq.size() < 32){
        kq = "0" + kq;
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
    
    Qint kq;
    
    string s1 = toBinary(a4) + toBinary(a3) + toBinary(a2) + toBinary(a1);
    string s2 = toBinary(x.a4) + toBinary(x.a3) + toBinary(x.a2) + toBinary(x.a1);
    
    string kqstring = addBinary(s1, s2); // tinh toan
    
    bool *kqbool = new bool[kqstring.size()];//mang kq
    
    for (int i = 0; i < kqstring.size(); i++) {
        kqbool[i] = kqstring[i] - '0';//chuyen thanh char
    }
    
    kq.BinToQint(kqbool);
    return kq;
}


Qint Qint::operator-(Qint x) {
    
    /* operator - theo quy tac chuyen so thu 2 sang dang bu` 2's sau do thuc hien phep cong nhu thuong le*/
    /* cac buoc thuc hien giong nhu operator + */
    
    Qint kq;
    
    string s1 = toBinary(a4) + toBinary(a3) + toBinary(a2) + toBinary(a1);
    string s2 = toBinary(x.a4) + toBinary(x.a3) + toBinary(x.a2) + toBinary(x.a1);
    
    //a+(~b + 1)
    DaoBit(s2); //dao bit b
    s2 = addBinary(s2, "1"); //cong them 1 thanh dang bu 2
    
    string kqstring = addBinary(s1, s2); //cong nhau
    kqstring.erase(kqstring.begin()); // xoa bit dau = kq
    
    bool *kqbool = new bool[kqstring.size()];
    
    for (int i = 0; i < kqstring.size(); i++) {
        kqbool[i] = kqstring[i] - '0';
    }
    
    kq.BinToQint(kqbool);
    return kq;
}
