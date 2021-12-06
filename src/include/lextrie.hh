#ifndef LEXTRIE_HH
#define LEXTRIE_HH

#include "lextoken.hh"
#include <vector>

struct lexNode
{
  bool keyword;
  tokenEnum type;
  short children[26];

  lexNode(bool keyword, tokenEnum type);
};

struct lexTrie
{
  std::vector<lexNode> lexNodes;
  int node;

  lexTrie();
  void reset();
  bool hasChild(char child);
  void toChild(char child);
  bool atKeyword();
  tokenEnum nodeType();

  const std::vector<std::string> keywords = 
  {
    "int",
    "data"
  };

  const std::vector<tokenEnum> types = 
  {
    INT,
    DATA
  };
};

#endif

