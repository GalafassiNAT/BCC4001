#include <unordered_map>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <utility>
#include "print_pair.hpp"
#include <algorithm>



using namespace std;

// ex001
unordered_map<int, int> contarFrequencia(vector<int>& arr){
	unordered_map<int,int> m;
	for(int x : arr)
		m[x]++;

	return m;
}

void imprimirMapa(unordered_map<int, int>& mapa){
	for(auto it = mapa.begin(); it != mapa.end(); ++it){
		cout << it->first << ": " << it->second << endl;
	}
}

// ex002
int primeiroUnico(vector<int>& arr){
	unordered_map<int,int> map = contarFrequencia(arr);
	
	for (int i = 0; i < arr.size(); i++){
		if(map[arr[i]] == 1)
			return i;
	}
	
	return -1;
	
}

// ex003
pair<int, int> twosum(vector<int>& arr, int k){
	unordered_set<int> H;
	for(auto x : arr)
		H.insert(x);

	for(auto x : arr){
		if(H.count(k-x)){
			return make_pair(x, k-x);
		}
	}

	return make_pair(-1, -1);
}

// ex004
bool temDuplicatas(vector<int>& arr){
	unordered_set<int> H;
	for(auto x : arr){
		if (H.count(x))
			return true;
	
		H.insert(x);
	}
	
	return false;
}


// ex005
vector<int> semDuplicatas(vector<int>& arr){
	unordered_set<int> H;
	vector<int> vect;
	for(auto x : arr){
		if(!H.count(x))
			vect.push_back(x);
		H.insert(x);

	}
	
	return vect;
}

void printVect(vector<int>&arr){
	cout << "[";
	for(auto x : arr){
		cout << x << ", ";
	}	

	cout << "]" << endl;
}


// ex006
vector<vector<string>> agruparAnagramas(vector<string> &palavras){
	vector<vector<string>> vs;
	unordered_map<string, vector<string>> M;
	
	for(auto x: palavras){
		string s = x;
		sort(s.begin(), s.end());
		M[s].push_back(x);
	}
	
	for(auto x : M){
		vs.push_back(x.second);
	}

	return vs;

}

void printVectVect(vector<vector<string>>& vs){
	cout << "[";
	for (int i = 0; i< vs.size(); i++)
	{
		cout << "{";
		for(int j = 0; j < vs[i].size(); j++){
			cout << vs[i][j];
			if(j < vs[i].size() -1)
				cout << ", ";
		}
		cout << "}";
		if(i < vs.size() - 1)
			cout << ", ";
	}
	cout << "]" << endl;
}

// ex007
int maiorSequenciaConsecutivos(std::vector<int>& arr){
	
}


int main(int argc, char** argv){
	vector<int> arr = {1,2,4,3,2,1,5,4,2,1,6,2};
	vector <int> arr2 = {1,2,3,4,5,6,7,8,9};
	vector<string> palavras = {"ate", "eat", "tea", "bat","tab"};
	int k = 8;
	// unordered_map<int, int> map = contarFrequencia(arr);
	// imprimirMapa(map);
	// cout << endl;
	// cout << "Posição do primeiro numero com frequencia 1: " << primeiroUnico(arr);
	// cout << "par que somados dão " << k << ": " << twosum(arr, k) << endl;
	// cout << "a array tem elementos repetidos? " << temDuplicatas(arr2) << endl;
	// cout << "vetor com repeticoes: " << endl;
	// printVect(arr);
	// cout << "vetor sem repeticoes: " << endl;
	// vector<int> arr3 = semDuplicatas(arr);
	// printVect(arr3);
	vector<vector<string>> vs = agruparAnagramas(palavras);
	printVectVect(vs);

	return 0;
}