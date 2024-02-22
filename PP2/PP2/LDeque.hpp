#include "DLinkedList.hpp"
#include <string>
class LDeque {
private:
    DLinkedList D;
    int n;  
public:
    //Constructor/Destructor for deque
    LDeque();
    ~LDeque();

    //Reference functions to the front and back
    const std::string& front() const throw();
    const std::string& back() const throw();

    //Operations to insert, remove and check if deque is empty for the deque
    void insertFront(const string& e);
    void insertBack(const string& e);
    std::string removeFront() throw();
    std::string removeBack() throw();
    bool empty() const;

    //Size of the deque at a point
    int size() const;
};