#pragma once

#include <stdint.h>

class FSondagem{
    public:
    virtual uint64_t p(int chave, int k) = 0;
    virtual void redim_callback(int m_novo) { }
};

class SondagemLinear : public FSondagem{
    public:
    uint64_t p(int chave, int k){
        return k;
    }

};

class SondagemQuadratica : public FSondagem{
    public:
    uint64_t p(int chave, int k){
        return k*k;
    }

};

class SondagemHashDuplo : public FSondagem{
    public:
    SondagemHashDuplo(int s) { this->s = s; }
    uint64_t p(int chave, int k){
        return k * ((chave % this->s-1) + 1);
    }

    void redim_callback(int novo_m){
        this->s = novo_m - 1;
    }

    private:
    int s;
};


FSondagem* buildFsondagem(std::string nome, int m){
    if(nome == "Linear")
        return new SondagemLinear();
    if(nome == "Quadratica")
        return new SondagemQuadratica();
    if(nome == "duplo")
        return new SondagemHashDuplo(m-1);
    return nullptr;
}