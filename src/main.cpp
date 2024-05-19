#include "lexer.h"
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
	Lexer lexer("(+ 12 21)");
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
		case T_NUMBER:
			break;
		case T_ADD: {
			Token num1, num2;
			if (lexer.peak().type == T_NUMBER) {
				num1 = lexer.get();
			} else {
				std::cerr << "Invalid Argument to addition\n";
				std::cout << lexer.peak().contents << "\n";
				return 1;
			}
			if (lexer.peak().type == T_NUMBER) {
				num2 = lexer.get();
			} else {
				std::cerr << "Invalid Argument to addition\n";
				std::cout << lexer.peak().contents << "\n";
				return 1;
			}
			asm_code << "    mov rax," << num1.contents << "\n";
			asm_code << "    mov rdx," << num2.contents << "\n";
			asm_code << "    add rax,rdx" << "\n";
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
