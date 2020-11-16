#include<iostream>
#include<cstdio>
#include<fstream>
#include<string>
using namespace std;
#define SIZE 100


int recog(int image[SIZE][SIZE]) {
    fstream file("0Text.txt");
    
    for(int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            string d = "00";
            d[0] = image[i][j] / 10 + '0';
            d[1] = image[i][j] %10 + '0';
            file << d << ' ';
        }
        file << '\n';
    }
	return 1;   
}