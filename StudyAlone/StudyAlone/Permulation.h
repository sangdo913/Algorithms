#pragma once
#include<iostream>

using namespace std;

char arr[100] = {'+', '0', '1', '-', '-', 'x', 'x', '/', '/', '/'};
int CNT = 0;
void P_swap(int x, int y)
{
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}
void P_print(int r)
{
	for (int i = 0; i < r; i++)
	{
		cout << arr[i] << " ";
	}
	cout << '\n';
	CNT++;
}

void permul(int n, int r, int length)
{
	if (r == length)
	{
		P_print(r);
		return;
	}

	for (int i = length; i < n; i++)
	{
		if (arr[length] == arr[i]) continue;
		P_swap(length,i);
		permul(n, r, length + 1);
		P_swap(length, i);
	}
}


void Permulation()
{/*
	for (int i = 0; i < 100; i++)
	{
		arr[i] = i;
	}*/

	permul(3, 2, 0);
	cout << CNT << endl;
}
