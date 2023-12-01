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

    ~NoARN() = default;

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

    bool ehVermelho(){
        if(this == nullptr)
            return false;

        return this->cor == Cor::VERMELHO;
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

    void inverterCores(){
        this->cor = Cor::VERMELHO;
        this->esq = Cor::PRETO;
        this->dir = Cor::PRETO;
    }

private:

    // O nó armazena a cor da aresta que incide sobre ele
    enum class Cor { PRETO, VERMELHO };

    tC chave;
    tV valor;
    Cor cor;
    NoARN<tC, tV> *esq, *dir;

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
        ~ARN() = default;

        // retorna o endereço do nó com a chave especificada
        NoARN<tC, tV>* buscar(tC chave);

        // insere o par (chave, valor) na árvore
        void inserir(tC chave, tV valor){
            this->raiz.
        }

        // remove o nó com a chave especificada
        void remover(tC chave);

        // imprime a árvore
        void imprimir();
        // retorna a altura da árvore
        int altura();
        // retorna a altura negra da árvore
        int alturaNegra();
        // retorna o número de nós da árvore
        int tamanho();
        // retorna true se a árvore estiver vazia
        bool vazia();
        
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
        
private:    

   NoARN<tC, tV>* inserirNo(NoARN<tC, tV>* no, tC chave, tV valor){
        if(no == nullptr)
            return new NoARN(chave, valor);

        if(chave < no->chave)
            no->esq = inserirNo(no->esq, chave, valor);
        else if(chave > no->chave)
            no->dir = inserirNo(no->dir, chave, valor);
        else
            no->valor = valor;

        if((!no->esq->ehVermelho()) && (no->dir->ehVermelho())){
            no = no->rotacionarEsquerda();
        }

        if((no->esq->ehVermelho()) && (no->esq->esq->ehVermelho())){
            no = no->rotacionarDireita();
        }

        if((no->esq->ehVermelho()) && (no->dir->ehVermelho())){
            no->inverterCores();
        }

        return no;

    }

    // armazena o endereço da raiz da árvore
    NoARN<tC, tV> *raiz;
};

