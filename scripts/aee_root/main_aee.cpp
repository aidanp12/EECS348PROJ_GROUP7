// main_aee.cpp: Root file for the program, runs each other module to execute desired behavior.


#include <iostream>
#include "input.cpp"  // use input module
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() 
{
    char response = 'y';
    while (response == 'y' || response == 'Y') {
        Input input(1);
        cout << "Do you want to continue the program? Type \"y\" for yes or \"n\" for no: ";
        cin >> response;
        
        if (response == 'n' || response == 'N') {
            break;
        }
        // If user types 'y', the loop just continues.
    }
    
    return 0;
}
