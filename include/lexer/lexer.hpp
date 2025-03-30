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
    int character;
    tokenType type;
    std::string name;
};

class file{
    std::string filename;
    std::vector<token> tokens;
};