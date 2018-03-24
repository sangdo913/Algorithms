#pragma once
//https://www.acmicpc.net/problem/9466 백준 텀 프로젝트
#include<iostream>

using namespace std;

int TermProject_notTeam;
int TermProject_wantWith[100001];
bool TermProject_visited[100001];
bool TermProject_teamSelected[100001];

int TermProject_MakeTeam(int nowStudent)
{
	TermProject_visited[nowStudent] = true;

	int wantWith = TermProject_wantWith[nowStudent];

	if (TermProject_teamSelected[wantWith] )
	{
		TermProject_notTeam-=2;
		return wantWith;
	}
	else if (wantWith == nowStudent)
	{
		TermProject_notTeam--;
		return -1;
	}

	TermProject_teamSelected[nowStudent] = true;

	int teamNumber = TermProject_visited[wantWith] ? -1 :  TermProject_MakeTeam(wantWith);

	TermProject_teamSelected[nowStudent] = false;

	if (teamNumber == -1) return -1;
	else if (teamNumber == nowStudent)
	{
		return -1;
	}
	else
	{
		TermProject_notTeam--;
		return teamNumber;
	}
}


int TermProject()
{
	int T,N;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		TermProject_notTeam = N;
	
		for (int i = 1; i <= N; i++)
		{
			TermProject_visited[i] = false;
			cin >> TermProject_wantWith[i];
		}

		for (int i = 1; i <= N; i++)
		{
			if (TermProject_visited[i]) continue;
			TermProject_MakeTeam(i);
		}

		cout << TermProject_notTeam << endl;
	}

	return 0;
}