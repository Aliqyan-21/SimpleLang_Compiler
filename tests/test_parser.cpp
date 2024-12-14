#include "../parser.h"

int main(void) {
  std::string code = "int a; a = 5; if(a == 5) {a = a+1;}";
  Lexer lex(code);

  Parser parser(lex);
  ASTNode *ast = parser.parse();

  auto n = dynamic_cast<AST_DeclarationNode *>(ast->nodes[0]);
  std::cout << n->varname << std::endl;

  auto x = dynamic_cast<AST_AssignmentNode *>(ast->nodes[1]);
  std::cout << x->varname << " = ";
  auto expr1 = dynamic_cast<AST_BinaryOpNode *>(x->expression);
  std::cout << expr1->op1 << " ";
  std::cout << expr1->opSym << " ";
  std::cout << expr1->op2 << " ";
  std::cout << std::endl;

  auto y = dynamic_cast<AST_IfStatementNode *>(ast->nodes[2]);
  auto a = dynamic_cast<AST_ConditionNode *>(y->condition);
  std::cout << a->lhs << " ";
  std::cout << a->opSym << " ";
  std::cout << a->rhs << " ";

  x = dynamic_cast<AST_AssignmentNode *>(y->statement);
  std::cout << x->varname << " = ";
  expr1 = dynamic_cast<AST_BinaryOpNode *>(x->expression);
  std::cout << expr1->op1 << " ";
  std::cout << expr1->opSym << " ";
  std::cout << expr1->op2 << " ";
  std::cout << std::endl;

  // for (auto &node : ast->nodes) {
  //   auto n = dynamic_cast<AST_DeclarationNode *>(node);
  //   std::cout << n->varname << std::endl;
  // }

  return 0;
}
