#include "LDeque.hpp"
LDeque::LDeque() : D(), n(0) {}
LDeque::~LDeque(){}

int LDeque::size() const{
    return n;
}

bool LDeque::empty() const {
    return n == 0;
}

const string& LDeque::front() const throw () {
    return D.front();
}

const string& LDeque::back() const throw () {
    return D.back();
}

//ENQUEUE AND DEQUEUE 
std::string LDeque::removeFront() throw() {
    if(empty()){return "";}
    std::string value = D.front();
    D.removeFront();
    n--;
    return value;
}

std::string LDeque::removeBack() throw() {
    if(empty()){return "";}
    std::string value = D.back();
    D.removeBack();
    n--;
    return value;
}

void LDeque::insertFront(const string &e) {
    D.addFront(e);
    n++;
}

void LDeque::insertBack(const string &e) {
    D.addBack(e);
    n++;
}