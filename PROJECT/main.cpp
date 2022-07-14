#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>
#include <iomanip>

#include "parser.h"

using namespace std;
int main(int argc, char** argv) {
	
	int menu;
	char switchloop;
	string filename, extension = ".txt";
	string x; 
	string code = "";
	do{
		cout << "1 : Upload text file\n" 
		 << "2 : View Lexemes and tokens\n" 
		 << "3 : View Lexical errors\n" 
		 << "4 : View Syntax errors\n"
		 << "5 : View Semantic errors\n" 
		 << "6 : Exit\n" 
		 << "Please select an option: ";
		 
		cin >> menu;
		
		switch(menu){
			
			case 1: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[1] Upload text file" << endl;
				cout << "__________________________________________________________" << endl << endl;
				cout << "Please input file name: ";
				
				cin >> filename;
				
				filename.append(extension);
	
				ifstream file(filename.c_str());
				
				if(!file.fail()){
					while(getline(file,x)){
						parser(x + ' ');	
						//cout<<x<<endl;	
					}
					cout << "[ NOTICE ] " << filename << " file successfully uploaded" << endl;
					
				}
				else{
					cout << "[ ERROR ] File not found . . ." << endl;
				}
				
				break;
			}
			case 2: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[2] View lexemes and tokens" << endl;
				cout << "__________________________________________________________" << endl << endl;
						
						
				cout << "LEXEMES" << setw(30) << "TOKENS" << setw(30) <<endl;
				for(auto it : tokens)
	        	{
	        		cout <<left << it.first << setw(25) << left << it.second <<setw(30) <<endl;
	        	
				}
				
				break;
			}
			case 3: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[3] View lexical errors" << endl;
				cout << "__________________________________________________________" << endl << endl;
				view_lexical_errors();
				break;
			}
			case 4: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[4] View Syntax errors" << endl;
				cout << "__________________________________________________________" << endl << endl;
				unbalanced_brackets();
				break;
			}
			case 5: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[5] View Semantic errors" << endl;
				cout << "__________________________________________________________" << endl << endl;
				show_semantic_errors();
				break;
			}
			case 6: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t\t[6] Exit" << endl;
				cout << "__________________________________________________________" << endl << endl;
				cout << "Program is closing => ";
				system("pause");
				return 0;
				break;	
			}
			case 7: {
				cout << "[DECLARED VARIABLES]" << endl;
				for(auto itr : declared_vars)
				{
					cout << itr.first << "\t" <<itr.second << endl;
				}
				cout<<endl;
				cout << "[UNDECLARED VARIABLES]\n";
				for(auto it : undefined_vars){
					cout << it.first << "\t" <<it.second << endl;
				} 
				
				/*
				for(auto itr : lines)
				{
					cout << itr << endl;
				}
				break;*/
			}
			
			
		}
		
		cout << "Try again? [ Y / N ]" << endl;
		cin >> switchloop;
		system("cls");
	
	}
	while(switchloop == 'Y' || switchloop =='y');
	cout << "Program is closing => ";
	return 0;
}
