#pragma once
#include<iostream>

using namespace std;

int HalaBong_parent[100000];
long long HalaBong_diff[100000];
long long HalaBong_max[100000];
bool HalaBong_isParent[100000];
void HalaBong_Init(int N)
{
	for (int i = 0; i < N; i++)
	{
		HalaBong_parent[i] = -1;
		HalaBong_diff[i] = 0;
		HalaBong_max[i] = 0; 
		HalaBong_isParent[i] = true;
	}
}
void HalaBong_Swap(int &i1, int &i2)
{
	int temp = i1;
	i1 = i2;
	i2 = i1;
}
int HalaBong_Find(int node)
{
	int pNode = HalaBong_parent[node];
	if (pNode < 0) return node;

	pNode = HalaBong_Find(pNode);
	HalaBong_diff[node] += HalaBong_diff[HalaBong_parent[node]];
	HalaBong_parent[node] = pNode;
	return pNode;
}

long long HalaBong_GetValue(int node)
{
	int pNode = HalaBong_parent[node];
	if (pNode < 0) return HalaBong_diff[node];

	long long res = HalaBong_diff[node];
	res += HalaBong_GetValue(pNode);
	return res;
}

void HalaBog_ChangeParent(int node1, int node2)
{

}

void HalaBong_Union(int node1, int node2, long long diff)
{
	//node1 is Parent
	int pNode1 = HalaBong_Find(node1);
	int pNode2 = HalaBong_Find(node2);
	if (HalaBong_max[node1] < HalaBong_max[node2])
	{
		HalaBong_Swap(node1, node2);
		HalaBong_Swap(pNode1, pNode2);
	}
	else if (HalaBong_max[node1] == HalaBong_max[node2])
	{
		if (HalaBong_parent[pNode1] > HalaBong_parent[pNode2])
		{
			HalaBong_Swap(pNode1, pNode2);
			HalaBong_Swap(node1, node2);
		}
	}
	long long pNode2Value = HalaBong_GetValue(node2) + diff;
	HalaBong_diff[pNode2] = diff;
	HalaBong_max[pNode1] = pNode2Value > HalaBong_max[pNode1] ? pNode2Value : HalaBong_max[pNode1];
	HalaBong_parent[pNode1] += HalaBong_parent[pNode2];
	HalaBong_parent[pNode2] = pNode1;
}

int HalaBong()
{
	ios::ios_base::sync_with_stdio(false);
	int T, N, M;
	long long res,long long L;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N >> M >> L;
	}
	
	return 0;
}