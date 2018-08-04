#include<iostream>

using namespace std;

struct JongMinHambergerClass
{
	double culSumFi[1000005];
	double culSumFiplus1[1000005];
	double relativeLength(int ind1, int ind2)
	{
		return 1.0*(culSumFiplus1[ind1] - culSumFiplus1[ind2]) / (culSumFi[ind2] - culSumFi[ind1]);
	}
	void add(double d1, double d2)
	{
		culSumFi[size] = d1;
		culSumFiplus1[size] = d2;
		while (size >= 2 && relativeLength(size - 2, size-1) > relativeLength(size - 1, size))
		{
			culSumFi[size - 1] = culSumFi[size];
			culSumFiplus1[size - 1] = culSumFiplus1[size];
			size--;
		}
		size++;
	}

	//parametric search
	double findStart(double std)
	{
		int l = 0, r = size - 1;
		int m ;
		while (l != r)
		{
			m = (l + r) >> 1;
			if (relativeLength(m, m + 1) <= std) l = m + 1;
			else r = m;
		}
		return culSumFi[l] * std + culSumFiplus1[l];
	}
	int size;
}JongMin;

double JongMin_people[100005];
double JongMin_difficulty[100005];
double JongMin_culPeople[100005];

int JongMinHamberger()
{
	int T, N, M;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		JongMin.size = 0;
		cin >> N >> M;
		for (int p = 0; p < N; p++) cin >> JongMin_people[p];
		for (int cnt = 0; cnt <M; cnt++)
		{
			cin >> JongMin_difficulty[cnt];
		}

		JongMin_culPeople[0] = 0;
		for (int cnt = 1; cnt <= N; cnt++)
		{
			JongMin_culPeople[cnt] = JongMin_people[cnt - 1] + JongMin_culPeople[cnt - 1];
			JongMin.add(JongMin_culPeople[cnt], -JongMin_culPeople[cnt - 1]);
		}
		
		int ind = 0; 
		
		long long endTime = 0;
		
		for (int i = 0; i < M - 1;  i++)
		{
			double ratio = JongMin_difficulty[i] / JongMin_difficulty[i + 1];
			endTime += (long long)(JongMin.findStart(ratio)*(JongMin_difficulty[i+1])+1e-2);
		}
		endTime += (long long)(JongMin_difficulty[M - 1] * JongMin_culPeople[N]);


		cout << '#' << tc << ' ' << endTime << endl;
	}
	return 0;
}