class ExprNode{
	public:
	virtual double avaliar() = 0;
	~ExprNode();

	protected:
	ExprNode* esq = nullptr;
	ExprNode* dir = nullptr;
};

class ExprNodeConst : public ExprNode{

	public:
	ExprNodeConst(double valor){
		this->valor = valor;
	}

	double avaliar() override;

	private:
	double valor;


};

class ExprNodeOp : public ExprNode {
    public:
    explicit ExprNodeOp(char op, ExprNode* esq, ExprNode* dir){
		this->op = op;
		this->esq = esq;
		this->dir = dir;
	}
        
    double avaliar() override;

    private:
    char op;
};

class ExprTree{
	public:
	explicit ExprTree(char* posfixa);
	~ExprTree();
	double avaliar(){
		return this->raiz->avaliar();
	}

	private:
	ExprNode* raiz;
};