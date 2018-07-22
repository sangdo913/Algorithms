#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include"PELINDROME.h"

using namespace std;
/*
int main()
{
	freopen("/Users/sangdolee/Desktop/Algorithm/StudyAlone/StudyAlone/00Text.txt", "r", stdin);
	PELINDROME();
	
	return 0;
}
*/
#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include "roaderHeaven.h"
#include<vector>

using namespace std;

int main()
{
	//freopen("/Users/sangdolee/Desktop/Algorithm/StudyAlone/AlgorithmStudy/Text.txt", "r", stdin);

	vector<vector<int> > b;
	for(int i = 0; i < 3; i++){
		b.resize(3);
		for(int j = 0; j < 3; j++){
			b[i].push_back(0);
		}
	}
	int a = solution(3,3, b);

	return 0;
}
