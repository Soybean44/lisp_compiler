#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <optional>
#include <string>

Lexer::Lexer(std::string input) {
	// Remove all newline characters
	input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
	code = input;
}

Token Lexer::next() {
	std::optional<Token> token;
	std::string contents;

	do {
		// Check if we are at the end of a file, creating an eof token if we are
		if (index >= code.length()) {
			token = {.type=T_EOF,.contents="EOF"};
			break;
		};
		char current_char = code[index]; // Get current character

		// Check if character is reserved
		auto it = std::find(reserved_characters.begin(), reserved_characters.end(), current_char);

		if (it != reserved_characters.end()) {  // Character is reserved
			// If we set the value that means its the end of the current token
			if (token.has_value()) {
				token.value().contents = contents;
				break;
			} else {
				index++;
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
				std::cerr << "Invalid Character\n";
				break;
			}
		} else { // Started a token but havent ended it so push the current character to contents
			contents.push_back(current_char);
		}
		index++;
	} while (true);
	return token.value();
}

