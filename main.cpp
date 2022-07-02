#include <iostream>
#include <fstream>
#include<cstring>
#include<stdlib.h>
#include<ctype.h>
#include<array>
#include<string>
#include<vector>
using namespace std;


array<string, 17> keyword = { "INT", "CHAR", "BLN", "FLT", "DBL", "VOID", "STR", "CONST", "main",
				  			  "IN", "OUT", "return", "std", "iostream", "endl", "IF", "ELSE" };
array<string, 19> op = { "+", "-", "*", "/",  "^",  "&&",  "||",  "=",  "==",  "&",  "|",  "%", "++",  "--", "+=", "-=", "/=", "*=", "%=" };
array<string, 18> sym = { "(", "{", "[", ")", "}", "]", "<", ">", "()", ";", "<<", ">>", ",", "#", ",", "~", "#", "@" };

string legal_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_";
string nums = "1234567890";

vector<string> lex;
vector<string> :: iterator i;
vector<string> lexical_errors;

bool isKeyword (string a){

	for (int i = 0; i < 17; i++)
	{
		if (keyword[i] == a)
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

 // identifier error symbol(s) on the identifier
bool islexicalerror(string a){
    if (a.find_first_not_of(legal_chars) != string::npos){
    	return true;
	} else {
		return false;
	}
} 

	// identifier cannot start with a number (conflict)
bool islexicalerror_2 (string a){
	for(int i = 0; i < nums.length(); i++){
		if(a.at(0) == nums[i]){
			return true;
		} else {
			return false;
		}
	}
}

void view_lexical_errors(){
	for (i = lexical_errors.begin(); i != lexical_errors.end(); ++i){		
		if(i == lexical_errors.end() - 1){
			cout << *i <<"\n";
		} 
	}
}
    

void parser(string str){
		string s="";
		int len = str.length();
		bool read_str_lit = false;
		
	
		
	for (int i = 0; i < len; i++)
	{
		if (read_str_lit == true)
		{
			s+= str[i];
			if (str[i] == '\"')
			{
				read_str_lit = false;
				lex.push_back(s);
				cout << s <<" is a string literal";
				s = "";
			}
			continue;
		}	
		
		if (str[i] == '\"')
		{
			read_str_lit = true;
			s+= str[i];
			continue;
		}
		
		if (str[i] != ' ')
		s += str[i];

	else {
		if (isOperator(s))
	{
		lex.push_back(s);
		cout << s <<" is an operator" << endl;
		s = "";
	}

	else if (isKeyword (s)) {
		
		lex.push_back(s);
		cout << s <<" is a keyword" << endl;
		s = "";
	}
	
	else if (isSymbol(s))
	{
		lex.push_back(s);
		cout << s <<" is a symbol" << endl;
		s = "";
	}
	
	else if (s == "\n" || s == "" || s == "")
	{
		cout << endl;
		s = "";
	}
	
	else if (isdigit (s[0])) //conflict aayusin pa
	{
		int x = 0;
			if (!isdigit (s[x++]))
				{
					continue;
				} 
		else
		{
			lex.push_back(s);
			cout << s <<" is a number" << endl;
			s = "";
		}
	}
	
	else {
		lex.push_back(s);
		
		if(islexicalerror(s) || islexicalerror_2(s)){
			lexical_errors.push_back(s);
			cout << s << " is an lexical error\n";
		} else {
			cout << s <<" is an identifier" << endl;
		}
		s = "";
			}

		}
	}
	
	cout<<endl;
	for (i = lex.begin(); i != lex.end(); ++i){
		
		if(i == lex.end() - 1){
			cout << *i;
		} else {
			cout << *i << ", ";
		}
	}
	
}

int main(){
    
    int menu;
    char switchloop;
    string filename, extension = ".txt";
    string x;
	string code="";
	
    do{
	
	cout << "1: Upload text file\n" 
		 << "2: View Lexemes and tokens\n" 
		 << "3: View Lexical errors\n" 
		 << "4: View Syntax errors\n"
		 << "5: View Semantic errors\n" 
		 << "6: Exit\n" 
		 << "Please select an option: ";
    cin >> menu;
    
    switch(menu){
        case 1:{//upload text file
        
			cout<<"please input file name: ";
			cin>>filename;
			filename.append(extension);
			
			ifstream file(filename.c_str());
			
			if(!file.fail()){
				while (getline(file, x)){
					code+=x;
					}	
			cout<< filename <<" file successfully uploaded\n";
			} 
			else {
				cout << "Error file not found...\n";
			}
			
			file.close();
			break;
		}
        
        case 2:{ // lexemes tokens
            cout << "View lexemes and tokens\n";
        			
            parser(code + ' ');
        
            break;
        }
        case 3:{ // lexical errors
            cout << "Lexical errors...\n";
            view_lexical_errors();
            break;
        }
        case 4:{ // syntax errors
            cout << "View Syntax errors";
            break;
        }
        case 5:{ // semantic errors
            cout << "View Semantic errors";
            break;
        }
        case 6:{ // exit
            cout<<"Exit";
            break;
        }
        
        
        default:{
        	cout <<"Invalid input \n";
			break;
		} 
        	
    }
    
    cout<<"\n";
    cout<<"Try Again?  Y/N \n";
	cin >> switchloop;
	//system("cls");
	
    }
	while(switchloop == 'Y' || switchloop == 'y');
	
    return 0;
}

