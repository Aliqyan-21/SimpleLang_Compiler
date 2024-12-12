#include "../lexer.h"

int main(void) {
  // empty string
  std::string code1 = "";

  // invalid token
  std::string code2 = "int i; i = @";

  // valid code
  std::string code3 =
      "int a; int b; int c; a = 10; b = 20; c = a + b; if (c == "
      "30) { c = c + 1; }";

  std::cout << "tokens 1: " << std::endl;
  Lexer lex1(code1);
  std::vector<Token> tokens1 = lex1.tokenize();
  for (auto &t : tokens1) {
    std::cout << t.name << " : " << t.value << std::endl;
  }

  std::cout << std::endl;
  std::cout << "tokens 2: " << std::endl;
  Lexer lex2(code2);
  std::vector<Token> tokens2 = lex2.tokenize();
  for (auto &t : tokens2) {
    std::cout << t.name << " : " << t.value << std::endl;
  }

  std::cout << std::endl;
  Lexer lex3(code3);
  std::vector<Token> tokens3 = lex3.tokenize();
  std::cout << "tokens 3: " << std::endl;
  for (auto &t : tokens3) {
    std::cout << t.name << " : " << t.value << std::endl;
  }

  return 0;
}
