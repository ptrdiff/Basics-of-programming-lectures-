#ifndef  _FORMULANODE_2017_
#define _FORMULANODE_2017_

#include <cmath>
#include <iostream>
#include "errors.h"
#include "myfunctions.h"

class FormulaNode {
public:
	virtual double Calc() const = 0;
	virtual void Print() const = 0;
	virtual ~FormulaNode() {}

};

class NumNode : public FormulaNode {
	const double num;
public:
	NumNode(double x) : num(x) {}
	double Calc() const { return num; }
	void Print()const {
		if (num < 0) std::cout << '(' << num << ')';
		else std::cout << num;
	}
};

class BinNode : public FormulaNode {
protected:
	FormulaNode *left, *right;
public:
	BinNode(FormulaNode *L, FormulaNode *R) : left(L), right(R) {}
	~BinNode() {
		if (left) delete left;
		if (right) delete right;
		left = right = nullptr;
	}
};

class PlusNode : public BinNode {
public:
	PlusNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}
	double Calc() const { return left->Calc() + right->Calc(); }
	void Print() const { left->Print(); std::cout << '+'; right->Print(); }
};

class MinusNode : public BinNode {
public:
	MinusNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}
	double Calc() const { return left->Calc() - right->Calc(); }
	void Print() const { left->Print(); std::cout << "-("; right->Print(); std::cout << ")"; }
};

class MultNode : public BinNode {
public:
	MultNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}
	double Calc() const { return left->Calc() * right->Calc(); }
	void Print() const { std::cout << "("; left->Print(); std::cout << ")*("; right->Print(); std::cout << ")"; }
};

class DivNode : public BinNode {
public:
	DivNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}
	double Calc() const {
		double denum = right->Calc();
		if (denum == 0) throw DivideByZero();
		return left->Calc() / denum;
	}
	void Print() const { std::cout << "("; left->Print(); std::cout << ")/("; right->Print(); std::cout << ")"; }
};

class PowNode : public BinNode {
public:
	PowNode(FormulaNode *L, FormulaNode *R) : BinNode(L, R) {}
	double Calc() const {return std::pow(left->Calc(), right->Calc()) ;}
	void Print() const { std::cout << "("; left->Print(); std::cout << ")^("; right->Print(); std::cout << ")"; }
};

class ParamNode : public FormulaNode {
	const char ch;
public:
	ParamNode(char s) : ch(s) {}
	void Print() const { std::cout << ch; }
	double Calc() const {
		std::cout << std::endl << ch << " = ";
		double x; std::cin >> x;
		std::cin.ignore();
		return x;
	}
};

class UnarNode : public FormulaNode {
protected:
	FormulaNode *next;
public:
	UnarNode(FormulaNode *n) : next(n) {}
	~UnarNode() { delete next; next = nullptr; }
};

class UMinusNode : public UnarNode {
public:
	UMinusNode(FormulaNode *n) : UnarNode(n) {}
	double Calc() const { return -next->Calc(); }
	void Print() const { std::cout << "-("; next->Print(); std::cout << ")"; }
};

class FuncNode :public UnarNode {
	int fnum;
public:
	FuncNode(const char *s, FormulaNode *n) : UnarNode(n) {	
		fnum = FunNumberByName(s);
	}
	FuncNode(char s, FormulaNode *n) : UnarNode(n) {
		fnum = FunNumberByShortName(s);
	}
	double Calc() const {
		return (FTable[fnum].fun)(next->Calc());
	}
	void Print() const {
		std::cout << FTable[fnum].Name;
		std::cout << "("; next->Print(); std::cout << ")";
	}
};

#endif // ! _FORMULANODE_2017_
