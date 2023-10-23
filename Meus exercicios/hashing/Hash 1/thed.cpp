#include "thed.h"
#include <iostream>

TabHashEncadeamento::TabHashEncadeamento(int tamanho, int limiar){
    this->n = 0;
    this->m = tamanho;
    this->tabela = new std::vector<std::pair<int,int>>[m];
    this->invalido = std::make_pair(-1,-1);
    this->limiar = limiar;
    this->redims = 0;
}

TabHashEncadeamento::~TabHashEncadeamento(){
    delete[] this->tabela;
}

int TabHashEncadeamento::hash(int chave){
    return chave % this->m;
}

void TabHashEncadeamento::inserir(int chave, int valor){
   auto& el = buscar(chave);
    if(el != this->invalido){
        el.second = valor;
        return;
    }

    if(this->n/this->m >= limiar){
        imprimir();
        std::cout << "\n";
        redimensionar(this->m*2);
    }

    int h = hash(chave);
    
    this->tabela[h].push_back(std::make_pair(chave,valor));
    this->n++;
}

std::pair<int,int>& TabHashEncadeamento::buscar(int chave){
    
    int h = hash(chave);
    for (auto& el: this->tabela[h]){
        if(el.first == chave)
            return el;
    }

    return this->invalido;   
}

void TabHashEncadeamento::imprimir(){
    for (int i = 0; i < m; i++)
    {
        std::cout << i << ": ";
        for (auto&  el : this->tabela[i])
        {
            std::cout << "(" << el.first << "," << el.second << "), ";
        }
        std::cout << std::endl;
    }
    
}

std::vector<int> TabHashEncadeamento::chaves(){
    std::vector<int> saida;

    for(int i=0; i < this->m; i++){
        for(auto& el : this->tabela[i])
            saida.push_back(el.first);
    }
    return saida;
}

std::vector<std::pair<int,int>> TabHashEncadeamento::itens(){
    std::vector<std::pair<int,int>> saida;
    for(int i=0; i < this->m; i++)
        for(auto& el : this->tabela[i])
            saida.push_back(el);

    return saida;
}

void TabHashEncadeamento::redimensionar(int novo_m){
    this->redims++;
    auto* antiga = this->tabela;
    int m_antigo = this->m;
    this->tabela = new std::vector<std::pair<int,int>>[novo_m];
    this->m = novo_m;
    this->n = 0;
    for (int i = 0; i < m_antigo; i++)
    {
        for(auto& el : antiga[i]){
            this->inserir(el.first, el.second);
        }
    }
    delete[] antiga;
}
