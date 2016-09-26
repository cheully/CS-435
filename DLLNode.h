#ifndef DLLNODE_H
#define DLLNODE_H

#include "Position.h"
#include <cstddef>

class DLLNode : public Position {

private:
    DLLNode * next;
	DLLNode * prev;

public:
    DLLNode(int, int, int);

	void setNext(DLLNode*);
	DLLNode* getNext();

	void setPrev(DLLNode*);
	DLLNode* getPrev();
};

#endif
