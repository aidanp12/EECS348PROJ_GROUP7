// DataStorage.cpp : This file contains the primary components for the DataStorage module. 
// ExpressionTree() : a node-based class structure that saves & computes a prefix-notation expression.
// Node : a struct designed to link together expressions and numbers within the ExpressionTree.
// Memory : allows for storage and recall of results. 

/* NOTE: This is not the final version, still working on it + 
adding functionality & finishing touches, just wanted something 
on the github to help with implementation. will be finished soon 
(03.12.24)
*/


#include <iostream>
#include <string>


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

        int evaluate() {
            // not sure if i supposed to do this but it seems pretty easy to incorporate right into the class
            // idk may look at it tmr/later
            while (returnTop() == 1) {
                
            }
        }

        void handleOperator() {
            // handle operators recursively 
            /* note for when its not 2 AM: keep checking 2 nodes deep until both next 2 nodes
            are numbers, then continue returning results up the expression tree. prefix notation is 
            cool that way so it handles itself as long as valid prefix notation is given in the input*/
        };

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


// yeah i didnt get this far but that's on the to-do list tomorrow (03.12)
// this will be responsible for storing outputs/results and such, maybe it'll hold stuff like the original expression
// but honestly i kinda realized it was pointless beyond storing results which can just be done in a vertex but who knows
class Results {};


int main()
{
    /* This is mostly just debugging/testing stuff, the class doesn't rely on a main function to operate, and probably shouldnt
    have one. */

    // Example of using the ExpressionTree class
    ExpressionTree tree("* - 5 6 7");

    // Push operands to the tree


    // Print top node (last operator or operand added)
    while (tree.returnTop()) tree.pop();
    return 0;
}
