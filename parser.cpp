#include "parser.h"
#include "lexer.h"

// ********** Parser class ********
// constructor
Parser::Parser(Lexer lexer) : lexer(lexer), currToken(0) {}

// for parsing the vector of tokens
ASTNode *Parser::parse() {
  ASTNode *ast = new ASTNode();
  std::vector<Token> tokens = lexer.tokenize();

  while (currToken < tokens.size()) {
    auto c = tokens[currToken];
    if (c.name == tokenType::TOKEN_INT) {
      ast = variableDeclarationParser();
    }
  }

  return ast;
}

ASTNode *Parser::variableDeclarationParser() {
  currToken++;
  if (tokens[currToken].name == tokenType::TOKEN_IDENTIFIER) {
    std::string varname = tokens[currToken].value;
    currToken++;
    if (tokens[currToken].name == tokenType::TOKEN_SEMICOLON) {
      return new AST_DeclarationNode(varname);
    }
  }
  return nullptr;
}

// ********** ASTNode class ********
AST_DeclarationNode::AST_DeclarationNode(const std::string &varname)
    : varname(varname) {}
