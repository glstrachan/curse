#include "include/lextrie.hh"

lexNode::lexNode(bool keyword, tokenEnum type) : 
keyword(keyword), type(type), children{0} {}

lexTrie::lexTrie()
{
  lexNode head = lexNode(false, ID);
  lexNodes.push_back(head);

  for(int i = 0; i < keywords.size(); i++)
  {
    reset();
    std::string word = keywords[i];

    for(int j = 0; j < word.size(); j++)
    {
      char letter = word[j];

      if(hasChild(letter)) toChild(letter);
      else
      {
        lexNodes[node].children[letter - 97] = lexNodes.size();
        node = lexNodes.size();

        bool lastLetter = (j == word.size() - 1);
        lexNode newChild = lexNode(lastLetter, lastLetter ? types[i] : ID);
        lexNodes.push_back(newChild);
      }
    }
  }

  reset();
}

void lexTrie::reset()
{
  node = 0;
}

bool lexTrie::hasChild(char child)
{
  child -= 97;
  return (child >= 0 && child <= 26) ? lexNodes[node].children[child] : false;
}

void lexTrie::toChild(char child)
{
  node = lexNodes[node].children[child - 97];
}

bool lexTrie::atKeyword()
{
  return lexNodes[node].keyword;
}

tokenEnum lexTrie::nodeType()
{
  return lexNodes[node].type;
}