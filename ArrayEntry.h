#ifndef ARRAYENTRY_H
#define ARRAYENTRY_H

#include "Position.h"

class ArrayEntry : public Position {

private:
    int index;

public:
    ArrayEntry(int, int, int, int);
	
	int getIndex();
	void setIndex(int);
};

#endif
