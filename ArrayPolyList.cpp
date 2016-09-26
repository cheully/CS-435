#include "ArrayPolyList.h"

// STEP 3 CODE

ArrayPolyList::ArrayPolyList() {
	this->n = 0;
	this->arraySize = 5; // TODO: What should be the initial size?

	// TODO: Initialize the array.
    this->entries = new ArrayEntry*[this->arraySize];
	for(int i = 0; i < this->arraySize; i++)
        this->entries[i] = NULL;
}

ArrayPolyList::~ArrayPolyList() {
    /*for(int i = 0; i < this->arraySize; i++)
        delete this->entries[i];

    delete this->entries;*/
}

void ArrayPolyList::insertTerm(int c, int i, int j) {

    if(c == 0)
        return;

    if(this->n == 0){
        ArrayEntry *entry = new ArrayEntry(c, i, j, 0);
        this->entries[0] = entry;
        this->n++;
        return;
    }

    if(n == arraySize)
        resizeArray();

    for(int index = 0; index < this->n; index++){

            if ( ( this->entries[index]->getI() > i ) || ( this->entries[index]->getI() == i && this->entries[index]->getJ() > j ) ){

                shiftRight(index);
                ArrayEntry *entry = new ArrayEntry(c, i, j, index);

                this->entries[index] = entry;
                this->n++;
                return;

            } else if( ( this->entries[index]->getI() == i ) && (this->entries[index]->getJ() == j) ){
                int newC = this->entries[index]->getC() + c;

                if(newC != 0){
                    ArrayEntry *entry = new ArrayEntry(newC, i, j, index);
                    this->entries[index] = entry;
                    return;

                } else {
                    shiftLeft(index);
                    this->n--;
                    return;
                }

            }
    }

    ArrayEntry *entry = new ArrayEntry(c, i, j, this->n);
    this->entries[this->n] = entry;
    this->n++;

    return;

}

void ArrayPolyList :: shiftRight (int currentIdx){
    for(int i = this->n; i > currentIdx; i--){
        this->entries[i] = this->entries[i - 1];
        this->entries[i]->setIndex(i);
    }
}

void ArrayPolyList :: shiftLeft (int currentIdx){

    for(int i = currentIdx + 1; i < this->n ; i++){
        this->entries[i - 1] = this->entries[i];
        this->entries[i - 1]->setIndex(i - 1);
    }
}

void ArrayPolyList :: resizeArray(){

    ArrayEntry ** newEntries = new ArrayEntry*[this->n * 2];

    for(int i = 0; i < this->n; i++)
        newEntries[i] = this->entries[i];

    // Double the size of the array
    this->arraySize = this->n * 2;

    for(int j = (this->arraySize / 2); j < this->arraySize; j++)
        newEntries[j] = NULL;

    setEntries(newEntries);
}

void ArrayPolyList :: setEntries(ArrayEntry **newEntries){
    this->entries = newEntries;
}

Position* ArrayPolyList::first() {
    return this->entries[ this->n - 1 ];
}

Position* ArrayPolyList::last() {
    return this->entries[0];
}

Position* ArrayPolyList::before(Position * p) {
    ArrayEntry * entry = dynamic_cast<ArrayEntry*>(p);

    if(this->entries[ this->n - 1 ] == entry){
        cout << "\nError: No accessible element before this point!\n";
        return entry;
    }

    return this->entries[entry->getIndex() + 1];
}

Position* ArrayPolyList::after(Position * p) {
    ArrayEntry * entry = dynamic_cast<ArrayEntry*>(p);

    if(this->entries[ 0 ] == entry){
        cout << "\nError: No accessible element before this point!\n";
        return entry;
    }

    return this->entries[entry->getIndex() - 1];
}

bool ArrayPolyList::isFirst(Position * p) {
    ArrayEntry * entry = dynamic_cast<ArrayEntry*>(p);

    if(this->entries[ this->n - 1 ] == entry)
        return true;
    else
        return false;
}

bool ArrayPolyList::isLast(Position * p) {
    ArrayEntry * entry = dynamic_cast<ArrayEntry*>(p);

    if(this->entries[ 0 ] == entry)
        return true;
    else
        return false;
}

bool ArrayPolyList::isEmpty() {
    if(this->n == 0)
        return true;
    else
        return false;
}

int ArrayPolyList::size() {
    return this->n;
}


