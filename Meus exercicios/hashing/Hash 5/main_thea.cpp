#include <iostream>
#include "thea.h"
#include "print_pair.h"
#include <cstdlib>
#include "sondagem.h"


void test3(int argc, char** argv){
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    float limiar = atof(argv[3]);
    // std::string fsondagem = argv[4];

    // FSondagem* fsondagem = new SondagemLinear();
    // FSondagem* fsondagem = new SondagemQuadratica();
    // FSondagem* fsondagem = new SondagemHashDuplo(m-1);
    FSondagem * fsondagem = buildFsondagem(argv[4],  m);
    TabHashEndAberto tab(m, fsondagem, limiar);
    srand(1);
    for(int i = 0; i < n; i++){
        tab.inserir(rand() % (n*100), rand() % (n*100));
    }

    tab.imprimir_info();

    // for(int i = 0; i < n; i++){
    //     tab.buscar(rand() % (n*100));
    // }

    //tab.imprimir();

}


int main(int argc, char** argv){
    
    //test1();
    //test2();
    test3(argc, argv);

    return 0;
}
