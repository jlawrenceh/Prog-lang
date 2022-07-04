#include "parser.h"

#include <iostream>
#include <fstream>
//#include <cstring>
#include <stdlib.h>
#include <ctype.h>
#include <array>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


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
			
			parser(code + ' ');
			} 
			else {
				cout << "Error file not found...\n";
			}
			
			file.close();
			break;
		}
        
        case 2:{ // lexemes tokens
            cout << "View lexemes and tokens\n";
        	
        	cout<<endl;
			for (i = lex.begin(); i != lex.end(); ++i){
				if(i == lex.end() - 1){
					cout << *i;
					
				} else {
					cout << *i << ", ";
				}
			}
			
        	cout << "\n\n";
        	for(auto it : tokens)
        	{
        		cout << it.first << "\t" << it.second<<endl;
			}
            break;
        }
        case 3:{ // lexical errors
        	keyword_error();
        	if(lexical_errors.empty()){
        		cout<<"\n";
				cout<<"No Lexical Error(s) found...\n";
		    } else {
		    	cout<<"\n";
		    	cout << "Lexical Error(s)...\n";
            	view_lexical_errors();
			}
            break;
        }
        case 4:{ // syntax errors
            cout << "View Syntax errors";
            break;
        }
        case 5:{ // semantic errors
            cout << "View Semantic errors"<<endl;
            assignment();
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
	system("cls");
	
    }
	while(switchloop == 'Y' || switchloop == 'y');
	
    return 0;
}



