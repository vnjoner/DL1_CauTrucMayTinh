#include"KTMT.h"

//void PrintQint(Qint x)
//{
//	
//}

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

bool *StringHexToBin(char *hex)
{
	long int i = 0;
	/*string hex = ConvertCharToString(hex);*/
	string BinaryString = "";
	for (i = 0; i <sizeof(hex) ; i++)
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
		else if (hex[i] == 'a'||hex[i]=='A')
			BinaryString += "1010";
		else if (hex[i] == 'b'||hex[i]=='B')
			BinaryString += "1011";
		else if (hex[i] == 'c'||hex[i]=='C')
			BinaryString += "1100";
		else if (hex[i] == 'd'||hex[i]=='D')
			BinaryString += "1101";
		else if (hex[i] =='e'||hex[i]=='E')
			BinaryString += "1110";
		else if (hex[i] == 'f'||hex[i]=='F')
			BinaryString += "1111";
	}
	bool *kq = new bool[128];
	memset(kq, 0, 128);
	for (int j = 0 ; j <sizeof(kq); j++)
	{
		kq[j] = BinaryString[j] - '0';
	}
	
	return kq;
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
	char *Hexa = new char;
	memset(Hexa, 0, 32);
	for (int i = 0; i <sizeof(Hexa); i++)
	{
		Hexa[i] = HexaString[i];
	}
	return Hexa;
}






int main()
{
	char hex[100];
	cout << "nhap hex:";
	cin >> hex;
	cout<<StringHexToBin(hex);
	cout << endl;


	system("pause");
	return 0;
}
