#include "ArrayEntry.h"

ArrayEntry::ArrayEntry(int c, int i, int j, int index) : Position(c, i, j) {
	this->index = index;
}

int ArrayEntry::getIndex() {
    return this->index;
}

void ArrayEntry::setIndex(int index) {
    this->index = index;
}
