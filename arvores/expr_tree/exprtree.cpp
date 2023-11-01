#include "exprtree.h"
#include <stack>
#include <sstream> //istringstream
#include <string>
#include <cctype> //isdigit

ExprTree::ExprTree(char *posfixa){
	std::stack<ExprNode*> pilha;
	ExprNode *tmp, *a, *b;
	std::istringstream iss(posfixa);
	std::string token;

	while(iss >> token){
		if(std::isdigit(token[0])){
			tmp = new ExprNodeConst(std::stod(token));
		}else{
			a = pilha.top(); pilha.pop();
			b = pilha.top(); pilha.pop();
			tmp = new ExprNodeOp(token[0], b, a);
		}
		pilha.push(tmp);
	}
	raiz = pilha.top();
}

double ExprNodeConst::avaliar(){
	return this->valor;
}


double ExprNodeOp::avaliar(){
	double esq = this->esq->avaliar();
	double dir = this->dir->avaliar();

	switch (this->op)
	{
	case '+':
		return esq + dir; break;
	case '-':
		return esq - dir; break;
	case '*':
		return esq * dir; break;
	case '/':
		return esq / dir; break;
	}

}
