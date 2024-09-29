#pragma once

#include "lexer.h"
#include <string>
#include <vector>

enum AST_Node_Type {
	AST_ROOT,
	AST_ATOM,
	AST_SEXP,
	AST_LIST,
	AST_STRING,
};

class AST_Node {
  public:
	AST_Node_Type type;
	std::string contents;
	std::vector<AST_Node*> children;
	AST_Node(AST_Node_Type t);
	void setContents(std::string s);
	void createAST(Lexer* l);
	void printAST();
	void printASTDebug();

	~AST_Node();
};
