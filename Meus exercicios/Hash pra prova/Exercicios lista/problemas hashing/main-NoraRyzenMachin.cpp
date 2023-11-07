#include <unordered_map>
#include <vector>
#include <iostream>

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


int main(int argc, char** argv){
	vector<int> arr = {1,2,4,3,2,1,5,4,2,1,6,2};
	// unordered_map<int, int> map = contarFrequencia(arr);
	// imprimirMapa(map);
	// cout << endl;
	cout << "Posição do primeiro numero com frequencia 1: " << primeiroUnico(arr);

	return 0;
}