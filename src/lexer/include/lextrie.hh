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
    "id",
    "link",

    "model",
    "int",
    "long",
    "char",
    "bit",
    "enum",
    "double",
    "float",
    "string",
    "void",
    "auto",

    "false",
    "true",

    "if",
    "else",
    "continue",
    "break",
    "return",
    "split",
    "when"
  };

  const std::vector<tokenEnum> types = 
  {
    ID,
    LINK,

    MODEL,
    INT,
    LONG,
    CHAR,
    BIT,
    ENUM,
    DOUBLE,
    FLOAT,
    STRING,
    VOID,
    AUTO,

    FALSE,
    TRUE,

    IF,
    ELSE,
    CONTINUE,
    BREAK,
    RETURN,
    SPLIT,
    WHEN
  };
};

#endif

