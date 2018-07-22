#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include "roaderHeaven.h"
#include<vector>

using namespace std;

int main()
{
	//freopen("/Users/sangdolee/Desktop/Algorithm/StudyAlone/AlgorithmStudy/Text.txt", "r", stdin);
	vector<int> a;
	a.push_back(0);
	a.push_back(0);
	a.push_back(0);
	vector<vector<int> > b;
	b.push_back(a);
	b.push_back(a);
	b.push_back(a);
	int a = solution(3,3, b);

	return 0;
}
