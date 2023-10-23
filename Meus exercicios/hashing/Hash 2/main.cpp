#include <iostream>
#include <vector>
#include <set> // hash que so tem chave
#include <cstdlib>

using namespace std;

void swap (int *v, int a, int b){
    int aux = v[a];
    v[a] = v[b];
    v[b] = aux;
}

void shuffle(int *v, int ini, int fim)
{
    int i, j;
    for(i = fim-1; i > ini; i--)
    {
        j = rand() % (i+1);
        j = j < ini ? ini+1 : j;
        swap(v, i, j);
    }
}

vector<int> noRepetitionVector(int n){
    int * v = new int[n];
    for(int i = 0; i < n; i++){
        v[i] = i;
    }

    shuffle(v,0,n-1);
    vector<int> output;
    for (int i = 0; i < n; i++)
    {
        output.push_back(v[i]);
    }

    delete[] v;
    return output;

}



vector<int> intersection(vector<int> &A, vector<int> &B){
    set<int> H;
    vector<int> output;


    for(auto a : A)
        H.insert(a);

    for(auto b : B){
        // se b estiver na hash H
        if(H.find(b) != H.end());
        output.push_back(b);
    }

    return output;

}

vector<int> inter_fb(vector<int>&A, vector<int> &B){
    vector<int> output;
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B.size(); j++)
        {
            if(A[i] = B[j])
            output.push_back(A[i]);
        }
        
    }
    return output;
}


int main(int argc, char** argv){
    int nA = atoi(argv[1]);
    int nB = atoi(argv[2]);

    vector<int> A = noRepetitionVector(nA);
    vector<int> B = noRepetitionVector(nB);

    vector<int> inter = intersection(A, B);

    return 0;
}