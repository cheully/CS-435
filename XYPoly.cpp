#include "XYPoly.h"

XYPoly::XYPoly() {
	initialize();
}

XYPoly::XYPoly(const string& str) {
	initialize();
    int c = 0, i = 0, j = 0;
    bool firstSignFlag = false;
    char sign = '+';
    string newStr = removeSpace(str);

    if(newStr == "")
        return;

    for(int k = 0; k < newStr.length(); k++){

        if(newStr[k] == '-' && firstSignFlag == false){
            sign = newStr[k];
            firstSignFlag = true;
            continue;
        }

        if(newStr[k] == '0'){
            while(newStr[k] != '+' && newStr[k] != '-' && newStr[k] != '\0')
                k++;

            if(newStr[k] != '+' || newStr[k] != '-')
                k--;
            continue;
        }

        firstSignFlag = true;
        if(newStr[k] >= '0' && newStr[k] <= '9'){
            string temp = "";
            if(sign == '-')
                temp += sign;
            temp += newStr[k];

            ++k;
            while(newStr[k] >= '0' && newStr[k] <= '9'){
                temp += newStr[k];
                ++k;
            }
            --k;
            c = atoi(temp.c_str());
        }

        else if(newStr[k] == 'x' || newStr[k] == 'y'){
            if(c == 0)
                c = ((k-1 != -1) && (newStr[k-1] == '-') ? -1 : 1);

            switch(newStr[k]){
                case 'x':
                    if(newStr[k+1] < '0' || newStr[k+1] > '9')
                        i = 1;
                    else {
                        ++k;
                        string temp = "";

                        while(newStr[k] >= '0' && newStr[k] <= '9' && newStr[k] != '\0'){
                            temp += newStr[k];
                            ++k;
                        }

                        --k;

                        i = atoi(temp.c_str());
                    }

                    break;
                case 'y':
                    if(newStr[k+1] < '0' || newStr[k+1] > '9')
                        j = 1;
                    else {
                        ++k;
                        string temp = "";

                        while(newStr[k] >= '0' && newStr[k] <= '9' && newStr[k] != '\0'){
                            temp += newStr[k];
                            ++k;
                        }
                        --k;
                        j = atoi(temp.c_str());
                    }
                    break;
            }

        }

        else if(newStr[k] == '+' || newStr[k] == '-'){
            if(c != 0)
                list->insertTerm(c, i, j);
            sign = newStr[k];
            c = 0; i = 0; j = 0;
        }

    }

    if(c != 0)
        list->insertTerm(c, i, j);
}

XYPoly::XYPoly(const XYPoly * p) {
	initialize();
	PolyList *pList = p->list;
	Position *copyP = pList->first();

    while(!pList->isLast(copyP)){
        list->insertTerm(copyP->getC(), copyP->getI(), copyP->getJ());
        copyP = pList->after(copyP);
    }
    list->insertTerm(copyP->getC(), copyP->getI(), copyP->getJ());
}

XYPoly::~XYPoly() {
    delete this->list;
}

void XYPoly::initialize() {
	// Do not change this line until Step 3
    this->list = new DLLPolyList();

	// Step 3 initialization
    //this->list = new ArrayPolyList();
}

string XYPoly::removeSpace(const string &str){
    string newString = "";

    for(unsigned int i = 0; i < str.length(); i++){
        if(str[i] == ' ')
            continue;
        newString += str[i];
    }

    return newString;
}

void XYPoly::output() const {
    if(list->isEmpty()){
        cout << "0" << endl;
        return;
    }

    Position *p = list->first();
    bool firstVal = false;

    while(!list->isLast(p)){
        //cout << p->getC() << p->getI() << p->getJ();
        if(p->getC() <= -1 && firstVal == false){
            if(p->getC() == -1 && (p->getI() != 0 || p->getJ() != 0))
                cout << "-";
            else
                cout << "-" << abs(p->getC());
            firstVal = true;

        } else if (p->getC() == 1 || p->getC() == -1){
            if (p->getI() == 0 && p->getJ() == 0)
                cout << abs(p->getC());
            else
                cout << "";
            firstVal = true;

        } else {
            firstVal = true;
            cout << abs(p->getC());
        }

        if(p->getI() != 0){
            cout << "x";
            if(p->getI() > 1)
                cout << "^" << p->getI();
        } else
            cout << "";

        if(p->getJ() != 0){
            cout << "y";
            if(p->getJ() > 1)
                cout << "^" << p->getJ();
       } else
            cout << "";

        p = list->after(p);
        if(p->getC() > 0)
            cout << " + ";
        else
            cout << " - ";
    }
 //cout << p->getC() << p->getI() << p->getJ();
    if(p->getC() <= -1 && firstVal == false){
        if(p->getC() == -1 && (p->getI() != 0 || p->getJ() != 0))
            cout << "-";
        else
            cout << "-" << abs(p->getC());
        firstVal = true;

    } else if (p->getC() == 1 || p->getC() == -1){
        if (p->getI() == 0 && p->getJ() == 0)
            cout << abs(p->getC());
        else
            cout << "";
        firstVal = true;

    } else {
        firstVal = true;
        cout << abs(p->getC());
    }

    if(p->getI() != 0){
        cout << "x";
        if(p->getI() > 1)
            cout << "^" << p->getI();
    } else
        cout << "";

    if(p->getJ() != 0){
        cout << "y";
        if(p->getJ() > 1)
            cout << "^" << p->getJ();
   } else
        cout << "";

    cout << endl;
}

