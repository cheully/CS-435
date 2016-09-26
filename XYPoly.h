#ifndef XYPOLY_H
#define XYPOLY_H

#include <string>
#include <stdlib.h>
#include <math.h>
#include "DLLPolyList.h"
#include "ArrayPolyList.h"

using std::string;
using std::endl;

class XYPoly {

private:
    PolyList * list;

	void initialize();
    string removeSpace(const string&);

public:

    XYPoly(const string&);
	XYPoly();
	XYPoly(const XYPoly *);

    ~XYPoly();

    void output() const;

    bool equalTo(const XYPoly *) const;

	XYPoly* scalarMultiply(const int c) const;

    XYPoly* add(const XYPoly*) const;
    XYPoly* subtract(const XYPoly*) const;
    XYPoly* multiply(const XYPoly*) const;
    XYPoly* power(const int pow) const;

	long evaluate(int, int) const;
};

#endif
