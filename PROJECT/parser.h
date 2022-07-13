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
#include <regex>

using namespace std;


vector<string> data_types = {"INT", "CHAR", "BLN", "FLT", "DBL", "STR", "VOID"};							
vector<string> arithmetic = {"+", "-", "*", "/", "%", "INC", "DEC"};
vector<string> assignment = {"=", "+=", "-=",  "*=",  "/=",  "%="};
vector<string> relational = {"==", "!=", ">", "<", ">=", "<="};
vector<string> logical = {"AND", "OR", "NOT",};
vector<string> keywords = { "OUT", "IN", "IF-ELSE", "FLOOP", "DLOOP", "WLOOP", "IF", "ELSE"};
vector<string> symbols =  { "(", "{", "[", ")", "}", "]", ",", "#", "@"};
string terminator = "~";

string legal_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890_";
string nums = "1234567890";

vector<pair<string,string>> tokens;
vector<string> lexemes;
vector<string> :: iterator i;
vector<pair<int, string>> lexical_errors;
vector<string> declared_vars;

unsigned int line_no = 0;

bool is_DataType(string a);
bool is_Arithmetic(string a);
bool is_Assignment(string a);
bool is_Relational(string a);
bool is_Logical(string a);
bool is_Keyword(string a);
bool is_Symbol(string a);
void parser(string str);

bool is_DataType(string a){
	for(auto itr : data_types)
	{
		if(itr == a)
			return true;
	}
	return false;
}

bool is_Arithmetic(string a){
	for(auto itr : arithmetic)
	{
		if(itr == a)
			return true;
	}
	return false;
}

bool is_Assignment(string a){
	for(auto itr : assignment)
	{
		if(itr == a)
			return true;
	}
	return false;
}

bool is_Relational(string a){
	for(auto itr : relational)
	{
		if(itr == a)
			return true;
	}
	return false;
}

bool is_Logical(string a){
	for(auto itr : logical)
	{
		if(itr == a)
			return true;
	}
	return false;
}

bool is_Keyword(string a){
	for(auto itr : keywords)
	{
		if(itr == a)
		{
			return true;
		}
	}
	
	return false;
}

bool is_Symbol(string a){
		for(auto itr : symbols)
	{
		if(itr == a)
			return true;
	}
	return false;
}

bool is_Number(string a){
	string::const_iterator it = a.begin();
    while (it != a.end() && isdigit(*it)) ++it;
    return !a.empty() && it == a.end();
}

 // identifier error symbol(s) on the identifier
 /*
bool isLexicalError(string a){
    if (a.find_first_not_of(legal_chars) != string::npos){
    	return true;
	}

	return false;
}
*/

bool isLexicalError(string a){
    regex pattern("[a-zA-Z_][0-9a-zA-Z_]{0,19}");
    regex pattern2("[0-9]+[.]*[0-9]*"); //to check if the token is just a number
    
    bool match = regex_match(a, pattern);
    bool match2 = regex_match(a, pattern2);
    
    if(match || match2){
    	return false;
	} 
	
	return true;
}

void view_lexical_errors(){
	
	sort(lexical_errors.begin(), lexical_errors.end());

	
	for (auto it : lexical_errors){		
		cout<<"Error at line " << it.first << " " << "\"" << it.second << "\"\n";
	}
}

bool is_declared(string &a){ //to check if the identifer is declared
	for(auto i = declared_vars.begin(); i != declared_vars.end(); ++i){		
		if(a == *i){
			return true;
		}
	}
	return false;
}

void view_declared_vars(){
	for (i = declared_vars.begin(); i != declared_vars.end(); ++i){		
		cout << *i <<"\n";
	}	
}

