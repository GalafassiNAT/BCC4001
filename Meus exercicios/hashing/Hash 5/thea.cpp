#include "thea.h"

#include <iostream>

TabHashEndAberto::TabHashEndAberto(int tamanho,
    FSondagem* fsondagem, float limiar){
    this->m = tamanho;
    // this->s = this->m-1;
    this->n = 0;
    this->colisoes_insercao = 0;
    this->limiar = limiar;
    this->redims = 0;
    this->tabela = new Elemento[m];
    this->fsondagem = fsondagem;
    this->gp = GeradorPrimos(1000000);
    for (int i = 0; i < m; i++) {
        this->tabela[i].estado = Estado::LIVRE;
    }

}

TabHashEndAberto::~TabHashEndAberto(){
    delete[] this->tabela;
}

int TabHashEndAberto::hash(int chave, int k){
    return ((chave % this->m) + this->fsondagem->p(chave, k)) % m;
    
    // if(this->fsondagem == "linear")
    //     return ((chave % this->m) + k) % this->m;
    // if(this->fsondagem == "quadratica")
    //     return ((chave % this->m) + (k*k)) % this->m;
    // if(this->fsondagem == "duplo"){
    //     int h2 = (chave % (this->s-1)) + 1;
    //     return ((chave % this->m) + (k*h2)) % this->m;
    // }

    return -1;
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

std::pair<int,int> TabHashEndAberto::buscar(int chave){
    int pos = buscar_pos(chave);
    if(pos == -1)
        return this->invalido;
    auto ret = std::make_pair(this->tabela[pos].chave, this->tabela[pos].valor);
    return ret;
}

void TabHashEndAberto::inserir(int chave, int valor){

    int h = this->buscar_pos(chave);
    if (h >= 0) {
        this->tabela[h].valor = valor;
        return;
    }

    if( (float)this->n/this->m > this->limiar){
        this->redimensionar(gp.proximo(this->m*2));
        this->redims++;
    }

    int k = 0;
    h = hash(chave, k);
    while(this->tabela[h].estado == Estado::OCUPADO){
        this->colisoes_insercao++;
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

void TabHashEndAberto::remover(int chave){
    int pos = buscar_pos(chave);
    if(pos == -1)
        return;
    this->tabela[pos].estado = Estado::APAGADO;
    this->n--;
}

void TabHashEndAberto::imprimir(){
    for (int i = 0; i < this->m; i++) {
        std::cout << i << ": ";
        const auto& el = this->tabela[i];
        std::cout << "(" << el.chave << "," << el.valor << ") ";
        char estado = el.estado == Estado::APAGADO ? 'A' :
                      (el.estado == Estado::LIVRE ? 'L' : 'O');
        std::cout << "[" << estado << "]";
        std::cout << std::endl;
    }    
}

void TabHashEndAberto::imprimir_info(){
    using namespace std;
    cout << "m: " << this->m << "\n";
    cout << "n: " << this->n << "\n";
    cout << "fator de carga: " 
         << (float)this->n / this->m << "\n";
    cout << "redimensionamentos: " << this->redims
         << endl;
    cout << "colisões: " << this->colisoes_insercao
    << endl;
}

std::vector<int> TabHashEndAberto::chaves(){
    std::vector<int> saida;
    for (int i = 0; i < this->m; i++) {
        if(this->tabela[i].estado == Estado::OCUPADO){
            saida.push_back(this->tabela[i].chave);
        }
    }
    return saida;
}

std::vector<std::pair<int,int>> TabHashEndAberto::itens(){
    std::vector<std::pair<int,int>> saida;
    for (int i = 0; i < this->m; i++) {
        if(this->tabela[i].estado == Estado::OCUPADO){
            saida.push_back(std::make_pair(this->tabela[i].chave, 
                            this->tabela[i].valor));
        }
    }
    return saida;
}

void TabHashEndAberto::redimensionar(int novo_m){
    Elemento* antiga = this->tabela;
    int m_antigo = this->m;
    // this->s = novo_m-1;
    this->fsondagem->redim_callback(novo_m); 
    this->tabela = new Elemento[novo_m];
    this->n = 0;
    this->m = novo_m;

    for(int i = 0 ; i < novo_m; i++)
        this->tabela[i].estado = Estado::LIVRE;
    
    for(int i = 0; i < m_antigo; i++){
        if(antiga[i].estado == Estado::OCUPADO){
            this->inserir(antiga[i].chave, 
                          antiga[i].valor);
        }
    }
    delete[] antiga;
}