bool XYPoly::equalTo(const XYPoly* p) const {
    PolyList *pList = p->list;
    if(pList->size() != list->size())
        return false;

    Position *m1 = list->first();
    Position *m2 = pList->first();

    while(!list->isLast(m1)){
        if(m1->getC() != m2->getC() || m1->getI() != m2->getI() || m1->getJ() != m2->getJ())
            return false;
        m1 = list->after(m1);
        m2 = pList->after(m2);
    }

    if(m1->getC() != m2->getC() || m1->getI() != m2->getI() || m1->getJ() != m2->getJ())
        return false;
    else
        return true;
}

XYPoly* XYPoly::scalarMultiply(const int c) const {
    XYPoly *rtnXYPoly = new XYPoly();
    PolyList *rtnPL = rtnXYPoly->list;
    Position *p = list->first();
    int newC = 0;

    while(!list->isLast(p)){
        newC = p->getC() * c;

        rtnPL->insertTerm(newC, p->getI(), p->getJ());

        p = list->after(p);
    }

    newC = p->getC() * c;
    rtnPL->insertTerm(newC, p->getI(), p->getJ());

    return rtnXYPoly;
}


XYPoly* XYPoly::add(const XYPoly* p) const {
    XYPoly *rtnXYPoly = new XYPoly();
    PolyList *rtnPL = rtnXYPoly->list;
    PolyList *pList = p->list;
    Position *p1 = list->first();
    Position *p2 = pList->first();
    int newC = 0;

    while(!list->isLast(p1) && !pList->isLast(p2)){

        if(p1->getI() == p2->getI() && p1->getJ() == p2->getJ()){
            newC = p1->getC() + p2->getC();
            rtnPL->insertTerm(newC, p1->getI(), p1->getJ());
        } else {
            rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
            rtnPL->insertTerm(p2->getC(), p2->getI(), p2->getJ());
        }

        p1 = list->after(p1);
        p2 = pList->after(p2);
    }

    if(p1->getI() == p2->getI() && p1->getJ() == p2->getJ()){
        newC = p1->getC() + p2->getC();
        rtnPL->insertTerm(newC, p1->getI(), p1->getJ());
    } else {
      rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
      rtnPL->insertTerm(p2->getC(), p2->getI(), p2->getJ());
    }

    if(list->isLast(p1) && !pList->isLast(p2)){
        p2 = pList->after(p2);
        while(!pList->isLast(p2)){
            rtnPL->insertTerm(p2->getC(), p2->getI(), p2->getJ());
            p2 = pList->after(p2);
        }
        rtnPL->insertTerm(p2->getC(), p2->getI(), p2->getJ());
    }

    if(!list->isLast(p1) && pList->isLast(p2)){
        p1 = list->after(p1);
        while(!list->isLast(p1)){
            rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
            p1 = list->after(p1);
        }
        rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
    }

    return rtnXYPoly;
}

XYPoly* XYPoly::subtract(const XYPoly* p) const {
    XYPoly *rtnXYPoly = new XYPoly();
    PolyList *rtnPL = rtnXYPoly->list;
    PolyList *pList = p->list;
    Position *p1 = list->first();
    Position *p2 = pList->first();
    int newC = 0;

    while(!list->isLast(p1) && !pList->isLast(p2)){
        if(p1->getI() == p2->getI() && p1->getJ() == p2->getJ()){
            newC = p1->getC() - p2->getC();
            rtnPL->insertTerm(newC, p1->getI(), p1->getJ());
        } else {
            rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
            rtnPL->insertTerm(-1*p2->getC(), p2->getI(), p2->getJ());
        }

        p1 = list->after(p1);
        p2 = pList->after(p2);
    }

    if(p1->getI() == p2->getI() && p1->getJ() == p2->getJ()){
        newC = p1->getC() - p2->getC();
        rtnPL->insertTerm(newC, p1->getI(), p1->getJ());
    } else {
      rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
      rtnPL->insertTerm(-1*p2->getC(), p2->getI(), p2->getJ());
    }

    if(list->isLast(p1) && !pList->isLast(p2)){
        p2 = pList->after(p2);
        while(!pList->isLast(p2)){
            rtnPL->insertTerm(-1*p2->getC(), p2->getI(), p2->getJ());
            p2 = pList->after(p2);
        }
        rtnPL->insertTerm(-1*p2->getC(), p2->getI(), p2->getJ());
    }

    if(!list->isLast(p1) && pList->isLast(p2)){
        p1 = list->after(p1);
        while(!list->isLast(p1)){
            rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
            p1 = list->after(p1);
        }
        rtnPL->insertTerm(p1->getC(), p1->getI(), p1->getJ());
    }

    return rtnXYPoly;
}

