#include "../lexer/include/lexer.hh"
#include "../lexer/include/lextoken.hh"
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  std::string input = "int b = 0\n\nfor(int a [1..10])\n\n\tb++\n\nout(b)";
  lexer lex = lexer(input);

  std::cout << input << std::endl << std::endl;

  lexToken tok = lexToken(ID, "");
  while(tok.type != END)
  {
    tok = lex.nextToken();
    std::cout << tok.type << ' ' << tok.data << std::endl;
  }

  return 0;
}