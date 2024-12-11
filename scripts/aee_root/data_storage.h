#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <string>
#include <vector>
#include <cmath>

struct Node {
    Node* next;
    std::string data;
    bool isOperator;

    // Constructor
    Node(std::string input);
};

class ExpressionTree {
private:
	// variables
    Node* top;
    std::string originalExpression;

public:
    // constructor
    ExpressionTree(std::string expression);

    // destructor
    ~ExpressionTree();

	// method prototypes for E.Tree
    void buildExpression(std::string formattedExpression);
    double evaluate();
    void push(std::string add_val);
    std::string pop();
    int returnTop();
};


class Results {
private:
	// variables
    std::vector<double> results;

public:
    // Constructor
    Results();

    // method prototypes
    double lastResult();
    void record(double result);
    void displayResults();
};

#endif
