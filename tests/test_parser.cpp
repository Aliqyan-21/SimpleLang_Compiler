#include "../parser.h"
#include <unordered_map>

std::unordered_map<tokenType, std::string> m{
    {TOKEN_INT, "TOKEN_INT"},
    {TOKEN_IDENTIFIER, "TOKEN_IDENTIFIER"},
    {TOKEN_NUMBER, "TOKEN_NUMBER"},
    {TOKEN_ASSIGN, "TOKEN_ASSIGN"},
    {TOKEN_PLUS, "TOKEN_PLUS"},
    {TOKEN_MINUS, "TOKEN_MINUS"},
    {TOKEN_IF, "TOKEN_IF"},
    {TOKEN_EQUAL, "TOKEN_EQUAL"},
    {TOKEN_LBRACE, "TOKEN_LBRACE"},
    {TOKEN_RBRACE, "TOKEN_RBRACE"},
    {TOKEN_LPAREN, "TOKEN_LPAREN"},
    {TOKEN_RPAREN, "TOKEN_RPAREN"},
    {TOKEN_SEMICOLON, "TOKEN_SEMICOLON"},
    {TOKEN_UNKNOWN, "TOKEN_UNKNOWN"},
    {TOKEN_EOF, "TOKEN_EOF"},
};

int main(void) {
  std::string code = "int a; int b; a = b + a;";
  Lexer lex(code);

  Parser parser(lex);
  ASTNode *ast = parser.parse();

  std::cout << ast->nodes.size() << std::endl;

  auto n = dynamic_cast<AST_DeclarationNode *>(ast->nodes[0]);
  std::cout << n->varname << std::endl;

  n = dynamic_cast<AST_DeclarationNode *>(ast->nodes[1]);
  std::cout << n->varname << std::endl;

  auto x = dynamic_cast<AST_AssignmentNode *>(ast->nodes[2]);
  std::cout << x->varname << " = ";
  std::cout << x->op1 << " ";
  std::cout << x->opSym << " ";
  std::cout << x->op2 << " ";
  std::cout << std::endl;

  // for (auto &node : ast->nodes) {
  //   auto n = dynamic_cast<AST_DeclarationNode *>(node);
  //   std::cout << n->varname << std::endl;
  // }

  return 0;
}
