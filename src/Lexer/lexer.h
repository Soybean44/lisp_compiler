#pragma once
#include <array>
#include <string>

enum Token_Type {
	T_OPENPAREN,
	T_CLOSEPAREN,
	T_ADD,
	T_NUMBER,
	T_EOF,
};

typedef struct Token {
	Token_Type type;
	std::string contents;
} Token;

constexpr std::array<char, 4> reserved_characters = {'(',')','+', ' '};

class Lexer {
  public:
	Lexer(std::string input);
	Token next();
  private:
	std::string code;
	std::size_t index = 0;
};
