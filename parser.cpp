#include "parser.h"
#include "lexer.h"
#include <stdexcept>

// ********** ASTNode class **********

ASTNode::~ASTNode() {
  for (auto &i : nodes) {
    delete i;
  }
}

AST_DeclarationNode::AST_DeclarationNode(const std::string &varname)
    : varname(varname) {}

AST_AssignmentNode::AST_AssignmentNode(const std::string &varname,
                                       ASTNode *expression)
    : varname(varname), expression(expression) {}

AST_IfStatementNode::AST_IfStatementNode(ASTNode *condition, ASTNode *statement)
    : condition(condition), statement(statement) {}

AST_ConditionNode::AST_ConditionNode(const std::string &lhs,
                                     const std::string &rhs,
                                     const std::string &opSym)
    : lhs(lhs), rhs(rhs), opSym(opSym) {}

AST_BinaryOpNode::AST_BinaryOpNode(const std::string &op1,
                                   const std::string &op2,
                                   const std::string &opSym)
    : op1(op1), op2(op2), opSym(opSym) {}

// ********** Parser class **********

// --- helper functions ---
inline bool Parser::isToken(tokenType token) {
  return tokens[currToken].name == token;
}

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
    } else if (c.name == tokenType::TOKEN_IF) {
      ASTNode *node = ifStatementParser();
      if (node) {
        root->nodes.push_back(node);
      }
    } else {
      currToken++;
    }
  }
  return root; // so this will have a nodes vector with all our nodes stored
  // in it
}

ASTNode *Parser::variableDeclarationParser() {
  currToken++;
  if (!isToken(tokenType::TOKEN_IDENTIFIER)) {
    throw std::runtime_error("Syntax error at token " +
                             tokens[currToken].value +
                             " -> missing identifier.");
  }
  std::string varname = tokens[currToken].value;
  currToken++;

  if (!isToken(tokenType::TOKEN_SEMICOLON)) {
    throw std::runtime_error("Syntax error at token " +
                             tokens[currToken].value +
                             " -> missing semicolon.");
  }
  currToken++;
  return new AST_DeclarationNode(varname);
}

ASTNode *Parser::binaryOpParser() {
  if (!isToken(TOKEN_IDENTIFIER) && !isToken(TOKEN_NUMBER)) {
    throw std::runtime_error(
        "Sytax error : expected idetifier or number after ");
  }

  std::string op1 = tokens[currToken].value;
  currToken++;

  if (isToken(TOKEN_SEMICOLON)) {
    return new AST_BinaryOpNode(op1, "", "");
  }

  if (!isToken(TOKEN_PLUS) && !isToken(TOKEN_MINUS)) {
    throw std::runtime_error("Sytax error : expected a operator after : " +
                             tokens[currToken].value);
  }

  std::string opSym = tokens[currToken].value;
  currToken++;

  if (!isToken(TOKEN_IDENTIFIER) && !isToken(TOKEN_NUMBER)) {
    throw std::runtime_error(
        "Sytax error : expected idetifier or number after " +
        tokens[currToken].value);
  }

  std::string op2 = tokens[currToken].value;

  currToken++;
  return new AST_BinaryOpNode(op1, op2, opSym);
}

ASTNode *Parser::variableAssignmentParser() {
  std::string varname = tokens[currToken].value;
  currToken++;
  if (!isToken(tokenType::TOKEN_ASSIGN)) {
    throw std::runtime_error("not a valid token: expected '='");
  }
  currToken++;

  ASTNode *expression = binaryOpParser();

  if (!isToken(TOKEN_SEMICOLON)) {
    throw std::runtime_error("Syntax Error: expected operator ';'");
  }

  currToken++;
  return new AST_AssignmentNode(varname, expression);
}

ASTNode *Parser::ifConditionParser() {
  if (tokens[currToken].name != tokenType::TOKEN_IDENTIFIER &&
      tokens[currToken].name != tokenType::TOKEN_NUMBER) {
    throw std::runtime_error(
        "Sytax error : expected idetifier or number after : " +
        tokens[currToken].value);
  }

  std::string lhs = tokens[currToken].value;
  currToken++;

  if (tokens[currToken].name != tokenType::TOKEN_EQUAL) {
    throw std::runtime_error("Sytax error : expected '==' after " +
                             tokens[currToken].value);
  }

  std::string opSym = tokens[currToken].value;
  currToken++;

  if (tokens[currToken].name != tokenType::TOKEN_IDENTIFIER &&
      tokens[currToken].name != tokenType::TOKEN_NUMBER) {
    throw std::runtime_error(
        "Sytax error : expected idetifier or number after " +
        tokens[currToken].value);
  }

  std::string rhs = tokens[currToken].value;
  currToken++;

  return new AST_ConditionNode(lhs, rhs, opSym);
}

ASTNode *Parser::ifStatementParser() {
  currToken++;
  if (!isToken(TOKEN_LBRACE)) {
    throw std::runtime_error("Missing '(' after token " +
                             tokens[currToken].value);
  }
  currToken++;

  ASTNode *condition = ifConditionParser();

  if (!isToken(TOKEN_RBRACE)) {
    throw std::runtime_error("Missing ')' after token " +
                             tokens[currToken].value);
  }
  currToken++;

  if (!isToken(TOKEN_LPAREN)) {
    throw std::runtime_error("Missing '{' after token " +
                             tokens[currToken].value);
  }
  currToken++;

  ASTNode *statement = variableAssignmentParser();

  if (!isToken(TOKEN_RPAREN)) {
    throw std::runtime_error("Missing '}' after token " +
                             tokens[currToken].value);
  }

  currToken++;
  return new AST_IfStatementNode(condition, statement);
}
