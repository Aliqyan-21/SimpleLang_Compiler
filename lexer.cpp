#include "lexer.h"

// constructor to initialize the code member variable
Lexer::Lexer(const std::string &code) : code(code) {}

// tokenize function returns the tokens vector
std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (pos < code.size()) {
    char c = code[pos];

    // whitespace
    if (isspace(c)) {
      pos++;
      continue;
    }

    // alphabet/identifier/keyword
    else if (isalpha(c)) {
      std::string identifier;
      while (pos < code.size() && isalpha(code[pos])) {
        identifier += code[pos++];
      }
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
      while (pos < code.size() && isdigit(code[pos])) {
        num += code[pos++];
      }
      tokens.push_back({tokenType::TOKEN_NUMBER, num});
    }

    // special chars like '+', '-', '=', '==', '(', ')', '{', '}', ';'
    else {
      switch (c) {
      case '=':
        if (pos + 1 < code.size() && code[pos + 1] == '=') {
          tokens.push_back({tokenType::TOKEN_EQUAL, "=="});
          pos += 2;
        } else {
          tokens.push_back({tokenType::TOKEN_ASSIGN, "="});
          pos++;
        }
        break;
      case '+':
        tokens.push_back({tokenType::TOKEN_PLUS, "+"});
        pos++;
        break;
      case '-':
        tokens.push_back({tokenType::TOKEN_MINUS, "-"});
        pos++;
        break;
      case '(':
        tokens.push_back({tokenType::TOKEN_LBRACE, "("});
        pos++;
        break;
      case ')':
        tokens.push_back({tokenType::TOKEN_RBRACE, ")"});
        pos++;
        break;
      case '{':
        tokens.push_back({tokenType::TOKEN_LPAREN, "{"});
        pos++;
        break;
      case '}':
        tokens.push_back({tokenType::TOKEN_RPAREN, "}"});
        pos++;
        break;
      case ';':
        tokens.push_back({tokenType::TOKEN_SEMICOLON, ";"});
        pos++;
        break;
      default:
        tokens.push_back({tokenType::TOKEN_UNKNOWN, ""});
        pos++;
        std::cerr << "Invalid token : " << c << std::endl;
        break;
      }
    }
  }

  tokens.push_back({tokenType::TOKEN_EOF});
  return tokens;
}
