#pragma once
#include<iostream>
#include<vector>
using namespace std;
bool FindParent(const vector<int> & info, const int parent, int input)
{
	while (input > 0)
	{
		if (parent == info[input]) return true;
		input = info[input];
	}

	return false;
}

int isParent(vector<int> info[2], int input1, int input2)
{
	int result = 0;
	int parent, temp_parent = parent = info[1][input1];

	while (!FindParent(info[1],temp_parent,input2))
	{
		temp_parent = info[1][temp_parent];
	}

	return temp_parent;
}

void SizeInCrease(vector<int>info[2], int num)
{
	const int SIZE_OF_TREE = 0;
	const int TREE = 1;
	int init = num;
	while (info[TREE][num] > 0)
	{
		info[SIZE_OF_TREE][info[TREE][num]]+= info[SIZE_OF_TREE][init];
		num = info[TREE][num];
	}
}
void BinarySubSet()
{
	int T;
	cin >> T;

	for (int tc = 1; tc <= T; tc++)
	{
		int num_of_nodes, num_of_edges, f, s;
		int result = 0;
		int temp1, temp2;
		cin >> num_of_nodes >> num_of_edges >> f >> s;

		const int SIZE_OF_TREE = 0;
		const int TREE = 1;
		vector<int>  nodes[2];
		++num_of_nodes;
		nodes[SIZE_OF_TREE].resize(num_of_nodes, 1);
		nodes[TREE].resize(num_of_nodes, 0);

		for (int i = 0; i < num_of_edges; i++)
		{
			cin >> temp1 >> temp2;
		
			nodes[TREE][temp2] = temp1;
			SizeInCrease(nodes, temp2);
		}

		//find parnet
		int tempParent;

		tempParent=isParent(nodes, f, s);

		if (tc == 1)
		for (int i = 0; i < num_of_nodes; i++)
		{
			cout << "i: " << i << " " << nodes[SIZE_OF_TREE][i] << endl;
		}

		cout << "#" << tc << " " << tempParent << " " << nodes[SIZE_OF_TREE][tempParent] << endl;
	}
}