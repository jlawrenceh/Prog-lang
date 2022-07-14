#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <iomanip>
using namespace std;


vector<string> lines;
int line_no = 0;

vector<string> data_types = {"INT", "CHAR", "BLN", "FLT", "DBL", "STR", "VOID"};							
vector<string> arithmetic = {"+", "-", "*", "/", "%"};
vector<string> relational = {"==", "!=", ">", "<", ">=", "<="};
vector<string> logical = {"AND", "OR", "NOT",};
vector<string> keywords = { "OUT", "IN", "IF-ELSE", "FLOOP", "DLOOP", "WLOOP", "IF", "ELSE"};
vector<string> symbols =  { "#", "@", "{" , "}" , "[", "]" , "(", ")"};
string terminator = "~";
string assignment = "=";

vector<pair<int,string>> undefined_vars;
vector<pair<int,string>> brackets; 

vector<pair<string,string>> tokens;
vector<string> lexemes;

vector<pair<int,string>> lexical_errors;
vector<pair<string, string>> line_syntax;
//vector<pair<string, string>> line_syn_lex;
vector<pair<string, string>> declared_vars;
vector<int> zero_division;

void view_lexical_errors();
bool is_DataType(string a);
bool is_Arithmetic(string a);
bool is_Assignment(string a);
bool is_Relational(string a);
bool is_Logical(string a);
bool is_Keyword(string a);
bool is_Symbol(string a);
bool is_Numeral(string a);
void parser(string str);
bool isLexicalError(string a);
void bracket_balance(string s);
void is_mismatch(vector<pair<string,string>> temp);
void division(vector<pair<string, string>> arith_syn);
void datatype_error(vector<pair<string, string>> dec_syn);

bool is_declared(string &a)
{
	if(!declared_vars.empty())
	{
		for(auto it = declared_vars.begin(); it != declared_vars.end(); it++)
		{
			if(it->first == a)
				return true;
		}
	}
	else
	{
		cout<<"Vector is empty\n";
	}
	return false;
}

void view_lexical_errors()
{
	for(auto itr : lexical_errors)
	{
		cout << "Lexical error " << "\"" << itr.second << "\" at line " << itr.first << endl;
	}
	
}
void bracket_balance(string s)
{
	//cout << "[CALLED] bracket_balance with " << s << endl;
	if (brackets.empty())
	{
		brackets.push_back({line_no,s});
	//	cout << "[PUSHED] " << s << " from line " << line_no << endl; 
		
	}
	else
	{
		#define symbol second
		#define line first
		if ((brackets.back().symbol== "{" && s == "}") ||
			(brackets.back().symbol== "(" && s == ")") ||
			 (brackets.back().symbol== "[" && s == "]"))
		{	
		//	cout << "[POPPED] " << brackets.back().symbol << endl; 
			brackets.pop_back();
		}
		else
		{
			brackets.push_back({line_no,s});
		//	cout << "[PUSHED] " << s << " from line " << line_no << endl; 
		}
	}
}

bool is_Numeral(string a)
{
	regex d("[-]?([1-9][0-9]*)|[0]");	//integer 
	regex f("[-]?([0]|[1-9]+)[.][0-9]+");	//double
	
	if(regex_match(a, d))
	{
		tokens.push_back({a,"integer"});
		
		line_syntax.push_back({a,"integer"});
		return true;
	}
	else if (regex_match(a,f))
	{
		tokens.push_back({a,"double"});
		
		line_syntax.push_back({a,"double"});
		return true;
	}
	else
	{
		return false;
	}
}

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
	if (a == assignment)
	{
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
			{		
				if (a == "(" || a == "{" || a == "[" || a == "]" || a == "}" || a == ")")
					bracket_balance(a);
				return true;
			}
		}
	
	return false;
}

