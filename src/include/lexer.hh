#ifndef LEXER_HH
#define LEXER_HH

#include <string>
#include <stdio.h>
#include <cctype>
#include "lextoken.hh"
#include "lextrie.hh"

struct lexer
{
  std::string source;
  int size;
  char current;
  unsigned int index;

  lexTrie trie = lexTrie();

  lexer(std::string source);

  lexToken nextToken();
  void step();
  
  void eatSpace();
  void eatComment();
  lexToken eatString();
  lexToken eatNumeric();
  lexToken eatID();
  lexToken eatSymbol();
};


#endif