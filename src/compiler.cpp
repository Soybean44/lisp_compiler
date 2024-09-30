#include "compiler.h"
#include "parser.h"
#include <iostream>
#include <string>

void replace_all( // This function is used in print to replace \n with a newline character
    std::string& s,
    std::string const& toReplace,
    std::string const& replaceWith
) {
	std::string buf;
	std::size_t pos = 0;
	std::size_t prevPos;

	// Reserves rough estimate of final size of string.
	buf.reserve(s.size());

	while (true) {
		prevPos = pos;
		pos = s.find(toReplace, pos);
		if (pos == std::string::npos)
			break;
		buf.append(s, prevPos, pos - prevPos);
		buf += replaceWith;
		pos += toReplace.size();
	}

	buf.append(s, prevPos, s.size() - prevPos);
	s.swap(buf);
}

AST_Node* interpretAST(AST_Node* ast) {
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
		if (function->contents == "print") {
			for (AST_Node* arg : args) {
				AST_Node* output;
				if (arg->type == AST_SEXP) {
					output = interpretAST(arg);
				} else {
					output = arg;
				}
				if (output->type == AST_STRING || output->type == AST_INT) {
					std::string str = output->contents;
					replace_all(str, "\\n", "\n");
					std::cout << str;
					if (args.back() == arg)
						break;
				}
				std::cout << " ";
			}
		}
		if (function->contents == "+") {
			int ans = 0;
			for (AST_Node* arg : args) {
				if (arg->type == AST_SEXP) {
					AST_Node* res = interpretAST(arg);
					ans += std::stoi(res->contents);
				} else if (arg->type == AST_INT) {
					ans += std::stoi(arg->contents);
				}
			}
			AST_Node* ans_node = new AST_Node(AST_INT);
			ans_node->setContents(std::to_string(ans));
			return ans_node;
		}
	}
	return ast;
}
