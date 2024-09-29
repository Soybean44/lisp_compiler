#include "compiler.h"
#include "parser.h"
#include <iostream>

void interpretAST(AST_Node* ast) {
	// If our node is the root node, just run all the s expressions inside it
	if (ast->type == AST_ROOT) {
		for (AST_Node* child : ast->children) {
			interpretAST(child);
		}
	}
	// for an s expression, we evaluate it as (function arg1 arg2 ... argN)
	if (ast->type == AST_SEXP) {
		if (ast->children.empty()) {
			std::cerr << "Error empty sexp\n";
			std::exit(1);
		}
		AST_Node* function = ast->children[0];
		std::vector<AST_Node*> args(ast->children.begin()+1, ast->children.end());
		if (function->contents == "println") {
			for (AST_Node* arg : args) {
				if (arg->type == AST_STRING) {
					std::cout << arg->contents;
					if (args.back() == arg)
						break;
				}
				std::cout << " ";
			}
			std::cout << "\n";
		}
	}
}
