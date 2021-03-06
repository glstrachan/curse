#ifndef LEX_TOKEN_HH
#define LEX_TOKEN_HH

#include <string>

struct lexToken;

enum tokenEnum : int;

struct lexToken
{
	tokenEnum type;
	std::string data;

	lexToken(tokenEnum type, std::string data);
};

enum tokenEnum : int
{
	/* Dynamic Types */
	ID,
	DATA_INT,
	DATA_DOUBLE,
	DATA_STRING,

	/* Keywords */
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
	WHEN,

	/* Operators */
	PLUS,
	MINUS,
	STAR,
	SLASH,
	PERCENT,

	PLUS_EQ,
	MINUS_EQ,
	STAR_EQ,
	SLASH_EQ,
	PERCENT_EQ,

	PLUS_PLUS,
	MINUS_MINUS,

	ASSIGN,
	EQ,
	GT,
	LT,
	GT_EQ,
	LT_EQ,
	NOT_EQ,
	AND,
	OR,
	BANG,
	BANG_EQ,

	POINTER_ASSIGN,
	POINTER_DEREF,
	POINTER_LOCATION,

	COMMA,
	DOT,
	DOT_DOT,

	/* Pairs */
	PAREN_OPEN,
	PAREN_CLOSE,
	SQUARE_OPEN,
	SQUARE_CLOSE,
	ARROW_OPEN,
	ARROW_CLOSE,
	OPEN,
	CLOSE,

	/* Random character */
	END
};

#endif