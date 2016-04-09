#pragma once

#include "StackInterface.h"
#include "Node.h"
#include <vector>
#include <cassert>

using namespace std;

template<class ItemType>
class DLinkedStack : public StackInterface<ItemType> {
private:
    Node<ItemType> *headPtr;    // Pointer to first node in the chain;
    Node<ItemType> *topPtr;    // Pointer to (last) node in the chain that contains the stack's top
public:

    DLinkedStack();

    DLinkedStack(const DLinkedStack<ItemType> &aStack);    // Copy constructor

    virtual ~ DLinkedStack();    // Destructor

    Node<ItemType> *getPointerTo(const ItemType &target) const;

    bool isEmpty() const;

    bool push(const ItemType &newItem);

    bool pop();

    ItemType peek() const;

    vector<ItemType> toVector() const;

    Node<ItemType> *getHeadPTR() const;

    Node<ItemType> *getTopPTR() const;
};

template<class ItemType>
DLinkedStack<ItemType>::DLinkedStack() : headPtr(nullptr), topPtr(nullptr) {
}

template<class ItemType>
DLinkedStack<ItemType>::DLinkedStack(const DLinkedStack<ItemType> &aStack) {
    //Implement the copy constructor
    Node<ItemType> *origSPtr = aStack.headPtr;
    if (origSPtr == nullptr) {
        topPtr = headPtr = nullptr;
    }
    else {
        // should work if basicStack2 = basicStack in Gtest
        headPtr = new Node<ItemType>();
        headPtr->setItem(origSPtr->getItem());

        //similar to SDLL, just ensure to renew vals of topPtr & .getPrev
        Node<ItemType> *newSPtr = headPtr;
        origSPtr = origSPtr->getNext();

        while (origSPtr != nullptr){    // when traversing, keep a pointer to count
            ItemType nextItem = origSPtr->getItem(); //next value from aStack/origSPtr
            Node<ItemType> *newNodePtr = new Node<ItemType>(nextItem); //new node from the next value
            newSPtr->setNext(newNodePtr);
            newNodePtr->setPrev(headPtr);
            topPtr = newNodePtr;
            origSPtr = origSPtr->getNext();
        }

        newSPtr->setNext(nullptr);
    }
}
template<class ItemType>
DLinkedStack<ItemType>::~DLinkedStack() {
    // Implement the destructor : call pop() until stack is empty
    while (!isEmpty()&& topPtr->getNext()!= nullptr)
        pop();
}

template<class ItemType>
Node<ItemType> *DLinkedStack<ItemType>::getPointerTo(const ItemType &target) const {
    //Return the Node pointer that contains the target(return nullptr if not found)
    bool isFound = false;
    Node<ItemType> *current = headPtr;

    while ((current != nullptr) && !isFound) {
        if (target == current->getItem()){
            isFound = true;
        }
        else{
            current = current->getNext();
        }
    }
    return current;
}

template<class ItemType>
bool DLinkedStack<ItemType>::isEmpty() const {
    //return true if the list is empty
    return topPtr == nullptr;
}

template<class ItemType>
bool DLinkedStack<ItemType>::push(const ItemType &newItem) {
    // Push an item on the Doubly Linked Stack
    if(topPtr == nullptr){
        topPtr = new Node<ItemType>(newItem);
        headPtr = topPtr;
    }
    else {
        Node<ItemType> *addedNode = new Node<ItemType>(newItem);
        addedNode->setPrev(topPtr);
        topPtr->setNext(addedNode);
        topPtr = addedNode;
    }

    return true;

}

template<class ItemType>
bool DLinkedStack<ItemType>::pop() {
    //Pop an item from the stack - Return true if successful
    if(headPtr != nullptr){
        topPtr = topPtr->getPrev();
        topPtr->setNext(nullptr);
        return true;
    }
    return false;
}

template<class ItemType>
ItemType DLinkedStack<ItemType>::peek() const {//Assume this never fails.
    //return the element stored at the top of the stack (topPtr)
    if(!isEmpty())
        return topPtr->getItem();
}

template<class ItemType>
vector<ItemType> DLinkedStack<ItemType>::toVector() const {
    // DO NOT MODIFY THIS FUNCTION
    vector<ItemType> returnVector;
    // Put stack items into a vector in top to bottom order
    Node<ItemType> *curPtr = topPtr;
    while (curPtr != nullptr) {
        returnVector.push_back(curPtr->getItem());
        curPtr = curPtr->getPrev();
    }
    return returnVector;
}

template<class ItemType>
Node<ItemType> *DLinkedStack<ItemType>::getHeadPTR() const {
    // DO NOT MODIFY THIS FUNCTION
    return headPtr;
}

template<class ItemType>
Node<ItemType> *DLinkedStack<ItemType>::getTopPTR() const {
    // DO NOT MODIFY THIS FUNCTION
    return topPtr;
}