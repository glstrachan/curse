#include "include/lexer.hh"

lexer::lexer(std::string source) : 
source(source), size(source.size()), current(source[0]), 
index(0), level(0), lastLevel(0) {}

lexToken lexer::nextToken()
{
	while(current != '\0')
	{
    if(current == ' ') eatSpace();
    if(current == '|') eatComment();
    if(current == '"') return eatString();
    if(std::isdigit(current) || current == '.') return eatNumeric();
		if(std::isalpha(current)) return eatID();
    if(current == '\n') return eatLine();
    return eatSymbol();
	}

	return lexToken(END, "");
}

void lexer::step()
{
	if(index < size && current != '\0')
	{
		index++;
		current = source[index];
	}
}

lexToken lexer::eatString()
{
  std::string data;

  step();
  while(current != '\"')
  {
    if(current == '\n' || current == '\0') break;
      //Throw incomplete token error expected terminating "
    if(current == '\\') step();

    data += current;
    step();
  }
  step();

  return lexToken(DATA_STRING, data);
}

lexToken lexer::eatNumeric()
{
  std::string data;
  tokenEnum type = DATA_INT;

  while(std::isdigit(current) || current == '.')
  {
    if(current == '.') type = DATA_DOUBLE;
    data += current;
    step();
  }

  return lexToken(type, data);
}

void lexer::eatComment()
{
  step();
  while(current != '|') 
  {
    if(current == '\0') break;
    step();
  }
  step();

  if(current == ' ') eatSpace();
}

void lexer::eatSpace()
{
  while(current == ' ') step();
  if(current == '|') eatComment();
}

lexToken lexer::eatID()
{
  std::string data;
  tokenEnum type;
  
  trie.reset();
  bool matching = true;
  
  while(std::isalpha(current))
  {
    if(matching)
    {
      type = ID;

      if(trie.hasChild(current))
      {
        trie.toChild(current);
        if(trie.atKeyword() == true) type = trie.nodeType();
      }
      else matching = false;
    }

    data += current;
    step();
  }

  return lexToken(type, data);
}

lexToken lexer::eatSymbol()
{
  tokenEnum type;
  std::string data; data += current;
  step();

  switch(data[0])
  {
    case '+':
    if(current == '=') { type = PLUS_EQ; data += current; }
    else if(current == '+') { type = PLUS_PLUS; data += current; }
    else type = PLUS;

    break; case '-':
    if(current == '=') { type = MINUS_EQ; data += current; }
    else if(current == '-') { type = MINUS_MINUS; data += current; }
    else if(current == '>') { type = ARROW_OPEN; data += current; }
    else type = MINUS;
  
    break; case '*':
    if(current == '=') { type = STAR_EQ; data += current; }
    else type = STAR;

    break; case '\\':
    if(current == '=') { type = SLASH_EQ; data += current; }
    else type = SLASH;

    break; case '%':
    if(current == '=') { type = PERCENT_EQ; data += current; }
    else type = PERCENT;

    break; case ':':
    type = ASSIGN;

    break; case '=':
    type = EQ;

    break; case '>':
    if(current == '=') { type = GT_EQ; data += current; }
    else type = GT;

    break; case '<':
    if(current == '=') { type = LT_EQ; data += current; }
    if(current == '-') { type = ARROW_CLOSE; data += current; }
    else type = LT;

    break; case '!':
    if(current == '=') { type = BANG_EQ; data += current; }
    else type = BANG;

    break; case '(':
    type = PAREN_CLOSE;

    break; case ')':
    type = PAREN_OPEN;

    break; case '[':
    type = SQUARE_CLOSE;

    break; case ']':
    type = SQUARE_OPEN;

    break; case ',':
    type = COMMA;

    break; case '.':
    if(current == '.') { type = DOT_DOT; data += current; }
    else type = DOT;

    break; default:
    return nextToken();
    /* Throw unexpected token error */
  }

  if(data.size() == 2) step();
  return lexToken(type, data);
}

lexToken lexer::eatLine()
{
  tokenEnum type;
  step();
  
  int newLevel = 0;
  while(current == '\t')
  {
    newLevel++;
    step();
  }

  if(current == '\n') return eatLine();

  lastLevel = level;
  level = newLevel;

  if(lastLevel < level) return lexToken(CLOSE, "[OPEN]");
  if(lastLevel > level) return lexToken(CLOSE, "[CLOSE]");
  return nextToken();
}