//
// Created by Helaman on 10/25/2021.
//

#ifndef LEXICALANALYZER_HEADER_H
#define LEXICALANALYZER_HEADER_H
#include <string>
#include <vector>

using namespace std;
class Header {
private:
    vector<string> attributes;
public:
    Header(vector<string> attributeList);
    vector<string> getAttributes();
    string toString();
    void addAttribute(string attributeToAdd);
};


#endif //LEXICALANALYZER_HEADER_H
