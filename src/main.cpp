#include "lexer.h"
#include "parser.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
int main() {
	std::cout << "Starting parsing\n";
	Lexer l("(+ 9 (+ 5 5)) (+ 9 10)");
	AST_Node ast(AST_ROOT);
	ast.createAST(&l);
	ast.printAST();
	return 0;
}

int old_main() {
	Lexer lexer("(+ 9 10)");
	std::stringstream asm_code;
	asm_code << "format ELF64 executable 3\n";
	asm_code << "segment readable executable\n";
	asm_code << "entry $\n";
	Token tok = lexer.peak();
	while (tok.type != T_EOF) {
		tok = lexer.get();
		switch (tok.type) {
		case T_OPENPAREN:
			break;
		case T_CLOSEPAREN:
			break;
		case T_ATOM: {
			if (tok.contents == "+") {
				Token num1, num2;
				Token curr_token = lexer.peak();
				// Check if current token is a space and ignore it
				if (curr_token.type == T_SPACE) {
					lexer.get();
				} else {
					std::cerr << "Invalid Token or Not enough arguments\n";
					std::cout << curr_token.contents << "\n";
					return 1;
				}
				curr_token = lexer.peak();
				if (curr_token.type == T_ATOM && std::all_of(curr_token.contents.begin(), curr_token.contents.end(), [](char c) { // check if the atom is a number
				return std::isdigit(c);
				})) {
					num1 = lexer.get();
				} else {
					std::cerr << "Invalid Argument to addition\n";
					std::cout << curr_token.contents << "\n";
					return 1;
				}
				curr_token = lexer.peak();
				// Check if current token is a space and ignore it
				if (curr_token.type == T_SPACE) {
					lexer.get();
				} else {
					std::cerr << "Invalid Token or Not enough arguments\n";
					std::cout << curr_token.contents << "\n";
					return 1;
				}
				curr_token = lexer.peak();
				if (curr_token.type == T_ATOM && std::all_of(curr_token.contents.begin(), curr_token.contents.end(), [](char c) { // check if the atom is a number
				return std::isdigit(c);
				})) {
					num2 = lexer.get();
				} else {
					std::cerr << "Invalid Argument to addition\n";
					std::cout << lexer.peak().contents << "\n";
					return 1;
				}
				asm_code << "    mov rax," << num1.contents << "\n";
				asm_code << "    mov rdx," << num2.contents << "\n";
				asm_code << "    add rax,rdx" << "\n";
			} else {
				std::cerr << "Invalid Token\n";
				std::cout << tok.contents << "\n";
				return 1;
			}
		}
		break;
		default:
			break;
		}
	}
	asm_code << "    mov rdi,rax\n";
	asm_code << "    mov rax,60\n";
	asm_code << "    syscall\n";
	std::ofstream f("lisp_build/test.asm");
	f << asm_code.str();
	return 0;
}
