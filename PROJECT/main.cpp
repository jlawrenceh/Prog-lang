#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex>

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
		 << "7 : Declared Variables\n"
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
						x+=" ";
						code+=x;
					}
					cout << "[ NOTICE ] " << filename << " file successfully uploaded" << endl;
					parser(code + ' ');
					declared_check(); //push all of the succesfully declared variable in a vector
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
						
				for(auto it : tokens)
	        	{
	        		cout << it.first << "\t" << it.second<<endl;
				}
				
				break;
			}
			case 3: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[3] View lexical errors" << endl;
				cout << "__________________________________________________________" << endl << endl;
				keyword_check();
				view_lexical_errors();
				
				break;
			}
			case 4: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[4] View Syntax errors" << endl;
				cout << "__________________________________________________________" << endl << endl;
				break;
			}
			case 5: {
				cout << "__________________________________________________________" << endl << endl;
				cout << "\t\t[5] View Semantic errors" << endl;
				cout << "__________________________________________________________" << endl << endl;
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
				view_declared_vars();
				break;
			}
			
		}
		
		cout << "Try again? [ Y / N ]" << endl;
		cin >> switchloop;
		system("cls");
	
	}
	while(switchloop == 'Y' || switchloop =='y');
	return 0;
}
