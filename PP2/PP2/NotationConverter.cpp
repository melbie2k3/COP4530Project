#include "NotationConverter.hpp"
#include <string>
#include <sstream>

class NotationConverter : public NotationConverterInterface {
public:
// this function wrong
    std::string postfixToInfix(std::string inStr) override {
    
        LDeque D;                        // initialize deque to use

        std::stringstream ss(inStr);    // string to concat operators and operands to push onto stack

        while(!ss.eof()) {

            std::string ret;            // string to return

            std::string temp;           // temp string to add character to Deque

            temp += ss.get();           // add character from string stream to temp variable

            if(isBadInput(temp))            // non-alpha, non-operator and non-space characters will throw an error

                throw("Error: Bad input");

            // skip spaces

            if(isSpace(temp)) {

                continue;

            }

            // when operator is encountered, surround it with relevant operands and push it onto the stack

            // as expressions are pushed onto the stack, concatenated expressions become operands that are being popped from the stack

            else if(isOperator(temp)) {

                ret += "(" + D.removeFront() + " " + temp + " " + D.removeFront() + ")";

                // D.removeFront();

                D.insertFront(ret);

            }

            // operands are just pushed onto the stack for later use

            else if(isAlpha(temp)) {

                D.insertFront(temp);  // push contents of temp variable onto Deque

            }

            // I think my function reached a null character at some point... this is to skip it if that happens.

            else {

                continue;

            }

        }

        return D.back();     // last expression left in the stack is the converted expression
    }

    std::string postfixToPrefix(std::string inStr) override {
        LDeque D;                        // initialize deque to use

        std::stringstream ss(inStr);    // add expression to stringstream

        while(!ss.eof()) {

            std::string ret;            // string to return

            std::string temp;           // temp string to add character to Deque

            temp += ss.get();           // add character from string stream to temp variable

            if(isBadInput(temp))            // non-alpha, non-operator and non-space characters will throw an error

                throw("Error: Bad input");

            // skip spaces

            if(isSpace(temp)) {

                continue;

            }

            // push operands onto stack

            else if(isAlpha(temp)) {

                D.insertFront(temp);

            }

            // when an operator is encountered, list operator followed by two operands

            // again, as expressions are pushed onto the stack, they become 'operands' that are being concatenated with the operator

            else if(isOperator(temp)) {

                ret += temp + " " + D.removeFront() + " " + D.removeFront();  // push contents of temp variable onto Deque

                D.insertFront(ret);

            }

            // skip possible bull characters

            else {

                continue;

            }

        }

        return D.back();     // last expression in the stack is the converted expression            
    }

    std::string infixToPostfix(std::string inStr) override {
        LDeque D;                // initialize deque to use

        std::string ret;        // string to return - operators and operands will be concatenated into this string

        std::stringstream ss(inStr);    // add expression to stringstream

        while(!ss.eof()) {

            int curPrec = 0;

            std::string temp;           // temp string to add character to Deque

            temp += ss.get();           // add character from string stream to temp variable

            if(isBadInput(temp))

                throw("Error: Bad input");

            if(isOperator(temp)) {                  // if current symbol is an operator, assign precedence

                curPrec = assignPrec(temp);         // (see helper function below for values)

            }

            if(isSpace(temp)) {                     // skip spaces

                continue;

            }

            else if(isAlpha(temp)) {                // add space + operand to return string

                ret += " " + temp;

            }

            else if(temp == "(") {                  // push opening parenthesis onto stack

                D.insertFront(temp);

            }
// GetFront maybe the front function
            else if(temp == ")") {

                while(!D.empty() && D.front() != "(")      // when a closing parenthesis is encountered, pop items from stack until

                    ret += " " + D.removeFront();                  // parenthesis is closed (by the corresponding opoeining parenthesis)

                if(!D.empty() && D.front() == "(")         // get rid of opening parenthesis on stack

                    D.removeFront();

            }

            else if(isOperator(temp)) {

                while(!D.empty() && curPrec <= assignPrec(D.front()))      // add operators with smaller precedence to return variable

                    ret += " " + D.removeFront();

                D.insertFront(temp);                                              // push current operator onto stack - deal with it later

            }

        }

        while(!D.empty())                 // when initial expression is empty and sorted, pop off all the remaining operators/operands

            ret += " " + D.removeFront();

        return ret.substr(1);               // return concatenated expression; get rid of space in front of it
    }

    std::string infixToPrefix(std::string inStr) override {
        std::string post = infixToPostfix(inStr);       // convert infix -> postfix -> prefix using existing expressions
        return postfixToPrefix(post);   
    }

