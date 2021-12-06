#include "include/curse.hh"

void compile(std::string source)
{
  lexer lex = lexer(source);
  
  lexToken token = lexToken(ID, "");

  std::cout << "source: " << source << "\n";

  while(token.type != END)
  {
    token = lex.nextToken();

    printf("%2d %s\n", token.type, token.data.c_str());
  }
}

int main()
{
  std::string source = "data int datat ints sint";
  compile(source);
  
  return 0;
}
