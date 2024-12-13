#ifndef PARSER
#define PARSER

#include "lexer.h"

// interface for ASTNode class
class ASTNode {};

// node for variable declaration
class AST_DeclarationNode : public ASTNode {
public:
  std::string varname;

  AST_DeclarationNode(const std::string &varname);
};

class Parser {
private:
  Lexer lexer;
  std::vector<Token> tokens;
  size_t currToken;

  ASTNode *variableDeclarationParser();

public:
  Parser(Lexer lexer);
  // for now void -> replace by ASTNode pointer return value
  ASTNode *parse();
};

#endif // !PARSER
