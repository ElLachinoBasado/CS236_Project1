//
// Created by Helaman on 10/25/2021.
//

#include "Header.h"

Header::Header(vector<string> attributeList) {
    attributes = attributeList;
}

vector<string> Header::getAttributes() {
    return attributes;
}

string Header::toString() {
    string headerElements = "";
    for (auto elem : attributes) {
        headerElements += elem;
        headerElements += " ";
    }
    return headerElements;
}