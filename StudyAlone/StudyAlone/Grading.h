#pragma once
#include<iostream>
#include<algorithm>

using namespace std;

int Grading_grade[101];
int Grading_scores[101];

class Grading_MyComp
{
public:
	bool operator()(int i1, int i2)
	{
		return Grading_scores[i1] > Grading_scores[i2];
	}
};

int Grading()
{
	const char Degree[10][3] = { "A+", "A0", "A-", "B+", "B0", "B-", "C+", "C0", "C-", "D0" };
	int t;
	cin >> t;

	for (int tc = 1; tc <= t; tc++)
	{
		int n, id;
		cin >> n >> id;
		for (int i = 1; i <= n; i++)
		{
			Grading_grade[i] = i;
		}

		for (int i = 1; i <= n; i++)
		{
			int total = 0;
			int score;
			cin >> score;
			total += score * 35;
			
			cin >> score;
			total += score * 45; 

			cin >> score;
			total += score * 20;

			Grading_scores[i] = total;
		}

		sort(Grading_grade, Grading_grade + n + 1, Grading_MyComp());
		int grading[101];
		for (int i = 0; i < n; i++)
		{
			grading[Grading_grade[i]] = i;
		}
		cout << '#' << tc << ' ' << Degree[grading[id] / (n / 10)] << '\n';
	}

	return 0;
}