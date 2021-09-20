#include "Lexer.h"
#include <iostream>
#include <fstream>
#include "Token.h"

using namespace std;

int main(int argc, char** argv) {

    //File reading
    ifstream in;
    ofstream out;
    in.open(argv[1]);
    out.open(argv[2]);

    //turns file's contents into a string "inputResult"
    string inputResult = "";
    char a;

    while (in.get(a)) {
        inputResult += a;
    }

    //instantiates + runs Lexer
    Lexer* lexer = new Lexer();
    lexer->Run(inputResult);

    //TODO: retrieve and print Tokens
    vector<Token*> allTokens = lexer->getTokens();
    for (int i = 0; i < allTokens.size(); i++) {
        cout << allTokens.at(i)->toString() << endl;
    }

    cout << "Total Tokens = " << allTokens.size() << endl;

    //deletes Lexer
    delete lexer;
    return 0;
}