    std::string prefixToInfix(std::string inStr) override {
        LDeque D;// initialize deque to use
        std::string rev;
        for(int i = inStr.length()-1; i > -1; i--)

            rev += inStr.at(i);

        std::stringstream ss(rev);  // add expression to stringstream

        while(!ss.eof()) {

            std::string ret;            // string to return

            std::string temp;           // temp string to add character to Deque

            temp += ss.get();           // add character from string stream to temp variable

            if(isBadInput(temp))            // throw error if bad input

                throw("Error: Bad input");

            if(isSpace(temp)) {                         // skip spaces

                continue;

            }

            else if(isAlpha(temp)) {                    // push operands onto stack

                D.insertFront(temp);

            }

            else if(isOperator(temp)) {                 // if operator is encountered, surround it with relevant operands and push onto stack

                std::string temp_a = D.removeFront();      // eventually, the whole converted expression will be pushed onto the stack

                std::string temp_b = D.removeFront();

                ret += "(" + temp_a + " " + temp + " " + temp_b + ")";

                D.insertFront(ret);                       // push concat expression onto stack

            }

        }

        return D.back();                             // return converted expression
    }

    std::string prefixToPostfix(std::string inStr) override {

        std::string in = prefixToInfix(inStr);      // convert prefix -> infix -> postfix using existing functions

        return infixToPostfix(in);    
    }

private:
    bool isOperator(const std::string &s) {
        bool ret = false;
        if (s == "+" || s == "-" || s == "*" || s == "/")
            ret = true;
        return ret;
    }

    bool isAlpha(const std::string &s) {
        bool ret = false;
        if (s == "A" || s == "B" || s == "C" || s == "D" || s == "E" || s == "F" || s == "G" || s == "H" || s == "I" || s == "J" || s == "K" || s == "L" || s == "M" || s == "N" || s == "O" || s == "P" || s == "Q" || s == "R" ||s == "S" || s == "T" || s == "U" || s == "V" || s == "W" || s == "X" || s == "Y" || s == "Z" || s == "a" || s == "b" || s == "c" || s == "d" || s == "e" || s == "f" || s == "g" || s == "h" || s == "i" || s == "j" || s == "k" || s == "l" || s == "m" || s == "n" || s == "o" || s == "p" || s == "q" || s == "r" ||s == "s" || s == "t" || s == "u" || s == "v" || s == "w" || s == "x" || s == "y" || s == "z")
            ret = true;
        return ret;
    }

    bool isSpace(const std::string &s) {
        bool ret = false;
        if (s == " ")
            ret = true;
        return ret;
    }

