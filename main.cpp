#include <iostream>
#include <fstream>
#include<cstring>
#include<stdlib.h>
#include<ctype.h>
#include<array>
#include<string>
#include<vector>
#include <algorithm>
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
	}
	 else {
		return false;
	}
} 

//identifer cannot start with number(s)
bool invalid_identifier(string a){
	
	if (!((a[0] >= 'a' && a[0] <= 'z') || 
		  (a[0] >= 'A' && a[0] <= 'Z') || 
		   a[0] == '_')){
          	return true;		
		} 
		else 
		{
		 return false;
		}    
}

bool is_number(string a){
	string::const_iterator it = a.begin();
    while (it != a.end() && isdigit(*it)) ++it;
    return !a.empty() && it == a.end();
}

void view_lexical_errors(){
	for (i = lexical_errors.begin(); i != lexical_errors.end(); ++i){		
		cout << *i <<"\n";
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
		cout << s <<" is an operator\n";
		s = "";
	}

	else if (isKeyword (s)) {
		
		lex.push_back(s);
		cout << s <<" is a keyword\n";
		s = "";
	}
	
	else if (isSymbol(s))
	{
		lex.push_back(s);
		cout << s <<" is a symbol\n";
		s = "";
	}
	
	else if (s == "\n" || s == "" || s == "")
	{
		cout << "\n";
		s = "";
	}
	
	else if (isdigit (s[0])) 
	{
		int x = 0;
		string s_copy = s;
		s_copy.erase(remove(s_copy.begin(), s_copy.end(), '.'), s_copy.end()); // to remove '.' from floating point numbers temporarily
			if (!isdigit (s[x++]))
			{
				continue;
			}
			else if(invalid_identifier(s) && !(is_number(s_copy))){ //if identifier has numbers at the start
				lexical_errors.push_back(s);
				cout << s << " is a lexical error\n";
				s = "";
			}

			else
			{
				lex.push_back(s);
				cout << s <<" is a number\n";
				s = "";
			}
	}
	
	else {
		lex.push_back(s);
		if(islexicalerror(s)){
			lexical_errors.push_back(s);
			cout << s << " is an lexical error\n"; //if identifier has symbol(s)
		} else {
			cout << s <<" is an identifier\n";
		}
		s = "";
			}

		}
	}
	
	int cnt = 0;
	cout<<endl;
	for (i = lex.begin(); i != lex.end(); ++i){
		cnt++;
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
        	if(lexical_errors.empty()){
				cout<<"No errors found...\n";
		    } else {
		    	cout << "Lexical errors...\n";
            	view_lexical_errors();
			}
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


