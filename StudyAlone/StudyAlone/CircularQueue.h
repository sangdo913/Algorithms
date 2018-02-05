#pragma once
#include<iostream>

using namespace std;

int CirCular_RIGHT(int max, int cursor,int des)
{
	if (cursor <= des) return des - cursor;
	else return max - cursor + des;

}
int CirCular_LEFT(int max, int cursor,int des)
{
	if (cursor >= des) return cursor - des;
	else
	{
		return max - des + cursor;
	}
}

void CirCularQueue()
{
	int cursor = 0;
	int max;
	int positions[50];
	int result = 0,length;
	cin >> max >> length;
	for (int i = 0; i < length; i++)
	{
		cin >> positions[i];
		positions[i]--;
	}

	for (int i = 0; i < length; i++)
	{
		int left = CirCular_LEFT(max, cursor, positions[i]);
		int right = CirCular_RIGHT(max--, cursor, positions[i]);

		result += right > left ? left : right;
		
		cursor = positions[i];
		
		for (int j = i+1; j < length; j++)
		{
			positions[j] = cursor < positions[j] ? --positions[j] : positions[j];
		}
	}

	cout << result << endl;
}


