#include <string>
#include <vector>

enum tokenType{
    newline,
    Semicolon,
    Name,
    String,
    Number,
    Bool,
    MathOperactor,
    LogicOperator,
    CircleBracketOpen,
    CircleBracketClose,
    SquareBracketOpen,
    SquareBracketClose,
    CurlyBracketOpen,
    CurlyBracketClose,
    

};

class token{
    int line;
    int position;
    int len;
    tokenType type;
    std::string data;
};

class file{
    std::string filename;
    std::vector<token> tokens;
};