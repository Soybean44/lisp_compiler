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
		setContents("Root"); // Debug info
	} else if (type == AST_ATOM) { // This function shouldnt be run on an atom/leaf
		std::cerr << "Cant call createAST on AST_Atom\n";
		std::exit(EXIT_FAILURE);
	}
	while (true) {
		Token tok = l->get();
    // Start a new s-expression and append it to the current node's children
    // Then recursively call this function
		if (tok.type == T_OPENPAREN) { 
			AST_Node* sexp = new AST_Node(AST_SEXP);
			sexp->setContents("s-expression");
			sexp->createAST(l);
			children.push_back(sexp);
		} else if (tok.type == T_ATOM) { // Append an atom to the current nodes children and stop (BASE CASE)
			AST_Node* atom = new AST_Node(AST_ATOM);
			atom->setContents(tok.contents);
			children.push_back(atom);
		} else if (tok.type == T_SPACE) { // ignore spaces
			continue;
    // The following are also BASE CASES, but ends the iteration not the recurrsion
		} else if (tok.type == T_CLOSEPAREN) { // Stops the current sexpression
			if (type == AST_ROOT) { // cant close on root
				std::cerr << "Missing an opening parenthesis\n";
				std::exit(EXIT_FAILURE);
			}
			break;
		} else if (tok.type == T_EOF) {
			if (type == AST_ROOT)
				break;
			else { // if we hit the end of the file inside an s-expression, call an error
				std::cerr << "Missing a closing parenthesis\n";
				std::exit(EXIT_FAILURE);
			}
		}
	}
}
AST_Node::~AST_Node() { // Destructor, deleting children just calls this so its recursive
	for (AST_Node* child : children) {
		delete child;
	}
}
void AST_Node::printAST() {
	if (type == AST_ATOM) {
		std::cout << contents;
		return; // return early on an atom (BASE CASE)
	}
	if (type != AST_ROOT) {
		std::cout << "(";
	}
	for (AST_Node* child : children) {
		child->printAST();
		if (child != children.back()) { // print if its not the last child
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
