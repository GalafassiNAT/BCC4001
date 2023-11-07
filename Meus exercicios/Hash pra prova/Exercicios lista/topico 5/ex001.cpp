#include <iostream>
#include <string>

using namespace std;

uint64_t expon(uint64_t a, uint64_t b){
	uint64_t aor = a;
	if(b == 0)
		return 1;
	for (int i = 0; i < b - 1; i++)
		a *= aor;
	
	return a;
}



uint64_t string_hash(string s, int m, int k){
	uint64_t power = s.size() - 1;
	uint64_t sum = 0;
	uint64_t exp = 0;

	for (int i = 0; i < s.size(); i++){
		uint64_t temp = (uint64_t)s[i];
		exp = expon(k, power);
		sum += temp * exp;
		power--;
	}

	return sum % m;
}

uint64_t hornerString_hash(string s, int m, int k){
	int sum = 0;
	for (int i = 0; i < s.size(); i++)
		sum = (sum * k + s[i]);
	
	
	return sum % m;
}


int main(int argc, char** argv){
	string s = argv[1];
	int m = atoi(argv[2]);
	int k = atoi(argv[3]);

	// string s = "ABCDE";
	// uint64_t m = 37;
	// uint64_t k = 31;

	cout<< "Hash de " << s << ": " << string_hash(s, m, k) << endl;
	cout<< "Hash de " << s << ": " << hornerString_hash(s, m, k) << endl;


	return 0;
}