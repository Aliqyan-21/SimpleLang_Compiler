#include "lexer.h"

// constructor to initialize the code member variable
Lexer::Lexer(const std::string &code) : code(code) {}

// tokenize function returns the tokens vector
std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (pos <= code.size()) {
    char c = code[pos];

    // whitespace
    if (isspace(c)) {
      pos++;
      continue;
    }

    // alphabet/identifier/keyword
    else if (isalpha(c)) {
      std::string identifier;
      while (isalpha(code[pos])) {
        identifier += code[pos];
        pos++;
      }
      pos--;
      if (identifier == "if") {
        tokens.push_back({tokenType::TOKEN_IF, identifier});
      } else if (identifier == "int") {
        tokens.push_back({tokenType::TOKEN_INT, identifier});
      } else {
        tokens.push_back({tokenType::TOKEN_IDENTIFIER, identifier});
      }
    }

    // number
    else if (isdigit(c)) {
      std::string num;
      while (isdigit(code[pos])) {
        num += code[pos];
        pos++;
      }
      pos--;
      tokens.push_back({tokenType::TOKEN_NUMBER, num});
    }

    // special chars like '+', '-', '=', '==', '(', ')', '{', '}', ';'
    else if (c == '=' && pos <= code.size() && code[pos + 1] == '=') {
      tokens.push_back({tokenType::TOKEN_EQUAL, "=="});
    } else if (c == '=') {
      tokens.push_back({tokenType::TOKEN_ASSIGN, "="});
    } else if (c == '+') {
      tokens.push_back({tokenType::TOKEN_PLUS, "+"});
    } else if (c == '-') {
      tokens.push_back({tokenType::TOKEN_MINUS, "-"});
    } else if (c == '(') {
      tokens.push_back({tokenType::TOKEN_LBRACE, "("});
    } else if (c == ')') {
      tokens.push_back({tokenType::TOKEN_RBRACE, ")"});
    } else if (c == '{') {
      tokens.push_back({tokenType::TOKEN_LBRACE, "{"});
    } else if (c == '}') {
      tokens.push_back({tokenType::TOKEN_RBRACE, "}"});
    } else if (c == ';') {
      tokens.push_back({tokenType::TOKEN_SEMICOLON, ";"});
    }
    pos++;
  }

  tokens.push_back({tokenType::TOKEN_EOF});
  return tokens;
}
