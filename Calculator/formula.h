#ifndef _FORMULA_2017_
#define _FORMULA_2017_

#include "formulanode.h"
#include "errors.h"
#include <stack>


class Formula {
	FormulaNode *root;
	FormulaNode* _Postfix2Tree(const char *);
	void _Infix2Postfix(const char *, char*);
public:
	Formula(const char *str) : root(nullptr) {
		char * str2 = new char[strlen(str)+1];
		_Infix2Postfix(str, str2);
		root = _Postfix2Tree(str2);
		delete[] str2;
	}
	void print() const { if (root) root->Print(); }
	double calc() const { return root ? root->Calc() : 0; }
	~Formula() { if (root) delete root; root = nullptr; }

};


FormulaNode * Formula::_Postfix2Tree(const char * str) {
	int index = 0;
	std::stack<FormulaNode*> S;
	FormulaNode *x1, *x2, *y;
	char ch;
	try {
		while ((ch = str[index]) != 0) {
			switch (ch) {
			case '+':
				if (S.empty()) throw 0;  x2 = S.top(); S.pop();
				if (S.empty()) throw 0;  x1 = S.top(); S.pop();
				y = new PlusNode(x1, x2);
				break;
			case '-':
				if (S.empty()) throw 0;  x2 = S.top(); S.pop();
				if (S.empty()) throw 0;  x1 = S.top(); S.pop();
				y = new MinusNode(x1, x2); 
				break;
			case '*':
				if (S.empty()) throw 0;  x2 = S.top(); S.pop();
				if (S.empty()) throw 0;  x1 = S.top(); S.pop();
				y = new MultNode(x1, x2);
				break;
			case '/':
				if (S.empty()) throw 0;  x2 = S.top(); S.pop();
				if (S.empty()) throw 0;  x1 = S.top(); S.pop();
				y = new DivNode(x1, x2);
				break;
			case '^':
				if (S.empty()) throw 0;  x2 = S.top(); S.pop();
				if (S.empty()) throw 0;  x1 = S.top(); S.pop();
				y = new PowNode(x1, x2);
				break;
			case '_':
				if (S.empty()) throw 0;  x2 = S.top(); S.pop();
				y = new UMinusNode(x1);
				break;
			default:
				if (ch >= '0' && ch <= '9') y = new NumNode(ch - '0');
				else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
					y = new ParamNode(ch);
				else {
					if (S.empty()) throw 0; x1 = S.top(); S.pop();
					y = new FuncNode(ch, x1);
				}
			}
			S.push(y);
			++index;
		}
		if (S.size() > 1) throw 1;
		return S.top();
	}
	catch (int ) {
		while (!S.empty()) {
			x1 = S.top();
			S.pop();
			delete x1;
		}
		throw PostfixError(str, index);
	}
	return nullptr;
}

const unsigned char ActionsTable[][10] = {
	{0,2,2,2,2,2,2,6,1,2},
	{3,3,3,2,2,2,2,3,1,2},
	{3,3,3,2,2,2,2,3,1,2},
	{3,3,3,3,3,2,2,3,1,2},
	{3,3,3,3,3,2,2,3,1,2},
	{3,3,3,3,3,3,2,3,1,2},
	{5,2,2,2,2,2,2,4,1,2},
	{3,3,3,3,3,3,2,3,1,7}
};

inline int ActionsRowNumber(char ch) {
	switch (ch) {
	case 0: return 0;
	case'+':return 1;
	case'-':return 2;
	case'*':return 3;
	case'/':return 4;
	case'^':return 5;
	case'(':return 6;
	}
	return 7;
}

inline int ActionsColsNumber(char ch) {
	switch (ch) {
	case 0: return 0;
	case'+':return 1;
	case'-':return 2;
	case'*':return 3;
	case'/':return 4;
	case'^':return 5;
	case'(':return 6;
	case')':return 7;
	}
	if (ch >= 'a' && ch <= 'z') return 8;
	if (ch >= 'A' && ch <= 'Z') return 8;
	if (ch >= '0' && ch <= '9') return 8;
	return 9;
}

void Formula::_Infix2Postfix(const char *instr, char* outstr) {
	int i = 0, j = 0;
	int row, col;
	unsigned char action;
	std::stack<char>S;
	do {
		col = ActionsColsNumber(instr[i]);
		if (S.empty()) { 
			row = 0; 
		} else { 
			row = ActionsRowNumber(S.top());
		}
		action = ActionsTable[row][col];
		switch (action){
		case 0: outstr[j] = '\0';  break;
		case 1: outstr[j++] = instr[i++];  break;
		case 2: S.push(instr[i]); ++i; break;
		case 3: outstr[j++] = S.top(); S.pop(); break;
		case 4: S.pop(); ++i; break;
		case 5: throw BracketsError(instr, i); break;
		case 6: throw BracketsError(instr, i); break;
		case 7: throw FunctionBracketsError(instr, i); break;
		}
	} while (action);
}
#endif // _FORMULA_2017_
