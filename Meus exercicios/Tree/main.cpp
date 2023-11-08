#include "abb.hpp"
#include <iostream>


int main(int argc, char** argv){


    ABB<int, int> arvore;

    arvore.inserir(10, 10);
    arvore.inserir(5, 5);
    arvore.inserir(15, 15);
    arvore.inserir(3, 3);
    arvore.inserir(7, 7);
    arvore.inserir(12, 12);
    arvore.inserir(17, 17);
    arvore.inserir(1, 1);

    if(arvore.buscar(10)){
        std::cout << "achei o 10" << std::endl;
    }
    if(arvore.buscar(1)){
        std::cout << "achei o 11" << std::endl;
    }
    if(arvore.buscar(14)){
        std::cout << "achei o 14" << std::endl;
    }else{
        std::cout << "nao achei o 14" << std::endl;

    }

    // arvore.imprimir();

}