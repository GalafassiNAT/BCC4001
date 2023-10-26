#include <iostream>
#include <vector>
#include <unordered_set>
#include <random>
#include <algorithm>

bool saoIguais(std::vector<int>&v1, std::vector<int>&v2){
	if (v1.size() != v2.size())
		return false;

	std::unordered_set<int> h(v1.begin(), v1.end());


	for(int x : v2){
		if(h.count(x) == 0){
			return false;
		}
	}

	return true;

}

bool saoIguaisFB(std::vector<int>&v1, std::vector<int>&v2){
	if (v1.size() != v2.size())
		return false;

	bool achou = false;
	for(int x : v1){
		for (int y : v2)
		{
			if(x == y){
				achou = true;
				break;
			}
		}
	}
	if(!achou)
		return false;

	return true;

}


bool saoIguaisSort(std::vector<int>&v1, std::vector<int>&v2){
	if (v1.size() != v2.size())
		return false;

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	for(int i = 0; i < v1.size(); i++){
		if(v1.at(i) != v2.at(i))
			return false;
	}
		
	return true;

}

int main(int argc, char** argv){
	std::vector<int> v1 = {3, 4, 1, 0, 2, 5};
	std::vector<int> v2 = {0, 1, 2, 3, 4, 5};

	if(argc > 1){
		int n = atoi(argv[1]);
		v1.clear();
		for (int i = 0; i < n; i++)
		{
			v1.push_back(i);
		}
		v2 = v1;
		std::shuffle(v2.begin(), v2.end(), std::default_random_engine(0));

	}

	if(saoIguais(v1, v2)){
		std::cout << "os vetores sao iguais!" << std::endl;
	}else{
		std:: cout << "os vetores nao sao iguais!" << std::endl;
	}

	return 0;
}