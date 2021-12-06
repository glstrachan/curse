#include "include/lexer.hh"

lexer::lexer(std::string source) : 
source(source), size(source.size()), current(source[0]), index(0) {}

lexToken lexer::nextToken()
{
	while(current != '\0')
	{
    if(current == ' ') eatSpace();
    if(current == '|') eatComment();
    if(current == '"') return eatString();
    if(std::isdigit(current) || current == '.') return eatNumeric();
		if(std::isalpha(current)) return eatID();
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
    if(current == '\\') step();

    data += current;
    step();
  }
  step();

  return lexToken(STRING, data);
}

lexToken lexer::eatNumeric()
{
  std::string data;
  tokenEnum type = INT;

  while(std::isdigit(current) || current == '.')
  {
    if(current == '.') type = DOUBLE;
    data += current;
    step();
  }

  return lexToken(type, data);
}

void lexer::eatComment()
{
  step();
  while(current != '|') step();
  step();

  if(current == ' ') eatSpace();
}

void lexer::eatSpace()
{
  while(current == ' ') step();
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
    else if(current == '>') { type = ARROW_R; data += current; }
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
    if(current == '-') { type = ARROW_L; data += current; }
    else type = LT;

    break; case '!':
    if(current == '=') { type = BANG_EQ; data += current; }
    else type = BANG;

    break; case '(':
    type = PAREN_L;

    break; case ')':
    type = PAREN_R;

    break; case '[':
    type = SQUARE_L;

    break; case ']':
    type = SQUARE_R;

    break; case ',':
    type = COMMA;

    break; case '.':
    if(current == '.') { type = DOT_DOT; data += current; }
    else type = DOT;

    break; case '\n':
    type = NEWLINE;

    break; case '\t':
    type = TAB;

    break; default:
    return nextToken();
  }

  if(data.size() == 2) step();
  return lexToken(type, data);
}