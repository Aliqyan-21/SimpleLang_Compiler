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
  std::string code = "int a; int b; int c; a = 10; b = 20; c = a + b; if (c == "
                     "30) { c = c + 1; }";
  Lexer lex(code);

  Parser parser(lex);
  ASTNode *ast = parser.parse();

  return 0;
}
