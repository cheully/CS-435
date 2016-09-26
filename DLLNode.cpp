#include "DLLNode.h"

DLLNode::DLLNode(int c, int i, int j) : Position(c, i, j) {
	this->next = NULL;
	this->prev = NULL;
}

void DLLNode::setNext(DLLNode* next) {
    this->next = next;
}

void DLLNode::setPrev(DLLNode* prev) {
    this->prev = prev;
}

DLLNode* DLLNode::getNext() {
    return next;
}

DLLNode* DLLNode::getPrev() {
    return prev;
}
