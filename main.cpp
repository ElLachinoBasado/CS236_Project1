#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include "Token.h"
#include "DGraph.h"

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
    DatalogProgram* datalog;
    try {
        parser->parse();
        datalog = parser->getProgram();
    } catch (Token* token) {
        cout << "Failure!" << endl << token->toString();
    }

    Interpreter * interpreter = new Interpreter(datalog);
    interpreter->evaluateAllSCCRules();    //interpreter->evaluateAllRules();
    interpreter->evaluateAllQueries();
    //deletes stuff
    delete lexer;
    delete parser;
    delete interpreter;
    return 0;
}