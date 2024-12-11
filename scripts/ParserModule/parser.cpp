// Parser.cpp: A class that takes an input string (or tokenized input),
//             and converts it to Polish/prefix notation to be passed on to the ExpressionTree.

#include <iostream>
#include <string>


class Parser {

    public:
        Parser(std::string s) { // Constructor: pass the pointer to the string
            expression = s;
        }

        std::string convert() { // "main" method to return the simplified expression in prefix form
            remove_spaces(this->expression);
            check_parens(this->expression);
            check_invalid_char(this->expression);
            return simplify(this->expression);
        }

    private:
    std::string expression;
    std::string result;

    void remove_spaces(std::string &expression) { // pass by reference
    // removes all spaces from the expression. should only be done before solving because everything will gain spaces when converted to prefix notation
        for (int current = 0; expression[current] != '\0'; current++) {
            if (expression[current] == ' ') {
                expression.erase(current, 1);
            }
        }
    }

    void check_parens(const std::string &expression) {
        int parens_counter = 0;
        int length = expression.size();
        for (int i = 0; i < length; i++) {
            if (expression[i] == '(') {
                parens_counter += 1;
            }
            if (expression[i] == ')') {
                parens_counter -= 1;
            }
        }
        if (parens_counter < 0) {
            throw 105; // too many )
        }
        if (parens_counter != 0) {
            throw 106; // unmatched (
        }
    }

    void check_invalid_char(const std::string &expression) {
        int length = expression.size();
        for (int i = 0; i < length; i++) {
            char c = expression[i];
            if ((-1 > c - '0' || c - '0' > 10) && (c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != '(' && c != ')')) { // not a number AND not an operator or parens
                throw 108; //invalid character in input
            }
        }
    }

