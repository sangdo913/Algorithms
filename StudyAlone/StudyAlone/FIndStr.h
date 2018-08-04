#pragma once
#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>

using namespace std;

struct FindSTR_Info
{
	int nums;
	int position[1000001];
	int kmp[1000001];
	int end;

	string p;
	string t;

	int min(int i1, int i2)
	{
		return i1 < i2 ? i1 : i2;
	}

	void makeKMP()
	{
		int ind = 0;
		kmp[0] = -1;
		int len = p.length();

		for (int i = 1; i < len; i++)
		{
			kmp[i] = ind;
			while (ind != -1 && p[ind] != p[i])
			{
				ind = kmp[ind];
			}

			ind++;
		}

		int same1 = 1, same2 = 1;
		for (int i = 0; i < len-1; i++)
		{
			if (p[i] != p[i + 1]) break;
			same1++;
		}
		
		int cnt = kmp[len - 1];

		for (int i =0; i < cnt; i++)
		{
			if (p[len-1-i] != p[len-1]) break;
			same2++;
		}

		same1 = min(same1, same2);

		if (p[len - 1] == p[kmp[len - 1]]) end = kmp[len - 1] + 1;
		else if (p[len - 1] == p[0]) end = same1;
		else end = 0;
	}

	void find()
	{
		int m = 0;
		int len = t.length();
		int lenP = p.length();
		for (int i = 0; i < len; i++)
		{
			while (m != -1 && p[m] != t[i])
			{
				m = kmp[m];
			}
			
			m++;
		
			if (m == lenP)
			{
				position[nums++] = i - lenP + 2;
				m = end;
			}
		}
	}

	void init()
	{
		nums = 0;
		getline(cin, t);
		getline(cin, p);

	}

	void print()
	{
		cout << nums << endl;
		for (int i = 0; i < nums; i++)
		{
			cout << position[i] << ' ';
		}
		if(nums != 0) cout << '\n';
	}
	
}FindStr_info;



int FIndStr()
{
	FindStr_info.init();
	FindStr_info.makeKMP();
	FindStr_info.find();
	FindStr_info.print();
	return 0;
}