#include <unordered_map>
#include <vector>
#include <iostream>

int primeiroUnico(std::vector<int>& arr){
    // contar a frequencia de todos os elementos
    std::unordered_map<int, int> m;
    for(int x : arr){
        // if(m.count(x)){
        //     m.at(x)++;
        // }else{
        //     m.insert({x, 1});
        // }
        m[x]++;
    }

    // procurar o primeiro elemento de arr cuja frequencia é 1
    for(int i = 0; i < arr.size(); i++){
        if(m[arr[i]] ==1)
        // if(m.at(arr[i]) == 1)
            return i;
    }
    return -1;
}

int main(){
    std::vector<int> v = {1,2,3,4,10,2,1,4,3,7};
    std::cout << primeiroUnico(v) << std::endl;

    return 0;
}
