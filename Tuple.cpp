//
// Created by Helaman on 10/25/2021.
//

#include "Tuple.h"

Tuple::Tuple(vector<string> neededValues) {
    values = neededValues;
}

string Tuple::toString(int i) {
    return values.at(i);
}

vector<string> Tuple::getValues() {
    return values;
}

bool Tuple::operator<(const Tuple &rhs) const {
    return values < rhs.values;
}

string Tuple::getValue (int i) {
    return values.at(i);
}