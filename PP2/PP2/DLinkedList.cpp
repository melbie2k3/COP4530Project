#include "DLinkedList.hpp"
DLinkedList::DLinkedList() {
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    trailer->prev = header;
}

DLinkedList::~DLinkedList(){
    while (!empty()) removeFront();
    delete header;
    delete trailer;
}

bool DLinkedList::empty() const {
    return (header->next == trailer);
}

const Elem& DLinkedList::front() const {
    return header->next->elem;
}

const Elem& DLinkedList::back() const {
    return trailer->prev->elem;
}

void DLinkedList::add(DNode* v, const Elem& e) {
    /* This function will add a node into the list and set the pointers appropriately to 
       traverse through the list afterwards
    */
    DNode* u = new DNode;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}

void DLinkedList::addFront(const Elem &e) {
    add(header->next, e);
}

void DLinkedList::addBack(const Elem &e) {
    add(trailer, e);
}

void DLinkedList::remove(DNode* v){
    /* This function will remove the node passed to it and will move the pointers to make sure
       the links are set up properly
    */
    if (!empty()){
        DNode* u = v->prev; 
        DNode* w = v->next;
        u->next = w;
        w->prev = u;
        delete v;
    }
}

Elem DLinkedList::removeFront(){
    if(!empty()){
        Elem e = front();
        remove(header->next);
        return e;
    } else {
        throw("List empty");
    }
}

Elem DLinkedList::removeBack(){
    if(!empty()){
        Elem e = back();
        remove(trailer->prev);
        return e;
    } else{
        throw ("List empty");
    }
}