// input.cpp: Contains the code necessary to recieve user input and display errors properly.
// Input(): Class that holds all input functionality.



#include <iostream>
#include <string>
#include "parser.cpp"  //Parser module is included
#include "data_storage.cpp"  //ExpressionTree and Results modules are included


using std::cin;
using std::cout;
using std::endl;
using std::string;

class Input {
private:
    string inputExpression;
public:

    Input(int i) {
        if (i == 1) {
            cout << "Initialized input module..." << endl;
            getExpression();
            run();
        }

    }

    void getExpression() {
        cout << "Enter an arithmetic expression (in infix notation): ";
        std::getline(cin, inputExpression);
    }

    int run() {
        try {
            //1. Parse the input expression to convert it to prefix notation
            Parser parser(inputExpression);
            string prefixExpression = parser.convert();
            cout << "Converted to prefix notation: " << prefixExpression << endl;

            //2. Create an ExpressionTree with the prefix expression and evaluate it
            ExpressionTree expressionTree(prefixExpression);
            double result = expressionTree.evaluate();
            cout << "Result: " << result << endl;

            //3. Store the result using the Results class
            Results results;
            results.record(result);
            results.displayResults();

        }
        catch (int errorCode) {
            // Handle errors with appropriate messages
            switch (errorCode) {
            case 100:
                cout << "Error: Expression stack is empty." << endl;
            case 101:
                cout << "Error: Invalid input detected." << endl;
                break;
            case 105:
                cout << "Error: Too many closing parentheses." << endl;
                break;
            case 106:
                cout << "Error: Unmatched opening parentheses." << endl;
                break;
            case 107:
            case 109:
            case 112:
                cout << "Error: Consecutive / non-paired operators." << endl;
                break;
            case 108:
                cout << "Error: Non-numeric character in expression.";
                break;
            case 110:
                cout << "Error: Missing operand in the expression." << endl;
                break;

            default:
                cout << "Unknown error occurred with code: " << errorCode << endl;
            }
        }

        return 0;
    }
};
