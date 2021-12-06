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
	ID,
	LINK,

	DATA,
	INT,
	LONG,
	CHAR,
	BIT,
	ENUM,
	DOUBLE,
	FLOAT,
	STRING,
	VOID,

	FALSE,
	TRUE,

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

	PAREN_L,
	PAREN_R,
	SQUARE_L,
	SQUARE_R,
	ARROW_R,
	ARROW_L,

	COMMA,
	DOT,
	DOT_DOT,

	IF,
	ELSE,
	CONTINUE,
	BREAK,
	RETURN,
	SPLIT,
	WHEN,

	NEWLINE,
	TAB,
	END
};

#endif