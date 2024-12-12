#include "../lexer.h"

int main(void) {
  std::string code = "int a; int b; int c; a = 10; b = 20; c = a + b; if (c == "
                     "30) { c = c + 1; }";

  Lexer lex(code);
  std::vector<Token> tokens = lex.tokenize();

  for (auto &t : tokens) {
    std::cout << t.name << " : " << t.value << std::endl;
  }

  return 0;
}
