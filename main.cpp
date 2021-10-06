#include "Lexer.h"
#include "Parser.h"
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

    vector<Token*> allTokens = lexer->getTokens();

    Parser* parser = new Parser(allTokens);
    try {
        parser->parse();
    } catch (Token* token) {
        cout << "Failure!" << endl << token->toString();
    }

    //deletes stuff
    delete lexer;
    delete parser;
    return 0;
}