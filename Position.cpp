#include "Position.h"

Position::Position(int c, int i, int j) {
    this->c = c;
    this->i = i;
    this->j = j;
}

int Position::getC() {
    return c;
}

int Position::getI() {
    return i;
}

int Position::getJ() {
    return j;
}
