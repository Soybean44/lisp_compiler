#include "parser.h"
#include "lexer.h"
#include <cstdlib>
#include <iostream>

AST_Node::AST_Node(AST_Node_Type t) {
	type = t;
}

void AST_Node::setContents(std::string s) {
	contents = s;
}

void AST_Node::createAST(Lexer* l) {
	if (type == AST_ROOT) {
		setContents("Root");
	} else if (type == AST_ATOM) {
		std::cerr << "Cant call createAST on AST_Atom\n";
		std::exit(EXIT_FAILURE);
	}
	while (true) {
		Token tok = l->get();
		if (tok.type == T_OPENPAREN) {
			AST_Node* sexp = new AST_Node(AST_SEXP);
			sexp->setContents("s-expression");
			sexp->createAST(l);
			children.push_back(sexp);
		} else if (tok.type == T_ATOM) {
			AST_Node* atom = new AST_Node(AST_ATOM);
			atom->setContents(tok.contents);
			children.push_back(atom);
		} else if (tok.type == T_SPACE) {
			continue;
		} else if (tok.type == T_CLOSEPAREN) {
			break;
		} else if (tok.type == T_EOF) {
			if (type == AST_ROOT)
				break;
			else {
				std::cerr << "Missing a closing parenthesis\n";
				std::exit(EXIT_FAILURE);
			}
		}
	}
}
AST_Node::~AST_Node() {
	for (AST_Node* child : children) {
		delete child;
	}
}
void AST_Node::printAST() {
	if (type == AST_ATOM) {
		std::cout << contents;
		return;
	}
	if (type != AST_ROOT) {
		std::cout << "(";
	}
	for (AST_Node* child : children) {
		child->printAST();
		if (child != children.back()) {
			std::cout << " ";
		}
		if (type == AST_ROOT) {
			std::cout << "\n";
		}
	}
	if (type != AST_ROOT) {
		std::cout << ")";
	}
}