void parser(string str){
	string s = "";
	int len = str.length();
	bool read_str_lit = false;
	bool read_char_lit = false;
	
	line_no++;
	lines.push_back(str);
	
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
				
				line_syntax.push_back({s,"string literal"});
				
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
				
				line_syntax.push_back({s,"character"});
				
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
			lexemes.push_back(s);
			tokens.push_back({s, "terminator"});
			line_syntax.push_back({s,"terminator"});
			s = "";
		}
		
		else if (is_DataType(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "data type"});
			line_syntax.push_back({s, "data type"});
			s = "";
		}
		
		else if (is_Arithmetic(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "arithmetic operator"});
			line_syntax.push_back({s, "arithmetic operator"});
			s = "";
		}
		
		else if (is_Assignment(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "assignment operator"});
			line_syntax.push_back({s, "assignment operator"});
			s = "";
		}
		
		else if (is_Relational(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "relational operator"});
			line_syntax.push_back({s, "relational operator"});
			s = "";
		}
		
		else if (is_Logical(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "logical operator"});
			line_syntax.push_back({s, "logical operator"});
			s = "";
		}
		
		else if (is_Keyword(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "keyword"});
			line_syntax.push_back({s, "keyword"});
			s = "";
		}
		
		else if (is_Symbol(s))
		{
			lexemes.push_back(s);
			tokens.push_back({s, "symbol"});
			line_syntax.push_back({s, "symbol"});
			s = "";
		}
		else if (s == "\n" || s == "" || s == "")
		{
			s = "";
		}
		else if (is_Numeral(s))
		{
			lexemes.push_back(s);
			s = "";
		}
		else
		{
			regex pattern("[a-zA-Z_][0-9a-zA-Z_]{0,19}");
			if(regex_match(s, pattern))
			{
				lexemes.push_back(s);
				tokens.push_back({s,"identifier"});
				
				line_syntax.push_back({s,"identifier"});
			}
			else
			{
				lexical_errors.push_back({line_no,s});
			}
			s = "";	
		}	
	}
	
	//line_syntax [ACCESS]
	
	//data type check
		for(auto it = line_syntax.begin(); it != line_syntax.end()-1;it++){
		auto peak = next(it, 1);

			if(it->second == "identifier" && peak->second == "identifier"){
				if(!is_DataType(peak->first)){
					lexical_errors.push_back({line_no,it->first});
				}
			}
			else if(it->second == "terminator" && peak->second == "identifier"){
				if(is_declared(peak->first)){
					continue;
				}
				else 
				{
					undefined_vars.push_back({line_no, peak->first});
				}
			}
			
			if(it == line_syntax.end())
				break;
	}

	for(auto itr = line_syntax.begin(); itr!=line_syntax.end();itr++)
	{
		if (itr == line_syntax.begin())
		{
			if(itr->second == "identifier")		
			{
				bool ex;
				
				for(auto itr2 = declared_vars.begin(); itr2!=declared_vars.end();itr2++)
					{
						if (itr->first == itr2->first)
						{
							ex = true;
							break;
						}	
					}
					
				if (ex == false)
				{
					undefined_vars.push_back({line_no,itr->first});
				}
				
	//			cout << "[MESSAGE] Identifier ang una." << endl;
			}
		}
		else
		{
			if(itr->second == "identifier")	
			{
				bool exists;
				
				auto prev_ptr = prev(itr,1);
				
				if(prev_ptr -> second == "data type")
				{
					for(auto itr2 = declared_vars.begin(); itr2!=declared_vars.end();itr2++)
					{
						if (itr->first == itr2->first)
						{
							exists = true;
							break;
						}	
					}
					
					if (exists == false)
					{
						declared_vars.push_back({itr->first, prev_ptr->first});
					}
				}
			}
		
		}

	}
	

//	datatype_error(line_syntax); 
	division(line_syntax);
	//typo datatype in declaration
	
	for(auto it : line_syntax){
		cout<<"[LINE SNYTAX] " << it.first <<"\t" << it.second << endl;
	}			//lexeme        	//token
	
	line_syntax.clear();
	
	
}

void division(vector<pair<string, string>> syntax)
{
	bool check; 
	int count = 1;
	vector<pair<string, string>> arith_syn; //checks the arithmetic operation syntax
	
	for(auto it = syntax.begin(); it!=syntax.end();it++)
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
        					
					auto ptr_val = prev(arith_syn.end(),1);
					if(ptr_val-> first == "0")
					{
						zero_division.push_back(line_no);
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
}								//INT	data type
								//lexeme token
void datatype_error(vector<pair<string, string>> dec_line){
		//#define token second
		//#define lexeme first
	
	for(auto it = dec_line.begin(); it != dec_line.end(); it++){
	//	auto peak = next(it, 1);
			if(!is_DataType(it->lexeme)){
				lexical_errors.push_back({line_no, it->lexeme});
			
			}
	}
	
}

void parser_clear()
{
	tokens.clear();
	lexemes.clear();
	lexical_errors.clear();
}


void unbalanced_brackets()
{
	if(!brackets.empty())
	{
		for (auto itr : brackets)
		{
			cout << "Unpaired bracket " << "\"" << itr.second << "\" at line " << itr.first << endl;
		}
	}
	
}

void show_semantic_errors()
{
	for (auto itr: zero_division)
	{
		cout << "[ERROR] cannot divide by zero at line " << itr << endl;
	}

	for (auto itr: undefined_vars)
	{
		cout << "[ERROR] undefined identifier " << itr.second << " at line " << itr.first << endl;
	}
}


