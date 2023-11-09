#pragma once

#include <iostream>

template <typename C, typename V>
class ABB;

template <typename C, typename V>
class NoABB
{
public:
    NoABB(C chave, V valor)
        : chave(chave), valor(valor),
          esq(nullptr), dir(nullptr) {}

    ~NoABB() = default;

    C getChave() { return chave; }
    V &getValor() { return valor; }

private:
    C chave;
    V valor;
    NoABB *esq;
    NoABB *dir;

    friend class ABB<C, V>;
};

template <typename C, typename V>
class ABB
{
public:
    ABB() {}
    ~ABB() = default;

    // insere o par (chave, valor) na árvore
    void inserir(C chave, V valor){
        this->raiz = inserirNo(this->raiz, chave, valor);
    }
    
    // retorna uma referência ao nó com a chave especificada
    NoABB<C, V>* buscar(C chave){
        auto p = this->raiz;
        while(p != nullptr){
            if(chave == p->chave){
                return p;
            }
            if(chave < p->chave)
                p = p->esq;
            else
                p = p->dir;
        }
        return nullptr;
    }

    // remove o nó com a chave especificada
    void remover(C chave){
        this->raiz = removerNo(this->raiz, chave);
    }
    // imprime a árvore
    void imprimir();
    // retorna uma referência ao nó com a menor chave
    NoABB<C, V>* minimo();

    NoABB<C, V>* minimo(NoABB<C,V>* no){
        if(no == nullptr)
            return nullptr;


        if(no->esq== nullptr)
            return no;
        return minimo(no->esq);

    }
    // retorna uma referência ao nó com a maior chave
    NoABB<C, V>* maximo();
    // retorna uma referência ao nó com a chave sucessora da chave especificada
    NoABB<C, V>* sucessor(C chave);
    // retorna uma referência ao nó com a chave antecessora da chave especificada
    NoABB<C, V>* antecessor(C chave);
    // retorna o número de nós da árvore
    int tamanho();
    // retorna true se a árvore estiver vazia
    bool vazia();

private:
    NoABB<C, V>* inserirNo(NoABB<C, V> *no, C chave, V valor){
        if(no == nullptr)
            return new NoABB(chave, valor);
        if(chave == no->chave)
            no->valor = valor;
        else if(chave < no->chave)
            no->esq = inserirNo(no->esq, chave, valor);
        else
            no->dir = inserirNo(no->dir, chave, valor);
        return no;
    }

    NoABB<C,V> *removerNo(NoABB<C,V>* no, C chave){
        if(no == nullptr){
            return nullptr;
        }

        if(chave < no->chave)
            no->esq = removerNo(no->esq, chave);
        else if(chave > no->chave)
            no->dir = removerNo(no->dir, chave);
        else{
            //caso 1: O elemento a ser removido é folha
            if(no->esq == nullptr && no->dir == nullptr){
                delete no;
                return nullptr;
            }
            //caso 2: O elemento a ser removido tem um filho
            //2a: Ta falantando o filho esquerdo
            if(no->esq == nullptr){
                auto aux = no->dir;
                delete no;
                return aux;
            }
            //2b: Ta falantando o filho direito
            if(no->dir == nullptr){
                auto aux = no->esq;
                delete no;
                return aux;
            }
            // Caso 3: O nó removido tem 2 filho
            // encontrar o sucessor
            auto suc = minimo(no->dir);
            no->chave = suc->chave;
            no->valor = suc->valor;
            no->dir = removerNo(no->dir, suc->chave);

        }
        
        return no;

    }

    void imprimirNo(NoABB<C, V> *no, int nivel, char lado);

    NoABB<C, V> *raiz;
};


