#include <unordered_set>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

unordered_set<string> stringsConcatenadas(vector<string>&arr){

	unordered_set<string> saida;
	unordered_set<string> h(arr.begin(), arr.end());
	
	for(auto& s :  arr){
		for(int i = 1; i < s.size(); i++){
			string s1 = s.substr(0, i);
			string s2 = s.substr(i, s.size() - i);
			if(h.count(s1) && h.count(s2))
				saida.insert(s);
		}
	}
	return saida;
}


int main(int argc, char** argv){
	vector<string> v;

	v= {"cat", "dog", "catdog", "fish", "dogfish", "fishdog"};
	auto saida = stringsConcatenadas(v);

	for(auto s : saida){
		cout << s << " ";
	}
	cout << "\n";

	return 0;
}