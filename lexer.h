#ifndef LEXER
#define LEXER

#include <iostream>
#include <string>
#include <vector>

enum tokenType {
  TOKEN_INT,
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,
  TOKEN_ASSIGN,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_IF,
  TOKEN_EQUAL,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_SEMICOLON,
  TOKEN_UNKNOWN,
  TOKEN_EOF
};

struct Token {
  tokenType name;
  std::string value;
};

class Lexer {
private:
  std::string code;
  size_t pos = 0;

public:
  Lexer(const std::string &code);
  std::vector<Token> tokenize();
};

#endif // !LEXER
