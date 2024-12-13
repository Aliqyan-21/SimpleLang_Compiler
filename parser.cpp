#include "parser.h"
#include "lexer.h"

// ********** ASTNode class **********

ASTNode::~ASTNode() {}

AST_DeclarationNode::AST_DeclarationNode(const std::string &varname)
    : varname(varname) {}

AST_AssignmentNode::AST_AssignmentNode(const std::string &varname,
                                       const std::string &op1,
                                       const std::string &op2,
                                       const std::string &opSym)
    : varname(varname), op1(op1), op2(op2), opSym(opSym) {}

AST_AssignmentNode::AST_AssignmentNode(const std::string varname,
                                       const std::string op)
    : varname(varname), op1(op), op2(""), opSym("") {}

// ********** Parser class **********

// constructor
Parser::Parser(Lexer lexer) : lexer(lexer), currToken(0) {
  tokens = lexer.tokenize();
}

// for parsing the vector of tokens
ASTNode *Parser::parse() {
  ASTNode *root = new ASTNode();
  while (currToken < tokens.size()) {
    auto c = tokens[currToken];
    if (c.name == tokenType::TOKEN_INT) {
      ASTNode *node = variableDeclarationParser();
      if (node) {
        root->nodes.push_back(node);
      }
    } else if (c.name == tokenType::TOKEN_IDENTIFIER) {
      ASTNode *node = variableAssignmentParser();
      if (node) {
        root->nodes.push_back(node);
      }
    } else {
      currToken++;
    }
  }
  return root; // so this will have a nodes vector with all our nodes stored in
               // it
}

// todo: implement compiler like error handling instead of interpreter - later
ASTNode *Parser::variableDeclarationParser() {
  currToken++;
  if (tokens[currToken].name == tokenType::TOKEN_IDENTIFIER) {
    std::string varname = tokens[currToken].value;
    currToken++;
    if (tokens[currToken].name == tokenType::TOKEN_SEMICOLON) {
      currToken++;
      return new AST_DeclarationNode(varname);
    } else {
      std::cerr << "Syntax error at token " << tokens[currToken].value
                << " -> missing semicolon." << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "Syntax error at token " << tokens[currToken].value
              << " -> missing identifier." << std::endl;
    exit(1);
  }
}

ASTNode *Parser::variableAssignmentParser() {
  std::string varname = tokens[currToken].value;

  currToken++;
  if (tokens[currToken].name != tokenType::TOKEN_ASSIGN) {
    std::cerr << "not a valid token: missing '='" << std::endl;
    exit(1);
  }
  currToken++;

  if (tokens[currToken].name != tokenType::TOKEN_IDENTIFIER &&
      tokens[currToken].name != tokenType::TOKEN_NUMBER) {
    std::cerr << "syntax error: expected variable name or a literal after '='"
              << std::endl;
    exit(1);
  }
  std::string op1 = tokens[currToken].value;
  currToken++;

  if (tokens[currToken].name == tokenType::TOKEN_SEMICOLON) {
    currToken++;
    return new AST_AssignmentNode(varname, op1);
  } else if (tokens[currToken].name == tokenType::TOKEN_PLUS ||
             tokens[currToken].name == tokenType::TOKEN_MINUS) {
    std::string opSym = tokens[currToken].value;
    currToken++;
    if (tokens[currToken].name != tokenType::TOKEN_IDENTIFIER &&
        tokens[currToken].name != tokenType::TOKEN_NUMBER) {
      std::cerr
          << "Syntax Error: expected variable name or literal after operator"
          << std::endl;
      exit(1);
    }
    std::string op2 = tokens[currToken].value;
    currToken++;

    if (tokens[currToken].name != tokenType::TOKEN_SEMICOLON) {
      std::cerr << "Syntax Error: expected ';' after variable name"
                << std::endl;
      exit(1);
    }

    currToken++;
    return new AST_AssignmentNode(varname, op1, op2, opSym);
  }

  // for now
  std::cerr << "Syntax Error: unexpected token" << tokens[currToken].value
            << "in assignment of " << varname << std::endl;
  exit(1);
}
