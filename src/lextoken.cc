#include "include/lextoken.hh"

lexToken::lexToken(tokenEnum type, std::string data) :
type(type), data(data) {}