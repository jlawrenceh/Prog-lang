#pragma once

#include <iostream>
#include <fstream>
//#include <cstring>
#include <stdlib.h>
#include <ctype.h>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


array<string, 17> keyword = { "INT", "CHAR", "BLN", "FLT", "DBL", "VOID", "STR", "CONST", "main",
				  			  "IN", "OUT", "return", "std", "iostream", "endl", "IF", "ELSE" };
				  			
array<string, 19> op = { "+", "-", "*", "/",  "^",  "&&",  "||",  "=",  "==",  "&",  "|",  "%", "INC",  "DEC", "+=", "-=", "/=", "*=", "%=" };
array<string, 17> sym = { "(", "{", "[", ")", "}", "]", "<", ">", "()", ";", "<<", ">>", ",", "#", ",", "#", "@" };

string legal_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_";
string nums = "1234567890";

vector<pair<string,string>> tokens;
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
	
	for (int i = 0; i < 17; i++)
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
				//cout << s <<" is a string literal";
				tokens.push_back({s,"string literal"});
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
	
	else if (s == "~")
	{
		lex.push_back(s);
			tokens.push_back({s,"terminator"});
		s = "";
	}
	else if (isOperator(s))
	{
		lex.push_back(s);
	//	cout << s <<" is an operator\n";
		tokens.push_back({s,"operator"});
		s = "";
	}

	else if (isKeyword (s)) {
		
		lex.push_back(s);
		tokens.push_back({s,"keyword"});
	//	cout << s <<" is a keyword\n";
		s = "";
	}
	
	else if (isSymbol(s))
	{
		lex.push_back(s);
		tokens.push_back({s,"symbol"});
	//	cout << s <<" is a symbol\n";
		s = "";
	}
	
	else if (s == "\n" || s == "" || s == "")
	{
	//	cout << "\n";
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
				s = "";
			}

			else
			{
				lex.push_back(s);
				if(s==s_copy)
				{
						tokens.push_back({s,"integer"});
				}
				else
				{
						tokens.push_back({s,"double"});
				}
				s = "";
			}
	}

	
	else {
		lex.push_back(s);
		tokens.push_back({s,"identifier"});
		if(islexicalerror(s)){
			lexical_errors.push_back(s);
	//		cout << s << " is an lexical error\n"; //if identifier has symbol(s)
		} 
		s = "";
			}

		}
	}
	

void parser_clear()
{
	tokens.clear();
	lex.clear();
	lexical_errors.clear();
}

vector<string> data_types = {"INT", "CHAR", "BLN", "FLT", "DBL", "VOID", "STR"};

vector<string> literals = {"string literal","integer","double"};
vector<pair<string, string>> assign; // assignment syntax 
bool check;
/*
struct{
	int var;
}type_INT[]{};
int type_INT_inst = -1;

struct {
	char var;
}type_CHAR[]{};
int type_CHAR_inst = -1;

struct 
{
	bool var;
}type_BLN[]{};
int type_BLN_inst = -1;

struct 
{
	float var;
}type_DBL[]{};
int type_DBL_inst = -1;

struct 
{
	string var;
}type_STR[]{};
int type_STR_inst = -1;
*/

bool isMatched(string _type, string _val)
{
	if(
		((_type == "INT") && (_val == "integer")) || 
		(_type == "DBL") && (_val == "double") || 
		(_type == "STR") && (_val == "string literal")
	  ) 
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void assignment()
{
	
        	for(auto it = tokens.begin(); it!=tokens.end();it++)
        	{
        		if(it->second == "keyword")
        		{
        		//	cout << it->first << endl;
        			//auto nx =std :: next(it, 2);
        			
        			for(auto it2 = data_types.begin(); it2!=data_types.end();it2++)
        			{
        				if(it->first == *it2) // check if the keyword is a data type
        				{
        					assign.push_back({it->first,it->second});
        					check = true; //  if the keyword is a data type, check = true;
        			//		cout << it->first << "\t" << it->second << endl;
        					break;
						}
					}
					
					if (check == true)
					{
						check = false;
						auto nx = next(it,1);
						if(nx->second == "identifier") // check if the token next to data type is an identifier
						{
							assign.push_back({nx->first,nx->second});
					//		cout << nx->first << "\t" << nx->second << endl;
							nx++;
		        			if(nx->first == "=") // check if the token next to identifier is an assignment operator
		        			{
		        				assign.push_back({nx->first,nx->second});
		        	//			cout << nx->first << "\t" << nx->second << endl;
		        				nx++;
		        				for(auto it3 = literals.begin(); it3!=literals.end();it3++)
		        				{
		        					if(nx->second == *it3) // check if the token next an assignment operator is a literal
		        					{
		        						check = true; 
		        						assign.push_back({nx->first,nx->second});
		        	//					cout << nx->first << "\t" << nx->second << endl;
		        						break;
									}
								}
								
								if(check == true)
								{
									
									cout << endl;
									auto ptr_type = assign.begin(); // point at the type which is at index 0
									auto ptr_name = next(ptr_type,1); // point at the name which is at index 1
									//auto ptr_assign = next(ptr_type,2; // point at the equal sign at index 2
									auto ptr_val = next(ptr_type,3); // point to the value which is at index 3
									
									//cout << ptr_type->first << " " << ptr_name->first << " " << ptr_val->first << endl;
								
									
									if(!isMatched(ptr_type->first, ptr_val->second))
									{
										
										for(auto it4 = assign.begin(); it4!=assign.end();it4++)
										{
											cout<<it4->first << "\t" << it4->second << endl;
										}
										cout << "type mismatch" << endl << endl;
									}
									assign.clear();
									
								}
							}
							else continue;
						}
						else
						{
							continue;
						}
					}
					else
					{
						continue;
					}
	
				}
				
	
						
	}
}

bool keyword_error(){
					       	for(auto it = tokens.begin(); it!=tokens.end();it++){
				       		auto next_it = next(it, 1);
				        	if(it->second == "identifier" && next_it ->second == "identifier"){
								if(!isKeyword(it->first)){
									lexical_errors.push_back(it->first);
									return true;
								}
								
							}
						}	
}





