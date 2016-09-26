#ifndef ARRAYPOLYLIST_H
#define ARRAYPOLYLIST_H

#include "PolyList.h"
#include "ArrayEntry.h"
#include <iostream>
using std::cout;
// STEP 3 CODE

class ArrayPolyList : public PolyList {

private:

    ArrayEntry ** entries;

	int arraySize;

	int n;

    void resizeArray();

    void shiftLeft(int);

    void shiftRight(int);

public:
    ArrayPolyList();
    ~ArrayPolyList();

    void setEntries(ArrayEntry **);

    void insertTerm(int, int, int);

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
