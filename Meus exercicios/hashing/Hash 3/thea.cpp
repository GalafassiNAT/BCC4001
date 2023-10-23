#include <iostream>
#include "thea.h"

TabHashEndAberto::TabHashEndAberto(int tamanho, float limiar){
    this->n = 0;
    this->m = tamanho;
    this->limiar = limiar;
    this->redims = 0;
    this->tabela = new Elemento[m];
    for (int i = 0; i < m; i++)
    {
        this->tabela[i].estado = Estado::LIVRE;
    }
    
}

void TabHashEndAberto::redimensionar(int novo_m){
    Elemento* antiga = this->tabela;
    int m_antigo = this->m;
    this->tabela = new Elemento[novo_m];
    this->n = 0;
    this->m = novo_m;

    for (int i = 0; i < novo_m; i++)
    {
        this->tabela[i].estado = Estado::LIVRE;
    }
    for (int i = 0; i < m_antigo; i++)
    {
        if (antiga[i].estado == Estado::OCUPADO){
            this->inserir(antiga[i].chave, antiga[i].valor);
        }
    }
    delete[] antiga;
    this->redims++;
    
}

TabHashEndAberto::~TabHashEndAberto(){
    delete[] this->tabela;
}

void TabHashEndAberto::inserir(int chave, int valor){

    int h = this->buscar_pos(chave);
    if (h >= 0) {
        this->tabela[h].valor = valor;
        return;
    }

    if ((float)this->n/this->m > this->limiar)
    {
        this->redimensionar(this->m*2);
    }
    

    int k = 0;
    h = hash(chave, k);
    while(this->tabela[h].estado == Estado::OCUPADO){
        k++;
        h = hash(chave, k);
        if(k == this->m)
            return;
    }

    this->tabela[h].chave = chave;
    this->tabela[h].valor = valor;
    this->tabela[h].estado = Estado::OCUPADO;
    this->n++;

}

bool TabHashEndAberto::remover(int chave){
    int h = buscar_pos(chave);
    if (h >= 0){
        this->n--;
        this->tabela[h].estado = Estado::APAGADO;
        return true;
    }
    return false;
}

std::pair<int, int> TabHashEndAberto::buscar(int chave){
    int pos = buscar_pos(chave);
    if (pos == -1)
        return this->invalido;
    
    return std::make_pair(this->tabela[pos].chave, this->tabela[pos].valor);
    

}

void TabHashEndAberto::imprimir(){
    using namespace std;
    for (int i = 0; i < this->m; i++)
    {
        cout<< "[" << i << "]: ";
        auto& el = this->tabela[i];
        cout << "(" << el.chave <<" " << el.valor << ") ";

        char estado = el.estado == Estado::APAGADO ? 'A': (el.estado == Estado::LIVRE ? 'L' : 'O');
        cout << "[" << estado << "]" << endl;
    }

    
}

void TabHashEndAberto::imprimir_info(){
    using namespace std;
    cout << "m: " << this->m << endl;
    cout << "n: " << this->n << endl;
    cout << "fator de carga: " << (float)this->n/this->m << endl;
    cout << "Redimencionamentos: " << this->redims << endl;
}

int TabHashEndAberto::hash(int chave, int k){
    return ((chave % this->m)+k) % this->m;
}

int TabHashEndAberto::buscar_pos(int chave){
    int k = 0;
    int h = hash(chave, k);
    while(this->tabela[h].estado != Estado::LIVRE){
        if((this->tabela[h].estado == Estado::OCUPADO) 
            && (this->tabela[h].chave == chave)){
            return h;
        }
        k++;
        if(k==this->m)
            break;
        h = hash(chave, k);
    }
    return -1;
}   
