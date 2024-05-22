#pragma once
#include <array>
#include <string>

enum Token_Type {
	T_OPENPAREN,
	T_CLOSEPAREN,
	T_ATOM,
	T_EOF,
	T_DOUBLEQUOTE
};

typedef struct Token {
	Token_Type type;
	std::string contents;
} Token;

constexpr std::array<char, 5> reserved_characters = {'(',')','+', ' ', '\"'};

class Lexer {
  public:
	Lexer(std::string input);
	std::tuple<Token, std::size_t> next();
	Token peak();
	Token get();
  private:
	std::string code;
	std::size_t index = 0;
};