    bool isBadInput(const std::string &s) {
        bool ret = false;
        if (s == "!" || s == "@" || s == "#" || s == "%" || s == "^" || s == "&" || s == "_" || s == "=" || s == "{" || s == "}" || s == "[" || s == "]" || s == "|" || s == "\\" || s == "\"" || s == "'" || s == "<" || s == ">" ||s == "," || s == "." || s == "~" || s == "`" || s == "?" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9" || s == "0")
            ret = true;
        return ret;
    }

    int assignPrec(const std::string &s) {
        int ret;
        if(s == "+")

            ret = 1;

        else if(s == "-")

            ret = 2;

        else if(s == "/")

            ret = 3;

        else if(s == "*")

            ret = 4;

        else

            ret = 0;

        return ret;

    }
};

    
    /*
        bool NotationConverterInterface::isOperator(const std::string &s) {
        bool ret = false;
        if (s == "+" || s == "-" || s == "*" || s == "/")
            ret = true;
        return ret;
    }

    bool NotationConverterInterface::isAlpha(const std::string &s) {
        bool ret = false;
        if (s == "A" || s == "B" || s == "C" || s == "D" || s == "E" || s == "F" || s == "G" || s == "H" || s == "I" || s == "J" || s == "K" || s == "L" || s == "M" || s == "N" || s == "O" || s == "P" || s == "Q" || s == "R" ||s == "S" || s == "T" || s == "U" || s == "V" || s == "W" || s == "X" || s == "Y" || s == "Z" || s == "a" || s == "b" || s == "c" || s == "d" || s == "e" || s == "f" || s == "g" || s == "h" || s == "i" || s == "j" || s == "k" || s == "l" || s == "m" || s == "n" || s == "o" || s == "p" || s == "q" || s == "r" ||s == "s" || s == "t" || s == "u" || s == "v" || s == "w" || s == "x" || s == "y" || s == "z")
            ret = true;
        return ret;
    }

    bool NotationConverterInterface::isSpace(const std::string &s) {
        bool ret = false;
        if (s == " ")
            ret = true;
        return ret;
    }

    bool NotationConverterInterface::isBadInput(const std::string &s) {
        bool ret = false;
        if (s == "!" || s == "@" || s == "#" || s == "%" || s == "^" || s == "&" || s == "_" || s == "=" || s == "{" || s == "}" || s == "[" || s == "]" || s == "|" || s == "\\" || s == "\"" || s == "'" || s == "<" || s == ">" ||s == "," || s == "." || s == "~" || s == "`" || s == "?" || s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9" || s == "0")
            ret = true;
        return ret;
    }

    int NotationConverterInterface::assignPrec(const std::string &s) {
        int ret;
        if(s == "+")

            ret = 1;

        else if(s == "-")

            ret = 2;

        else if(s == "/")

            ret = 3;

        else if(s == "*")

            ret = 4;

        else

            ret = 0;

        return ret;

    }
    */
/*
struct Node {
    std::string data;
    Node* prev;
    Node* next;

    Node(const std::string& value) : data(value), prev(nullptr), next(nullptr) {}
};

class Deque {
private:
    Node* front;
    Node* back;

public:
    Deque() : front(nullptr), back(nullptr) {}

    bool isEmpty() const {
        return (front == nullptr);
    }

    void pushFront(const std::string& value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = newNode;
            back = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
    }

    void pushBack(const std::string& value) {
        Node* newNode = new Node(value);

        if (isEmpty()) {
            front = newNode;
            back = newNode;
        } else {
            newNode->prev = back;
            back->next = newNode;
            back = newNode;
        }
    }

    std::string popFront() {
        if (isEmpty()) {
            return '\0';
        }

        std::string value = front->data;
        Node* temp = front;

        if (front == back) {
            front = nullptr;
            back = nullptr;
        } else {
            front = front->next;
            front->prev = nullptr;
        }

        delete temp;
        return value;
    }

    std::string popBack() {
        if (isEmpty()) {
            return '\0';
        }

        std::string value = back->data;
        Node* temp = back;

        if (front == back) {
            front = nullptr;
            back = nullptr;
        } else {
            back = back->prev;
            back->next = nullptr;
        }

        delete temp;
        return value;
    }
};

class NotationConverter : public NotationConverterInterface {
public:
    std::string postfixToInfix(std::string inStr) override {
        Deque operands;
        std::string token;
        size_t pos = 0;

        while ((pos = inStr.find(' ')) != std::string::npos) {
            token = inStr.substr(0, pos);
            inStr.erase(0, pos + 1);

            if (isOperator(token)) {
                std::string operand2 = operands.popBack();
                std::string operand1 = operands.popBack();

                std::string result = "(" + operand1 + " " + token + " " + operand2 + ")";
                operands.pushBack(result);
            } else {
                operands.pushBack(token);
            }
        }

        return operands.popFront();
    }

    std::string postfixToPrefix(std::string inStr) override {
        Deque operands;
        std::string token;
        size_t pos = 0;

        while ((pos = inStr.find(' ')) != std::string::npos) {
            token = inStr.substr(0, pos);
            inStr.erase(0, pos + 1);

            if (isOperator(token)) {
                std::string operand2 = operands.popBack();
                std::string operand1 = operands.popBack();

                std::string result = token + " " + operand1 + " " + operand2;
                operands.pushBack(result);
            } else {
                operands.pushBack(token);
            }
        }

        return operands.popFront();
    }

    std::string infixToPostfix(std::string inStr) override {
        Deque operators;
        std::string output;
        std::string token;
        size_t pos = 0;

        while ((pos = inStr.find(' ')) != std::string::npos) {
            token = inStr.substr(0, pos);
            inStr.erase(0, pos + 1);

            if (isOperand(token)) {
                output += token + " ";
            } else if (isOperator(token)) {
                while (!operators.isEmpty() && precedence(operators.popBack()) >= precedence(token)) {
                    output += operators.popBack() + " ";
                }
                operators.pushBack(token);
            } else if (token == "(") {
                operators.pushBack(token);
            } else if (token == ")") {
                while (!operators.isEmpty() && operators.popBack() != "(") {
                    output += operators.popBack() + " ";
                }
            }
        }

        while (!operators.isEmpty()) {
            output += operators.popBack() + " ";
        }

        return output;       
    }

    std::string infixToPrefix(std::string inStr) {
        std::string reversedInfix = reverseString(inStr);
        std::string postfix = infixToPostfix(reversedInfix);
        std::string prefix = postfixToPrefix(postfix);
        return reverseString(prefix);
    }

    std::string prefixToInfix(std::string inStr) {
        std::string reversedPrefix = reverseString(inStr);
        std::string postfix = prefixToPostfix(reversedPrefix);
        std::string infix = postfixToInfix(postfix);
        return reverseString(infix);
    }

    std::string prefixToPostfix(std::string inStr) override {
        Deque operands;
        std::string token;
        size_t pos = 0;

        while ((pos = inStr.find(' ')) != std::string::npos) {
            token = inStr.substr(0, pos);
            inStr.erase(0, pos + 1);

            if (isOperand(token)) {
                operands.pushBack(token);
            } else if (isOperator(token)) {
                std::string operand2 = operands.popBack();
                std::string operand1 = operands.popBack();

                std::string result = operand1 + " " + operand2 + " " + token;
                operands.pushBack(result);
            }
        }

        return operands.popFront();

    }

private:
    bool isOperator(const std::string& token) {
        return (token == "+" || token == "-" || token == "*" || token == "/");
    }

    bool isOperand(const std::string& token) {
        return (token.length() == 1 and std::isalpha(token[0]));
    }
    // Consider this function again
    int precedence(const std::string& op) {
        if (op == "*" || op == "/") {
            return 2;
        } else if (op == "+" || op == "-") {
            return 1;
        } else {
            return 0;
        }
    }

    std::string reverseString(const std::string& str) {
        std::string reversed;
        for (int i = str.length() - 1; i >= 0; i--) {
            reversed += str[i];
        }
        return reversed;
    }
};
*/


