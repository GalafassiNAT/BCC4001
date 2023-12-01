#include "arn.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <random>
#include <algorithm>

// testa a inserção e busca de valores na árvore
void test1(int argc, char** argv){
    ARN<char, char> arvore;

    // std::array<int, 8> valores = {10, 5, 15, 3, 7, 12, 17, 1};
    std::array<char, 7> valores = {'U', 'T', 'F', 'P', 'R', 'Z', 'X'};

    std::array<char, 4> valores2 = {'H', 'J', 'Y', 'A'};

    for(char x : valores){
        std::cout << "inserindo " << x << std::endl;
        arvore.inserir(x, x);
        arvore.imprimir();
    }

    arvore.imprimir();

    for(char x : valores){
        if(arvore.buscar(x) == nullptr)
            std::cout << "Erro: " << x << " nao encontrado" << std::endl;
    }

    for(char x : valores2){
        if(arvore.buscar(x) != nullptr)
            std::cout << "Erro: " << x << " encontrado" << std::endl;
    }

}

// testa a inserção de muitos valores na árvore
void test2(int argc, char** argv){

    int n = std::stoi(argv[1]);

    ARN<int, int> arvore;

    std::vector<int> valores(n);

    for(int i = 0; i < n; i++)
        valores.push_back(i);

    std::shuffle(valores.begin(), valores.end(), std::default_random_engine(0));

    for(int x : valores){
        arvore.inserir(x, x);
    }

}

// testa a inserção de muitos valores em ordem crescente na árvore
void test3(int argc, char** argv){

    int n = std::stoi(argv[1]);

    ARN<int, int> arvore;
        
    for(int i = 0; i < n; i++)
        arvore.inserir(i, i);

}

int main(int argc, char** argv){

    test1(argc, argv);
    test2(argc, argv);
    // test3(argc, argv);

    return 0;

}