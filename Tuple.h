//
// Created by Helaman on 10/25/2021.
//

#ifndef LEXICALANALYZER_TUPLE_H
#define LEXICALANALYZER_TUPLE_H
#include <string>
#include <vector>

using namespace std;
class Tuple {
private:
    vector<string> values;

public:
    Tuple(vector<string> neededValues);
    vector<string> getValues();
    string toString(int i);
    bool operator<(const Tuple &rhs) const;
    string getValue (int i);
};


#endif //LEXICALANALYZER_TUPLE_H
