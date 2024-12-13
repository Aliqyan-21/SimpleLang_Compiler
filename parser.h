#ifndef PARSER
#define PARSER

#include "lexer.h"

// interface for ASTNode class and storage for all the nodes made while parsing
class ASTNode {
public:
  std::vector<ASTNode *> nodes;
  virtual ~ASTNode();
};

// node for variable declaration
class AST_DeclarationNode : public ASTNode {
public:
  std::string varname;

  AST_DeclarationNode(const std::string &varname);
};

// node for assignment of variable like a = c;
class AST_AssignmentNode : public ASTNode {
public:
  std::string varname;
  std::string op1;
  std::string opSym;
  std::string op2;

  AST_AssignmentNode(const std::string &varname, const std::string &op1,
                     const std::string &op2, const std::string &opSym);

  AST_AssignmentNode(const std::string varname, const std::string op);
};

class Parser {
private:
  Lexer lexer;
  std::vector<Token> tokens;
  size_t currToken;

  ASTNode *variableDeclarationParser();
  ASTNode *variableAssignmentParser();

public:
  Parser(Lexer lexer);
  ASTNode *parse();
};

#endif // !PARSER
