#include "NotationConverter.hpp"
#include <string>
#include <sstream>

class NotationConverter : public NotationConverterInterface {
public:
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

                D.removeFront();

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

        return D.getBack();     // last expression left in the stack is the converted expression
    }

    std::string postfixToPrefix(std::string inStr) override {
        
    }

    std::string infixToPostfix(std::string inStr) override {
        
    }

    std::string infixToPrefix(std::string inStr) override {
       
    }

    std::string prefixToInfix(std::string inStr) override {
   
    }

    std::string prefixToPostfix(std::string inStr) override {
        
    }

};

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