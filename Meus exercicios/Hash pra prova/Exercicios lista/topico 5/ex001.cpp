#include <iostream>
#include <string>
#include <math.h>

using namespace std;

uint64_t expon(uint64_t a, uint64_t b){
	if(b == 0)
	for (int i = 0; i < b - 1; i++)
		a *= a;
	
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




int main(int argc, char** argv){
	// string s = argv[1];
	// int m = atoi(argv[2]);
	// int k = atoi(argv[3]);

	string s = "ABC";
	uint64_t m = 37;
	uint64_t k = 31;

	cout<< "Hash de " << s << ": " << string_hash(s, m, k);


	return 0;
}