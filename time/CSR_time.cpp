#include "../src/Matrix/CSR.h"
#include "../src/Matrix/DenseMatrix.h"
#include <vector>
#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using steady_clock = std::chrono::steady_clock;


void get_time_CSR_20(){
	std::srand(time(0));  
	std::vector<int> values;
    std::vector<int> vector;
	int value;
    std::ofstream file;
    file.open ("CSR_time20.csv");
    auto start = steady_clock::now();
	for(size_t i = 100; i < 2005; i += 5){
		for(size_t j = 0; j < i * i; j++){
			value = ((std::rand() % 3 == 0) ? std::rand() : 0); 
			values.push_back(value);

		}
		CSR<int> matrix(values, i, i);

		for(size_t j = 0; j <= i; j++){
			vector.push_back(std::rand());
		}
        
        file << i << ", ";
		start = steady_clock::now();
		std::vector<int> result = matrix * vector;
        file << std::chrono::duration_cast<std::chrono::microseconds>(steady_clock::now() - start).count() << std::endl;
		 
    }
    file.close();
}

void get_time_Dense_20(){
	std::srand(time(0)); 
	std::vector<int> values;
    std::vector<int> vector;
	int value;
    std::ofstream file;
    file.open ("Dense_time20.csv");
    auto start = steady_clock::now();
	for(size_t i = 100; i < 2005; i += 5){
		for(size_t j = 0; j < i * i; j++){
			value = ((std::rand() % 3 == 0) ? std::rand() : 0); 
			values.push_back(value);

		}
		DenseMatrix<int> matrix(values,i,i);

		for(size_t j = 0; j <= i; j++){
			vector.push_back(std::rand());
		}
        
        file << i << ", ";
		start = steady_clock::now();
		std::vector<int> result = matrix * vector;
        file << std::chrono::duration_cast<std::chrono::microseconds>(steady_clock::now() - start).count() << std::endl;
		 
    }
    file.close();
}

void get_time_CSR_zeros(){
	std::srand(time(0)); 
	std::vector<int> values;
    std::vector<int> vector;
	int value;
    std::ofstream file;
    file.open ("CSR_time_zeros.csv");
	int n = 1000;
    auto start = steady_clock::now();
	for(size_t j = 0; j <= n; j++){
		vector.push_back(std::rand());
	}
	for(size_t i = 0 ;i < 500000; i+=10){
		std::vector<int> values;
		std::vector<int> rows(n + 1, 0);
		std::vector<int> cols;
		for(size_t j = 0; j < i; j ++){
			value = std::rand();
			int row = rand() % n;
        	int col = rand() % n;
			values.push_back(value);
        	cols.push_back(col);
        	rows[row + 1]++;
		}
		for (int j = 1; j <= n; j++) {
        	rows[j] += rows[j - 1];
    	}
		CSR<int> matrix(values, cols, rows);
        
        file << i << ", ";
		start = steady_clock::now();
		std::vector<int> result = matrix * vector;
        file << std::chrono::duration_cast<std::chrono::microseconds>(steady_clock::now() - start).count() << std::endl;
		 
    }
    file.close();
}



void get_time_Dense_zeros(){
	std::srand(time(0)); 
    std::vector<int> vector;
	int value;
    std::ofstream file;
    file.open ("Dense_time_zeros.csv");
	int n = 1000;
	std::vector<std::vector<int>> matr(n, std::vector<int>(n, 0));
    auto start = steady_clock::now();
	for(size_t j = 0; j <= n; j++){
		vector.push_back(std::rand());
	}
	for(size_t i = 0 ;i < 500000; i+=10){
		std::vector<std::vector<int>> matr(n, std::vector<int>(n, 0));
    
		for(size_t j = 0; j < i; j ++){
			value = std::rand();
			int row = rand() % n;
        	int col = rand() % n;
			matr[row][col] = value;
		}
		DenseMatrix<int> matrix(matr);
        
        file << i << ", ";
		start = steady_clock::now();
		std::vector<int> result = matrix * vector;
        file << std::chrono::duration_cast<std::chrono::microseconds>(steady_clock::now() - start).count() << std::endl;
		 
    }
    file.close();
}



int main(){
    get_time_Dense_zeros();
	get_time_CSR_zeros();
}