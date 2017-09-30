#ifndef TOKEN_H
#define TOKEN_H

#include "Constants.h"

#include <string>

class Token
{
public:
    Token() : empty(true) {}
    Token(TokenId id, const std::string &lexeme, int position)
      : id(id), lexeme(lexeme), position(position), empty(false) { }

    TokenId getId() const { return id; }
    const std::string &getLexeme() const { return lexeme; }
    int getPosition() const { return position; }
    bool isEmpty() const { return empty; }

private:
    TokenId id;
    std::string lexeme;
    int position;
    bool empty;
};

#endif
