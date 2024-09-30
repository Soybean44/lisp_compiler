#include "lexer.h"
#include "parser.h"
#include "compiler.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
	std::string lisp_code, asm_code;
	if (argc <= 1) {
		std::cerr << "Error: No input file specified\n";
		return 1;
	} else {
		std::string file_path = argv[1];
		std::ifstream f(file_path);
		if (!f.is_open()) {
			std::cerr << "Error: source file does not exist or failed to open\n";
			return 1;
		} else {
			std::stringstream s;
			s << f.rdbuf();
			lisp_code = s.str();
		}
	}
	std::cout << "Starting lexing\n";
	Lexer l(lisp_code);
	std::cout << "Starting parsing\n";
	AST_Node ast(AST_ROOT);
	ast.createAST(&l);
	std::cout << "Starting compiling\n";
	interpretAST(&ast);
	return 0;
}

