#ifndef DLLPOLYLIST_H
#define DLLPOLYLIST_H

#include "PolyList.h"
#include "DLLNode.h"
#include <iostream>
using std::cout;

class DLLPolyList : public PolyList {

private:
    DLLNode * head;
	DLLNode * tail;

public:
    DLLPolyList();
    ~DLLPolyList();

    void insertTerm(int, int, int);
    void remove(Position *);

    Position* first();
    Position* last();

    Position* before(Position*);
    Position* after(Position*);

    bool isFirst(Position*);
    bool isLast(Position*);

    bool isEmpty();

    int size();
};

#endif