/*Note: I added two lines after the newC calculations to check if an overflow occur. The
    number 2 represents the value of the C while its exponent should be 9 (2e9). Due to the constriction
    of the data structure, I do not know how to represent the exponent in this structure, so only the
    value of the exponent (2 and similar) is stored in the DLLNode. */
XYPoly* XYPoly::multiply(const XYPoly* p) const {
    XYPoly *rtnXYPoly = new XYPoly();
    PolyList *rtnPL = rtnXYPoly->list;
    PolyList *pList = p->list;
    Position *p1 = list->first();
    Position *p2 = pList->first();
    int newC, newX, newY;

    while(!list->isLast(p1)){

        while(!pList->isLast(p2)){
            newC = p1->getC() * p2->getC();
            if(newC >= 2000000)
                newC = 2;
            newX = p1->getI() + p2->getI();
            newY = p1->getJ() + p2->getJ();
            rtnPL->insertTerm(newC, newX, newY);
            p2 = pList->after(p2);
        }
        newC = p1->getC() * p2->getC();
        if(newC >= 2000000)
            newC = 2;
        newX = p1->getI() + p2->getI();
        newY = p1->getJ() + p2->getJ();
        rtnPL->insertTerm(newC, newX, newY);
        p1 = list->after(p1);
        p2 = pList->first();
    }

    while(!pList->isLast(p2)){
        newC = p1->getC() * p2->getC();
        if(newC >= 2000000)
            newC = 2;
        newX = p1->getI() + p2->getI();
        newY = p1->getJ() + p2->getJ();
        rtnPL->insertTerm(newC, newX, newY);
        p2 = pList->after(p2);
    }
    newC = p1->getC() * p2->getC();
    if(newC >= 2000000)
        newC = 2;
    newX = p1->getI() + p2->getI();
    newY = p1->getJ() + p2->getJ();
    rtnPL->insertTerm(newC, newX, newY);
    return rtnXYPoly;
}

XYPoly* XYPoly::power(const int p) const {
    if(p == 0){
        XYPoly *rtnXYPoly = new XYPoly();
        PolyList *rtnPL = rtnXYPoly->list;
        rtnPL->insertTerm(1,0,0);
        return rtnXYPoly;
    }

    if(p == 1){
        XYPoly *rtnXYPoly = new XYPoly(this);
        return rtnXYPoly;
    }

    if(p == 2)
        return this->multiply(this);

    if(p == 3)
        return this->multiply(this->power(p - 1));


    if(p%2 == 1)
        return this->multiply(this->power(p - 1));
    else
        return this->multiply(this->multiply( this->power(p - 2) ));

}

long XYPoly::evaluate(int x, int y) const {
    long evaluatedPoly = 0;
    int current_x = 0, diff_x = 0; long xEvaluated = pow(x, current_x);
    int current_y = 0, diff_y = 0; long yEvaluated = 1;
    Position *p = list->last();


    while(!list->isFirst(p)){
        if(current_x != p->getI()){
            diff_x = p->getI() - current_x;
            current_x = p->getI();
            xEvaluated = xEvaluated * pow(x, diff_x);
        }

        if(current_y < p->getJ()){
            diff_y = p->getJ() - current_y;
            current_y = p->getJ();
            yEvaluated = yEvaluated * pow(y, diff_y);
            evaluatedPoly += p->getC() * xEvaluated * yEvaluated;
        }
        else if(current_y > p->getJ())
            evaluatedPoly += p->getC() * xEvaluated * ( yEvaluated / pow(y, current_y - p->getJ()) );

        else
            evaluatedPoly += p->getC() * xEvaluated * yEvaluated;

        p = list->before(p);
    }

    if(current_x != p->getI()){
        diff_x = p->getI() - current_x;
        current_x = p->getI();
        xEvaluated = xEvaluated * pow(x, diff_x);
    }

    if(current_y < p->getJ()){
        diff_y = p->getJ() - current_y;
        current_y = p->getJ();
        yEvaluated = yEvaluated * pow(y, diff_y);
        evaluatedPoly += p->getC() * xEvaluated * yEvaluated;
    }
    else if(current_y > p->getJ())
        evaluatedPoly += p->getC() * xEvaluated * ( yEvaluated / pow(y, current_y - p->getJ()) );

    else
        evaluatedPoly += p->getC() * xEvaluated * yEvaluated;

    return evaluatedPoly;
}

