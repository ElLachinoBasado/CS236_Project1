#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EOF_TYPE,
    UNDEFINED
};

class Token
{
private:
    string value;
    int lineNumber;
    TokenType thisType;
public:
    Token(TokenType type, std::string description, int line);
    string toString();
    string tokenToString(TokenType token);
    string getType();
    string getValue();
};

#endif // TOKEN_H