void parser(string str){
	string s = "";
	int len = str.length();
	bool read_str_lit = false;
	bool read_char_lit = false;
	
	line_no++;
	
	for (int i = 0; i < len; i++)
	{
			// tells the parser that it is currently reading a type string.
		if (read_str_lit == true) 
		{
			s+= str[i];
			if (str[i] == '\"')
			{
				read_str_lit = false;
				lexemes.push_back(s);
				tokens.push_back({s,"string literal"});
				s = "";
			}
			continue;
		}
			// tells the parser that it will start reading a type string.
		if (str[i] == '\"') 
		{
			read_str_lit = true;
			s+= str[i];
			continue;
		} 
		
			// tells the parser that it is currently reading a type char
		if (read_char_lit == true) 
		{
			s+= str[i];
			if (str[i] == '\'')
			{
				read_char_lit = false;
				lexemes.push_back(s);
				tokens.push_back({s,"character"});
				s = "";
			}
			continue;
		}
			// tells the parser that it will start reading a type char.
		if (str[i] == '\'')
		{
			read_char_lit = true;
			s+=str[i];
			continue;
		}
		
		
		if(str[i] != ' ')
			s += str[i];
			
		else if (s == "~")
		{
			line_no++;
			lexemes.push_back(s);
			tokens.push_back({s, "terminator"});
			s = "";
		}
		
		else if (is_DataType(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "data type"});
			s = "";
		}
		
		else if (is_Arithmetic(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "arithmetic operator"});
			s = "";
		}
		
		else if (is_Assignment(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "assignment operator"});
			s = "";
		}
		
		else if (is_Relational(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "relational operator"});
			s = "";
		}
		
		else if (is_Logical(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "logical operator"});
			s = "";
		}
		
		else if (is_Keyword(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "keyword"});
			s = "";
		}
		
		else if (is_Symbol(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "symbol"});
			s = "";
		}
		
		else if (s == "\n" || s == "" || s == "")
		{
			s = "";
		}
		else if (isdigit(s[0]))
		{
			int x = 0;
			string s_copy = s;
			s_copy.erase(remove(s_copy.begin(), s_copy.end(), '.'), s_copy.end()); // to remove '.' from floating point numbers temporarily
			
		   if(isLexicalError(s)){ //if identifier has number(s) at the start
				lexical_errors.push_back({line_no, s});
				s = "";
			}
			
			else
			{
				lexemes.push_back(s);
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
		
		else
		{
			if(isLexicalError(s)){
				lexical_errors.push_back({line_no, s});
			}
			lexemes.push_back(s);
			tokens.push_back({s,"identifier"});
			s = "";	
		}	
	}
}
	

void parser_clear()
{
	tokens.clear();
	lexemes.clear();
	lexical_errors.clear();
}


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

void is_Typemismatch()
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

bool invalid_datatype(string &a){
		for(auto it2 = data_types.begin(); it2 != data_types.end(); it2++){
			if(a == *it2){
				return false;
			}
		}
	
	return true;
}


bool duplicate_check(string &a) {
	for(auto it : lexical_errors){
		if(it.second == a){
			return true;
		}
	}
	return false;
}

void keyword_check(){
	
	for(auto it = tokens.begin(); it != tokens.end()-1; it++){
			auto next_it = next(it, 1);
				if(it->second == "identifier" && next_it->second == "identifier"){
					if(invalid_datatype(it->first) && !duplicate_check(it->first)){
						line_no_lexical++;
						lexical_errors.push_back({line_no, it->first});
					}		
				}
				else if(it->second == "terminator" && next_it->second == "identifier"){ //hotfix sa floop
						if(is_declared(next_it->first)){
							continue;
						}
						else {
							line_no_lexical++;
							lexical_errors.push_back({line_no, next_it->first});
						}
				}
				else if(it->second == "data type" && next_it->second == "identifier"){
						if(invalid_datatype(it->first)){
							line_no_lexical++;
							lexical_errors.push_back({line_no, it->first});
						}
				}
	}

	//remove duplicates in the vector

}

void declared_check(){ //all valid identifiers that is declared
	for(auto it = tokens.begin(); it!=tokens.end();it++){
		auto next_it = next(it, 1);
		if(it->second == "data type" && next_it->second == "identifier" && !invalid_datatype(it->first) && !isLexicalError(next_it->first)){
			declared_vars.push_back(next_it->first);
		}
	}
}

void division()
{
	bool check; 
	int count = 1;
	vector<pair<string, string>> arith_syn; //checks the arithmetic operation syntax
	
	for(auto it = tokens.begin(); it!=tokens.end();it++)
	{
		#define token second
		#define lexeme first
		
		if(it->token == "identifier") 
		{
			auto nx = next(it,1);
			if(nx->second == "arithmetic operator" )
			{
				arith_syn.push_back({it->lexeme,it->token});
        		arith_syn.push_back({nx->lexeme,nx->token});
        		nx++;
        		
        		if((nx->token == "integer") || (nx->token == "double"))
        		{
        			arith_syn.push_back({nx->lexeme,nx->token}); 
        			
        			cout << endl << endl;
        			
        			for(auto it2 = arith_syn.begin(); it2!=arith_syn.end();it2++)
					{
						cout<< it2->lexeme << "\t" << it2->token << endl; 
					}	
					
					auto ptr_val = prev(arith_syn.end(),1);
					if(ptr_val-> first == "0")
					{
						cout << "cannot divide by zero" << endl;
					}
					arith_syn.clear();					
				}
				else
				{
					arith_syn.clear();
					continue;
				}

			}
		}
	}	
}

