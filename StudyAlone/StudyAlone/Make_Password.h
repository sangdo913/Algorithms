#pragma once
#include<iostream>

using namespace std;
bool Password_chars['z'-'a'+1];
int Num = 0;
int Password_Check(bool check['z' - 'a' + 1])
{
	int checkNum = 0;
	int motherChar[5] = { 'a','e','i','o','u' };
	for (int i = 0; i < 5; i++)
	{
		checkNum += check[motherChar[i]-'a'];
	}
	return checkNum;
}

void Password_Print(bool check['z' - 'a' + 1],const int size)
{
	int numOfMother = Password_Check(check);
	if (numOfMother==0 || (size - numOfMother) < 2) return;

	for (int i = 0; i < 'z' - 'a' + 1; i++)
	{
		if (check[i]) cout << (char)(i + 'a');
	}
	Num++;
	cout << '\n';
}

void Possible_Password(int count, int L, int length, bool check['z'-'a'+1],const int size)
{
	if (length > 'z' - 'a' + 1) return;
	if (count == L)
	{
		Password_Print(check,size);
		return;
	}

	if (Password_chars[length])
	{
		check[length] = true;
		Password_chars[length] = false;
		Possible_Password(count + 1, L, length + 1, check, size);
		check[length] = false;
		Password_chars[length] = true;
		
	}

	Possible_Password(count, L, length + 1, check, size);
}

int Make_Password()
{
	int L, C;
	char input;
	cin >> L >> C;
	for (int i = 0; i<C;i++)
	{
		Num = 0;
		cin >> input;
		Password_chars[input-'a'] = true;
	}
	bool check['z' - 'a'+1] = { false };
	Possible_Password(0, L, 0, check, L);
	return 0;
}