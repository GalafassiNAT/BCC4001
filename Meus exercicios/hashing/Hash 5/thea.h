#pragma once

#include <vector>
#include <utility>
#include <string>
#include "sondagem.h"

class GeradorPrimos {

public:

    GeradorPrimos(int n=1000000) : n(n){
        primos = sieve(n);
    }

    // retorna o menor primo > a
    int proximo(int a){
        //todo: considerar que n pode ser muito grande!
        if(a >= primos[primos.size()-1]){
            n = n*2;
            primos = sieve(n);
        }

        int i = buscar(a);
        //std::cout << i << std::endl;

        return primos[i];
    }

private:


    int buscar(int a){
        int l = 0, r = primos.size()-1;
        while(l <= r){
            //std::cout << l << " " << r << std::endl;
            int m = (l+r)/2;
            if(primos[m] == a) return m;
            if(a < primos[m]) r = m-1;
            else l = m+1;
        }
        return l;
    }

    std::vector<int> sieve(int n){
        std::vector<int> primes;
        std::vector<bool> is_prime(n+1, true);
        is_prime[0] = is_prime[1] = false;
        for(int i = 2; i <= n; i++){
            if(is_prime[i]){
                primes.push_back(i);
                for(int j = i*2; j <= n; j += i){
                    is_prime[j] = false;
                }
            }
        }
        return primes;
    }

    int n;
    std::vector<int> primos;
    
};

class TabHashEndAberto {
public:
    //Construtor: inicializa uma nova tabela com tamanho m
    TabHashEndAberto(int tamanho, FSondagem* fsondagem, float limiar = 0.5);
    //Destrutor: libera todos os recursos alocados para a tabela
    ~TabHashEndAberto(); 
    
    //Insere um novo par (chave, valor) na tabela
    void inserir(int chave, int valor);
    
    //Remove o par com a chave da tabela
    void remover(int chave);
    
    //Busca o valor associado a chave na tabela
    std::pair<int,int> buscar(int chave);
    
    //Imprime a tabela
    void imprimir();

    //Imprime informações sobre a tabela (m, n e fator de carga)
    void imprimir_info();

    //par chave-valor inválido para indicar que a chave não foi encontrada
    std::pair<int,int> invalido;

    // retorna as chaves da tabela
    std::vector<int> chaves();

    // retorna todos os pares (chave, valor) da tabela
    std::vector<std::pair<int,int>> itens();

private:

    enum class Estado {
        LIVRE,
        OCUPADO,
        APAGADO
    };

    struct Elemento {
    public:
        int chave;
        int valor;
        Estado estado;
    };

    int m; // tamanho da tabela
    int n; // número de elementos na tabela
    // limiar para redimensionamento. quando n/m > limiar, redimensionar
    float limiar; 
    int redims; // número de redimensionamentos realizados

    Elemento *tabela; // tabela hash

    int hash(int chave, int k); //função hash

    // redimensiona a tabela para o novo tamanho (novo_m)
    void redimensionar(int novo_m); 

    //retorna a posição que a chave ocupa na tabela. 
    //(ou -1 se a chave não estiver na tabela)
    int buscar_pos(int chave);

    // int s;
    FSondagem* fsondagem;
    int colisoes_insercao;
    GeradorPrimos gp;
};