#pragma once
#include<iostream>
#include<cstring>
#include<string>

using namespace std;

int String_A[100];

void SetString(string str, int size)
{
	String_A[0] = -1;
	int i = 0;
	int j = 1;
	while (i < size)
	{
		if (str[i] == str[j])
		{
			String_A[j] = i;
			i++;
		}
	}
}

void StringType()
{
	string A, B;
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		string A, B;
		memset(String_A, -1, sizeof(String_A));
		cin >> A >> B;

		int index = 0;
		int c = 0;
		for (int i = 0; i < A.size(); i++) {
			if (A[i] == B[index]) {
				index++;
			}
			else {
				index = 0;
				if (A[i] == B[index])
					index++;
			}
			if (index == B.size()) {
				index = 0;
				c++;
			}
		}
		int result = (B.size() - 1)*c;

		/*int same_num = 0;
		for (int i = 0; i < A.size(); i++)
		{
			bool check = true;
			for (int j = 0; j < B.size(); j++)
			{
				if (i + j == A.size())
				{
					check = false;
					break;
				}
				if (A[i + j] == B[j]) continue;
				else
				{
					check = false;
					break;
				}
			}
			if (check)
			{
				same_num++;
				i += B.size()-1;
			}
		}
		*/
		cout << '#' << tc << ' ' << A.size() - result << endl;
	}
}