    std::string simplify(std::string expression) {
        // recursive. needs to return the prefix version of the expression split at the highest precendence operation.        

        // std::cout << "simplify( " << expression << " ) called." << std::endl; // useful for debugging

        int length = expression.size();

        if (length == 1) {
            if (-1 < expression[0] - '0' && expression[0] - '0' < 10) {
                return expression;
            }
            else {
                std::cout << expression << " will throw an error (not a number)." << std::endl;
                throw 101; // not a number error
            }
        }

        char last = expression[length - 1];
        if (last == '+' || last == '-' || last == '*' || last == '/' || last == '%') {
            throw 107; // operator error
        }

        for (int i = 0; i < length - 1; i++) {
            char cur = expression[i];
            if (cur == '+' || cur == '-' || cur == '*' || cur == '/' || cur == '%') {
                if (expression[i+1] == ')') {
                    throw 109; // operator error
                }
            }
        }

        // ------------- checks above ------------- main loop below

        std::string operand1; // = "" implied
        std::string operand2;
        std::string operation;

        int parenthesis_diff = 0; // track ')' - '('. Look for operators only while this is 0 (meaning we are in the first "layer" of the expression)
                                  // this *should* get around needing to calculate what inside the parens
                                  // note that because we check for if the whole expression is in (), this should work for all cases

        for (int i = length - 1; 0 < i; i--) { // iterate through the expression from the right (for left to right order of operations, don't ask) from prev (so it can recurse)

            char c = expression[i];

            if (c == '(') {
                parenthesis_diff -= 1;
            }
            if (c == ')') {
                parenthesis_diff += 1;
                if (i + 1 < length && (-1 < expression[i+1] - '0' && expression[i+1] - '0' < 10)) {
                    // if the thing after ')' is a number
                    throw 112; // need an operator ')' and a number
                }
            }

            // look for lowest precendence operator on the first layer
            if (parenthesis_diff > 0) {
                continue;
            }
            // ----------------- +, - -----------------
            if (c == '+' || c == '-') { // pos/neg already handled
                operation = c;
                // std::cout << "calling simplify() on operand1 for +/-: " << expression.substr(0, i) << '\n';
                operand1 = simplify(expression.substr(0, i)); // (start, length)
                // std::cout << "calling simplify() on operand2 for +/-: " << expression.substr(i+1) << '\n';
                operand2 = simplify(expression.substr(i+1)); // == expression[i+1:] from Python
                if (operand1 == "" || operand2 == "") {
                    throw 110; // missing operand error
                }
                return combine_subexpressions(operand1, operation, operand2);
            }
        }
// ----------------- *, /, % -----------------
        parenthesis_diff = 0;
        for (int i = length - 1; 0 < i; i--) { // iterate through the expression from the right (for left to right order of operations, don't ask) from prev (so it can recurse)

            char c = expression[i];

            if (c == '(') {
                parenthesis_diff -= 1;
            }
            if (c == ')') {
                parenthesis_diff += 1;
            }

            // look for lowest precendence operator on the first layer
            if (parenthesis_diff > 0) {
                continue;
            }
            // ----------------- *, /, % -----------------
            if (c == '*' || c == '/' || c == '%') { // * must be for multiplication now
                if (i > 0 && expression[i-1] != '*' && i < length - 1 && expression[i+1] != '*') { // don't mistake * for **
                    operation = c;
                    operand1 = simplify(expression.substr(0, i));
                    operand2 = simplify(expression.substr(i+1)); // == expression[i+1:] from Python
                    if (operand1 == "" || operand2 == "") {
                        throw 110; // missing operand error
                    }
                    return combine_subexpressions(operand1, operation, operand2);
                }
            }
        }
// ----------------- ** -----------------
        parenthesis_diff = 0;
        for (int i = length - 1; 0 < i; i--) { // iterate through the expression from the right (for left to right order of operations, don't ask) from prev (so it can recurse)

            char c = expression[i];

            if (c == '(') {
                parenthesis_diff -= 1;
            }
            if (c == ')') {
                parenthesis_diff += 1;
            }

            // look for lowest precendence operator on the first layer
            if (parenthesis_diff > 0) {
                continue;
            }
            // ----------------- ** -----------------
            if (c == '*') {
                if (i > 0 && expression[i-1] == '*') {
                    // the first power from the right has been found, so it is the "root" operator (backwards now, but same concept because this helps it go left->right)
                    // we can take everything before the ** and make it operand1, the other side operand2
                    operation = "^";
                    operand1 = simplify(expression.substr(0, i-1)); // (start, stop)
                    operand2 = simplify(expression.substr(i+1)); // == expression[i+1:] from Python
                    i -= 1; // skip the other *
                    if (operand1 == "" || operand2 == "") {
                        throw 110; // missing operand error
                    }
                    return combine_subexpressions(operand1, operation, operand2);
                }
            }
        }

        // starts with + or - (add to call on inner expression)
        // *** important: this relies on the expression being valid (eg. no +- or bad sign input; this needs to be caught earlier)
        // checked after making sure there is not an operation in the middle of the expression
        if (expression[0] == '+') {
            if (length == 1) {
                throw 110; // missing operand error
            }
            std::string inner = simplify(expression.substr(1));
            if (inner[0] == '+') {
                return simplify(inner.substr(1)); // if eg. ++2 after simplification from +(+2): simplify the 2 part and return this
            }
            if (inner[0] == '-') {
                return inner;
            }
            else { // ???
                return inner;
            }
        }

        if (expression[0] == '-') {
            if (length == 1) {
                throw 110; // missing operand error
            }
            std::string inner = simplify(expression.substr(1));
            if (inner[0] == '-') {
                inner = inner.substr(1); // flip the sign if two negatives
            }
            return expression[0] + inner;
        }
        
        
        // matching parenthesis (eliminate and call again *only after making sure there are no first-layer operators*)
        if (expression[0] == '(' && expression[length-1] == ')') {
            return simplify(expression.substr(1, length - 2));
        }

        return expression;
    }


    std::string combine_subexpressions(std::string operand1, std::string operation, std::string operand2) {
        // returns the combined prefix expression of two operands and an operator (they can be any size)
        return operation + ' ' + operand1 + ' ' + operand2; // this should work for combining any 2 prefix expressions with an operator
    }
};
