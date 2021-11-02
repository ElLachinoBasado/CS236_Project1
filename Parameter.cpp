//
// Created by Helaman on 9/29/2021.
//

#include "Parameter.h"

Parameter::Parameter(bool isCon, string input) {
    isConstant = isCon;
    value = input;
}

string Parameter::getValue() {return value;}

bool Parameter::getConstant() {return isConstant;}