#include "LDeque.hpp"

/*FYE: Functions were provided by the lecture notes given on this particular
      implementation of a deque data structure*/


//CONSTRUCTOR/DESTRUCTOR
//----------------------------------------------------------------------------------------->
LDeque::LDeque() : D(), n(0) {}
LDeque::~LDeque(){}

//CHECK FOR SIZE OF DEQUE (No. OF NODES IN IT ) && IF ITS EMPTY
//----------------------------------------------------------------------------------------->
int LDeque::size() const{
    return n;
}

bool LDeque::empty() const {
    return n == 0;
}

//REFERENCE TO FRONT AND REAR OF DEQUE 
//----------------------------------------------------------------------------------------->
const string& LDeque::front() const throw () {
    return D.front();
}

const string& LDeque::back() const throw () {
    return D.back();
}

//ENQUEUE AND DEQUEUE 
//----------------------------------------------------------------------------------------->
std::string LDeque::removeFront() throw() {
    if(empty()){return '\0';}
    std::string value = D.front();
    D.removeFront();
    n--;
    return value; // Return the stored value
}

std::string LDeque::removeBack() throw() {
    if(empty()){return '\0';}
    std::string value = D.back();
    D.removeBack();
    n--;
    return value; // Return the stored value
}

void LDeque::insertFront(const string &e) {
    D.addFront(e);
    n++;
}

void LDeque::insertBack(const string &e) {
    D.addBack(e);
    n++;
}