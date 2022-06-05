#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<ctype.h>
#include<fstream>
#include<array>
#include<string>
using namespace std;

array<string, 14> arr = { "INT", "CHAR", "BLN", "FLT", "DBL", "VOID", "STR", "main",
				  "IN", "OUT", "return", "std", "iostream", "endl" };
				  
array<string, 19> op = { "+", "-", "*", "/",  "^",  "&&",  "||",  "=",  "==",  "&",  "|",  "%", "++",  "--", "+=", "-=", "/=", "*=", "%=" };
array<string, 18> sym = { "(", "{", "[", ")", "}", "]", "<", ">", "()", ";", "<<", ">>", ",", "#", ",", "~", "#", "@" };

bool isKeyword (string a){

	for (int i = 0; i < 14; i++)
	{
		if (arr[i] == a)
		{
			return true;
		}
	}
	
	return false;
}

bool isOperator (string a){
	
	for (int i = 0; i < 19; i++)
	{
		if (op[i] == a)
		{
			return true;
		}
	}
	
	return false;
}

bool isSymbol (string a){
	
	for (int i = 0; i < 18; i++)
	{
		if (sym[i] == a)
		{
			return true;
		}
	}
	
	return false;
}

void parser(string str){
		string s="";
		int len = str.length();
		
	for (int i = 0; i < len; i++)
	{

		if (str[i] != ' ')
		s += str[i];

	else {
		if (isOperator(s))
	{
		cout << s <<" is an operator" << endl;
		s = "";
	}

	else if (isKeyword (s)) {
		cout << s <<" is a keyword" << endl;
		s = "";
	}
	
	else if (isSymbol(s))
	{
		cout << s <<" is a symbol" << endl;
		s = "";
	}
	
	else if (s == "\n" || s == "" || s == "")
	{
		cout << endl;
		s = "";
	}
	
	else if (isdigit (s[0]))
	{
		int x = 0;
			if (!isdigit (s[x++]))
				{
					continue;
				} 
		else
		{
			cout << s <<" is a number" << endl;
			s = "";
		}
	}
	
	else {
		cout << s <<" is an identifier" << endl;
		s = "";
			}

		}
	}
	
}

int main ()
{
	ifstream file("prog.txt");
	string x;
	string code="";

	while (getline(file, x)) {
		code+=x;
	}
	
	parser(code + ' ');

	return 0;
}


