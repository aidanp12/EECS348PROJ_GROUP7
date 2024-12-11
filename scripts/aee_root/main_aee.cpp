// main_aee.cpp: Root file for the program, runs each other module to execute desired behavior.


#include <iostream>
#include "input.cpp"  // use input module

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() 
{
	bool continue_program = true;
    
    while (continue_program) {
        cout << "Do you want to continue the program? Type \"y\" for yes or \"n\" for no: ";
        
        char response;
        cin >> response;
        
        if (response == 'n' || response == 'N') {
            continue_program = false;
        } 
        // If user types 'y', the loop just continues.
    }
    
    return 0;
}
