//
// Created by Helaman on 9/29/2021.
//
#include <string>
#ifndef LEXICALANALYZER_PARAMETER_H
#define LEXICALANALYZER_PARAMETER_H

using namespace std;
class Parameter {
private:
    bool isConstant;
    string value;
public:
    Parameter(bool isCon, string input);
    string getValue();
};


#endif //LEXICALANALYZER_PARAMETER_H
