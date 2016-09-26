#ifndef POSITION_H
#define POSITION_H

class Position {

private:
    int c;
	int i;
	int j;

public:
    Position(int, int, int);
	
	virtual ~Position() { }
	
    int getC();
	int getI();
	int getJ();
};

#endif
