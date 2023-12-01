#pragma once

#include <iostream>
#include <string>
template <typename C, typename V>
class ABB;

template <typename C, typename V>
class NoABB
{
public:
    NoABB(C chave, V valor)
        : chave(chave), valor(valor),
          esq(nullptr), dir(nullptr) {}

    ~NoABB(){
		if(this->esq != nullptr)
			delete this->esq;

		if(this->dir != nullptr)
			delete this->dir;
	}

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
    ~ABB(){
		if(this->raiz != nullptr)
			delete this->raiz;
	}

    // insere o par (chave, valor) na árvore
    void inserir(C chave, V valor){
        this->raiz = inserirNo(this->raiz, chave, valor);
    }
    
    // retorna o endereço do nó com a chave especificada
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

    //imprime a árvore
    //A saída é apresentada no vídeo: https://youtu.be/dzTCB5HthBQ?t=1960
    void imprimir(){
		imprimirNo(this->raiz, 0, 'r');
	}

    // retorna o endereço do nó com a menor chave
    NoABB<C, V>* minimo();

    //retorna o endereço do nó com a menor chave da subárvore enraizada no nó especificado
    // NoABB<C, V>* minimo(NoABB<C, V>* no);

    NoABB<C, V>* minimo(NoABB<C, V>* no){
        if(no == nullptr)
            return nullptr;

        auto p = no;
        while(p->esq != nullptr)
            p = p->esq;

        return p;
    }

    //retorna o endereço do nó com a maior chave da árvore
    NoABB<C, V>* maximo();
    //retorna o endereço do nó com a maior chave da subárvore enraizada no nó especificado
    NoABB<C, V>* maximo(NoABB<C, V>* no);

    //retorna o endereço do nó com a chave sucessora da chave especificada
    NoABB<C, V>* sucessor(C chave);
    //retorna o endereço do nó com a chave sucessora à chave do nó especificado
    NoABB<C, V>* sucessor(NoABB<C, V>* no);

    //retorna o endereço do nó com a chave antecessora da chave especificada
    NoABB<C, V>* antecessor(C chave);
    //retorna o endereço do nó com a chave antecessora à chave do nó especificado
    NoABB<C, V>* antecessor(NoABB<C, V>* no);

    // retorna o número de nós da árvore (recursivamente)
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

    NoABB<C, V>* removerNo(NoABB<C, V>* no, C chave){
        if(no == nullptr){
            return nullptr;
        }

        if(chave < no->chave)
            no->esq = removerNo(no->esq, chave);
        else if(chave > no->chave)
            no->dir = removerNo(no->dir, chave);
        else{
            //caso 1: o elemento a ser removido é folha
            if(no->esq == nullptr && no->dir == nullptr){
                delete no;
                return nullptr;
            }
            //caso 2: o elemento a ser removido tem 1 filho
            //2a: tá faltando o filho esquerdo. 
            if(no->esq == nullptr){
                auto aux = no->dir;
				no->dir = nullptr;
                delete no;
                return aux;
            }
            //2b: tá faltando o filho direito.
            if(no->dir == nullptr){
                auto aux = no->esq;
					
                delete no;
                return aux;
            }
            //caso 3: o nó a ser removido tem 2 filhos!
            //encontrar o sucessor
            auto suc = minimo(no->dir);
            no->chave = suc->chave;
            no->valor = suc->valor;
            no->dir = removerNo(no->dir, suc->chave);
        } 
        return no;
    }

    void imprimirNo(NoABB<C, V> *no, int nivel, char lado){
		if(no == nullptr) return;

		for (int i = 0; i < nivel; i++) {
   			std::cout << " ";
  		}

		std::cout << "(" << lado << "): " << no->chave << std::endl;
		imprimirNo(no->esq, nivel +1, 'e');
		imprimirNo(no->dir, nivel +1, 'd');
	}


    NoABB<C, V> *raiz;
};