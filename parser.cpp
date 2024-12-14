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

AST_IfStatementNode::AST_IfStatementNode(ASTNode *condition, ASTNode *statement)
    : condition(condition), statement(statement) {}

ParseCondtionNode::ParseCondtionNode(const std::string &lhs,
                                     const std::string &rhs,
                                     const std::string &opSym)
    : lhs(lhs), rhs(rhs), opSym(opSym) {}

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

// todo: implement compiler like error handling instead of interpreter - later
ASTNode *Parser::variableDeclarationParser() {
  currToken++;
  if (!isToken(tokenType::TOKEN_IDENTIFIER)) {
    std::cerr << "Syntax error at token " << tokens[currToken].value
              << " -> missing identifier." << std::endl;
    exit(1);
  }
  std::string varname = tokens[currToken].value;
  currToken++;

  if (!isToken(tokenType::TOKEN_SEMICOLON)) {
    std::cerr << "Syntax error at token " << tokens[currToken].value
              << " -> missing semicolon." << std::endl;
    exit(1);
  }
  currToken++;
  return new AST_DeclarationNode(varname);
}

ASTNode *Parser::variableAssignmentParser() {
  std::string varname = tokens[currToken].value;

  currToken++;
  if (!isToken(tokenType::TOKEN_ASSIGN)) {
    std::cerr << "not a valid token: missing '='" << std::endl;
    exit(1);
  }
  currToken++;

  if (!isToken(TOKEN_IDENTIFIER) && !isToken(TOKEN_NUMBER)) {
    std::cerr << "syntax error: expected variable name or a literal after '='"
              << std::endl;
    exit(1);
  }
  std::string op1 = tokens[currToken].value;
  currToken++;

  if (isToken(TOKEN_SEMICOLON)) {
    currToken++;
    return new AST_AssignmentNode(varname, op1);
  } else if (isToken(TOKEN_PLUS) || isToken(TOKEN_MINUS)) {
    std::string opSym = tokens[currToken].value;
    currToken++;
    if (!isToken(TOKEN_IDENTIFIER) && !isToken(TOKEN_NUMBER)) {
      std::cerr
          << "Syntax Error: expected variable name or literal after operator"
          << std::endl;
      exit(1);
    }
    std::string op2 = tokens[currToken].value;
    currToken++;

    if (!isToken(TOKEN_SEMICOLON)) {
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

ASTNode *Parser::parseCondition() {
  if (!isToken(TOKEN_IDENTIFIER) && !isToken(TOKEN_NUMBER)) {
    std::cerr << "Sytax error : expected idetifier or number after "
              << tokens[currToken].value << std::endl;
    exit(1);
  }

  std::string lhs = tokens[currToken].value;
  currToken++;

  if (!isToken(TOKEN_EQUAL)) {
    std::cerr << "Sytax error : expected '==' after " << tokens[currToken].value
              << std::endl;
    exit(1);
  }

  std::string opSym = tokens[currToken].value;
  currToken++;

  if (!isToken(TOKEN_IDENTIFIER) && !isToken(TOKEN_NUMBER)) {
    std::cerr << "Sytax error : expected idetifier or number after "
              << tokens[currToken].value << std::endl;
    exit(1);
  }

  std::string rhs = tokens[currToken].value;
  currToken++;

  return new ParseCondtionNode(lhs, rhs, opSym);
}

ASTNode *Parser::ifStatementParser() {
  currToken++;
  if (!isToken(TOKEN_LBRACE)) {
    std::cerr << "Missing '(' after token " << tokens[currToken].value
              << std::endl;
    exit(1);
  }
  currToken++;

  ASTNode *condition = parseCondition();

  if (!isToken(TOKEN_RBRACE)) {
    std::cerr << "Missing ')' after token " << tokens[currToken].value
              << std::endl;
    exit(1);
  }
  currToken++;

  if (!isToken(TOKEN_LPAREN)) {
    std::cerr << "Missing '{' after token " << tokens[currToken].value
              << std::endl;
    exit(1);
  }
  currToken++;

  ASTNode *statement = variableAssignmentParser();

  if (!isToken(TOKEN_RPAREN)) {
    std::cerr << "Missing '}' after token " << tokens[currToken].value
              << std::endl;
    exit(1);
  }

  return new AST_IfStatementNode(condition, statement);
}
