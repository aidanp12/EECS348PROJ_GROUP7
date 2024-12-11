// DataStorage.cpp : This file contains the primary components for the DataStorage module. 
// ExpressionTree() : a node-based class structure that saves & computes a prefix-notation expression.
// Node : a struct designed to link together expressions and numbers within the ExpressionTree.
// Results() : allows for storage and recollection of results. 

/* NOTE: This is an implementable version of the data storage module. Methods are designed to be called from
* within the program or an outside source.
(10.12.24) - AP
*/


#include <iostream>
#include <string>
#include <cmath>
#include <vector>



// Binary Node structure makes up the expression tree
struct Node {
    Node* next;
    std::string data;
    bool isOperator = false;
    
    Node(std::string input) {
        data = input;
        next = nullptr;
    }
};


class ExpressionTree {
// ExpressionTree is used to evaluate any given input in Prefix/Polish notation.
// It's not actually a tree but rather a stack. Need to update documentation correspondingly.
// Courtesy to Wikipedia and EECS210 for teaching me about prefix notation.
private: 
    Node* top = nullptr;
    std::string originalExpression;

public:
    // Constructor
    ExpressionTree(std::string expression) {
        buildExpression(expression);
        originalExpression = expression;
    }

    // Destructor 
    ~ExpressionTree() {
        delete top;
    }
    void buildExpression(std::string formattedExpression) {
        // The formattedExpression should be in Polish notations seperated by whitespaces. (ex: [* - 5 16 -7] )
        // Read in a string from right to left 
        for (int i = formattedExpression.length() - 1; i >= 0; --i) {

            char c = formattedExpression[i];

            // Skip the spaces
            if (c == ' ') {
                continue;
            }

            // check if the character is non-numeric (an operator) by referencing its ASCII value 
            if (c - '0' < 0 || c - '0' > 9) {
                // Pushes the operator to the stack
                std::string operatorVal = "";
                operatorVal += c;
                push(operatorVal);
                top->isOperator = true;
            }

            // handle numeric inputs
            else {
                int next = 0;
                std::string nodeVal = "";
                nodeVal += c;
                // keep checking right to left after a number to determine if there are multiple digits
                while (formattedExpression[i - (next + 1)] != ' ' && i - (next + 1) >= 0) {
                    nodeVal = formattedExpression[i - (next+1)] + nodeVal;
                    next++;
                }
                push(nodeVal);
                i -= next;
            }

        }
    }

    double evaluate() {
        // The formattedExpression should be in Polish notations seperated by whitespaces. (ex: [* - 5 16 -7] )
        // Read in a string from right to left 
        top = nullptr;
        for (int i = originalExpression.length() - 1; i >= 0; --i) {

            char c = originalExpression[i];

            // Skip the spaces
            if (c == ' ') {
                continue;
            }

            // check if the character is non-numeric (an operator) by referencing its ASCII value 
            if (c - '0' < 0 || c - '0' > 9) {                 
                // Establish previous values to operate with
                double result = 0;
                double num1 = std::stod(pop());
                double num2 = std::stod(pop());

                // Define behaviors for each potential operator
                switch (c) {
                    case '+':
                        result = num1 + num2; 
                        break;
                    case '-':
                        result = num1 - num2; 
                        break;
                    case '*':
                        result = num1 * num2; 
                        break;
                    case '/':
                        if (num2 == 0) {
                            throw 113;
                        }
                        result = num1 / num2;
                        break;
                    case '%':
                        result = std::fmod(num1, num2);
                        break;
                    case '^':;
                        result = std::pow(num1, num2);
                        break;

                }
                // add the new value to the top of the expression tree
                push(std::to_string(result));
            }

            // handle numeric inputs
            else {
                int next = 0;
                std::string nodeVal = "";
                nodeVal += c;
                // keep checking right to left after a number to determine if there are multiple digits
                while (originalExpression[i - (next + 1)] != ' ' && i - (next + 1) >= 0) {
                    nodeVal = originalExpression[i - (next + 1)] + nodeVal;
                    next++;
                }
                push(nodeVal);
                i -= next;
            }

        }
        return std::stod(pop());
    }

    // Adds a value to the top of the stack
    void push(std::string add_val) {
        Node* newEntry = new Node(add_val);
        if (top == nullptr) {
            top = newEntry;
        }
        else {
            newEntry->next = top;
            top = newEntry;
        }
    }

    // Remove & return the top value of the stack
    std::string pop() {
        if (top != nullptr) {
            std::string topVal = top->data;
            Node* temp = top->next;
            top = temp;
            return topVal;
        }
        else {
            // throw an exception for when no top value is present to be removed, represented by code the 100
            throw 100;
        }
    }
        
    // Print the top value to the terminal (should only be used for debugging) 
    int returnTop() {
        if (top != nullptr) {
            std::cout << "Top data: " << top->data << std::endl;
            return 1;
        }
        else {
            std::cout << "Nothing in the ExpTree." << std::endl;
            return 0;
        }
    }

        
};


// stores previous results and allows for easy access to previous results.
// I really wanted to try and make timestamps for each result, but i kept running into an "unsafe function" -
// - issue, couldnt figure it out. may come back to this later (09.12)
class Results {
private:
    // variables
    std::vector<double> results;

public:
    // Constructor
    Results() {}

    double lastResult() {
        return results[results.size() - 1];
    }

    void record(double result) {
        // store result in vector
        results.push_back(result);
    }

    // this is really designed for the "outside compiler model implementation" than anything
    void displayResults() {
        for (int i = 0; i < results.size(); i++) {           
            std::cout << "Result: " << results[i] << std::endl;
        }
    }
};
