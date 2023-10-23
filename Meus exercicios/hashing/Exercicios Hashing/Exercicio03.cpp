#include <unordered_set>
#include <utility>
#include <vector>
#include <iostream>
#include <cstdlib>

std::pair<int, int> twosum(std::vector<int>&arr, int k){
    std::unordered_set<int> H;

    for(int x : arr){
        H.insert(x);
    }

    for(int x : arr){
        if(H.count(k-x)){
            return std::make_pair(x, k-x);
        }
    }

    return std::make_pair(-1, -1);
}

int main(int argc, char** argv){
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);

    std::vector<int> v(n);
    for(int i = 0; i < n; i++){
        v.push_back(i);
    }

    auto par = twosum(v, k);
    if(par.first + par.second == k){
        std::cout << par.first << " + " << par.second << " = " << k << "\n";

    }else{
        std::cout << "nao achei o par que somado da " << k << "\n";
    }

}