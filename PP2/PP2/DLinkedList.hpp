#include "DNode.hpp"

//Elem is a typedef of string initialized in DNode.hpp
class DLinkedList : public DNode {
    private:
        DNode* header;
        DNode* trailer;
    protected:
        //Functions used 'under the hood' by addFront, addBack, removeFront, removeBack
        void add(DNode* v, const Elem& e);
        void remove(DNode* v);
    public:
        //Constructor and Destructor for the class objects
        DLinkedList();
        ~DLinkedList();
    
        //Reference functions to the front and back
        const Elem& front() const;
        const Elem& back() const;

        //Operations to add, remove and check if list is empty for the linked list
        void addFront(const Elem& e);
        void addBack(const Elem& e);
        Elem removeFront();
        Elem removeBack();
        bool empty() const;
};

 