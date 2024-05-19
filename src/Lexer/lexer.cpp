#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>

Lexer::Lexer(std::string input) {
	// Remove all newline characters
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	code = input;
}

std::tuple<Token, std::size_t> Lexer::next() {
	std::size_t idx = 0;
	std::optional<Token> token;
	std::string contents;

	do {
		// Check if we are at the end of a file, creating an eof token if we are
		if (idx >= code.length()) {
			token = {.type=T_EOF,.contents="EOF"};
			break;
		}
		char current_char = code[index+idx]; // Get current character

		if (!current_char) {  // If the character is null assume it is eof (null terminated strings)
			token = {.type=T_EOF,.contents="EOF"};
			break;
		}

		// Check if character is reserved
		auto it = std::find(reserved_characters.begin(), reserved_characters.end(), current_char);

		if (it != reserved_characters.end()) {  // Character is reserved
			// If we set the value that means its the end of the current token
			if (token.has_value()) {
				token.value().contents = contents;
				break;
			} else {
				idx++;
				switch (current_char) {
				case '(':
					token = {.type = T_OPENPAREN, .contents="("};
					break;
				case ')':
					token = {.type = T_CLOSEPAREN, .contents=")"};
					break;
				case '+':
					token = {.type = T_ADD, .contents="+"};
					break;
				case ' ': // if we are starting on a space, it means nothign so move to the next token
					continue;
				default:
					std::cerr << "Invalid Character\n";
					break;
				}
			}
			break;
		} else if (!token.has_value()) {  // Is this the start of a new token
			if (std::isdigit(current_char)) {  // Character is a number, then its a number literal
				token = {.type = T_NUMBER};
				contents.push_back(current_char);
			} else {
				std::cerr << "Alpha characters not implemented yet\n";
				std::cout << (int)current_char << "\n";
				break;
			}
		} else { // Started a token but havent ended it so push the current character to contents
			contents.push_back(current_char);
		}
		idx++;
	} while (true);
	return std::make_tuple(token.value(), idx);
}

Token Lexer::peak() {
	return std::get<0>(next());
}
Token Lexer::get() {
	auto tkn = next();
	index += std::get<1>(tkn);
	return std::get<0>(tkn);
}
