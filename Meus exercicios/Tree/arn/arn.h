#pragma once

#include <iostream>

template <typename tC, typename tV>
class ARN;

// Nó da árvore rubro-negra
// tC: tipo da chave
// tV: tipo do valor
template <typename tC, typename tV>
class NoARN {

public:

    NoARN(tC chave, tV valor) : 
        chave(chave), 
        valor(valor), 
        cor(Cor::VERMELHO), 
        esq(nullptr), dir(nullptr) { }

    ~NoARN(){
        delete this->esq;

        delete this->dir;
    }

    // Métodos de acesso
    // retorna uma cópia da chave. 
    // Como uma cópia do objeto é retornada, o objeto original não pode ser alterado.
    // Neste caso, esperamos que a cópia seja um objeto pequeno, como um inteiro,
    // ou que suporte a semântica de movimento (move semantics)
    tC getChave()  { return chave; }

    // retorna uma referência para o valor.
    // O modificador const indica que não é possível alterar o objeto
    // a partir da referência retornada por getValor(). A vantagem é
    // que não é necessário fazer uma cópia do objeto que armazena o valor,
    // uma vez que os valores são possivelmente objetos grandes
    const tV& getValor() { return valor; }

    bool ehVermelho() { 
        if (this == nullptr)
            return false;
        return cor == Cor::VERMELHO; 
    }

private:

    // O nó armazena a cor da aresta que incide sobre ele
    enum class Cor { PRETO, VERMELHO };

    tC chave;
    tV valor;
    Cor cor;
    NoARN<tC, tV> *esq, *dir;

    void inverterCores(){
        this->cor = Cor::VERMELHO;
        this->esq->cor = Cor::PRETO;
        this->dir->cor = Cor::PRETO;
    }

    NoARN<tC, tV>* rotacionarEsquerda(){
        NoARN<tC, tV>* x = this->dir;
        this->dir = x->esq;
        x->esq = this;
        x->cor = this->cor;
        this->cor = Cor::VERMELHO;
        return x;
    }

    NoARN<tC, tV>* rotacionarDireita(){
        NoARN<tC, tV>* x = this->esq;
        this->esq = x->dir;
        x->dir = this;
        x->cor = this->cor;
        this->cor = Cor::VERMELHO;
        return x;
    }

    // A classe ARN é amiga da classe NoARN, ou seja, a classe ARN pode acessar
    // os membros privados da classe NoARN
    friend class ARN<tC, tV>;
};

// Árvore rubro-negra (left-leaning red-black tree)
// tC: tipo da chave
// tV: tipo do valor

template <typename tC, typename tV>
class ARN {

    public:
        ARN() : raiz(nullptr) { }
        ~ARN(){
            delete raiz;
        };

        // retorna o endereço do nó com a chave especificada
        NoARN<tC, tV>* buscar(tC chave){
            return buscarNo(raiz, chave);
        }

        // insere o par (chave, valor) na árvore
        void inserir(tC chave, tV valor){
            this->raiz = inserirNo(raiz, chave, valor);
            raiz->cor = NoARN<tC, tV>::Cor::PRETO;
        }

        // remove o nó com a chave especificada
        void remover(tC chave);

        // imprime a árvore
        void imprimir(){
            imprimirNo(raiz, 0, 'R');
        }
        // retorna a altura da árvore
        int altura();
        // retorna a altura negra da árvore
        int alturaNegra();
        // retorna o número de nós da árvore
        int tamanho();
        // retorna true se a árvore estiver vazia
        bool vazia(){
            return raiz == nullptr;
        }
        
        //retorna o endereço do nó com a menor chave da árvore
        tC minimo();
        //retorna o endereço do nó com a menor chave da subárvore enraizada no nó especificado
        NoARN<tC, tV>* minimo(NoARN<tC, tV>* no);

        //retorna o endereço do nó com a maior chave da árvore
        tC maximo();
        //retorna o endereço do nó com a maior chave da subárvore enraizada no nó especificado
        NoARN<tC, tV>* maximo(NoARN<tC, tV>* no);

        //retorna o endereço do nó com a chave sucessora da chave especificada
        NoARN<tC, tV>* sucessor(tC chave);
        //retorna o endereço do nó com a chave sucessora da chave especificada
        NoARN<tC, tV>* sucessor(NoARN<tC, tV>* no);

        //retorna o endereço do nó com a chave antecessora da chave especificada
        NoARN<tC, tV>* antecessor(tC chave);
        //retorna o endereço do nó com a chave antecessora da chave especificada
        NoARN<tC, tV>* antecessor(NoARN<tC, tV>* no);

        //retorna o custo esperado de uma busca bem sucedida
        int custoBuscaBemSucedida();

        //retorna o custo esperado de uma busca mal sucedida
        int custoBuscaMalsucedida();

        //retorna a percentagem de nós vermelhos na árvore
        float percentualNosVermelhos();
        
private:    
    // armazena o endereço da raiz da árvore
    NoARN<tC, tV> *raiz;

    NoARN<tC, tV>* buscarNo(NoARN<tC, tV> *no, tC chave){
        if (no == nullptr)
            return nullptr;
        if (chave == no->chave)
            return no;
        if (chave < no->chave)
            return buscarNo(no->esq, chave);
        return buscarNo(no->dir, chave);
    }

    NoARN<tC, tV>* inserirNo(NoARN<tC, tV>* no, int chave, int valor){
        if(no == nullptr)
            return new NoARN<tC, tV>(chave, valor);
        if(chave < no->chave)
            no->esq = inserirNo(no->esq, chave, valor);
        else if(chave > no->chave)
            no->dir = inserirNo(no->dir, chave, valor);
        else
            no->valor = valor;
        
        if(no->dir->ehVermelho() && !no->esq->ehVermelho())
            no = no->rotacionarEsquerda();
        if(no->esq->ehVermelho() && no->esq->esq->ehVermelho())
            no = no->rotacionarDireita();
        if(no->esq->ehVermelho() && no->dir->ehVermelho())
            no->inverterCores();

        return no;
    }

    void imprimirNo(NoARN<tC, tV>* no, int nivel, char lado){
        for(int i = 0; i < nivel; i++)
            std::cout << "-->";
        if(no == nullptr){
            std::cout << "(" << lado << ") (VAZIO)"  << std::endl;
        }
        else{
            std::cout << "(" << lado << ") (" 
                  << no->chave << ", " << no->valor << ")" 
                  << "[" 
                  << (no->cor == NoARN<tC, tV>::Cor::VERMELHO ? 'V' : 'P') 
                  << "]" 
                  << std::endl;
            imprimirNo(no->esq, nivel + 1, 'E');
            imprimirNo(no->dir, nivel + 1, 'D');
        }
    }
};

