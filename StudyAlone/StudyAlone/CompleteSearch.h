#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<cmath>
#include<iomanip>

using namespace std;

int getNums(int in)
{
	int Cnt = 0;
	while (in > 0)
	{
		in /= 10;
		Cnt++;
	}

	return Cnt;
}
vector<int> setVector(int num)
{
	int numCnt = getNums(num);

	vector<int> result;

	result.resize(numCnt);

	for (int i = numCnt - 1; i >= 0; i--)
	{
		result[i] = num % 10;
		num /= 10;
	}
	return result;
}

int getResult(const vector<int> nums)
{
	int size = nums.size();
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		int tenCount = 1;
		for (int j = 0; j < size - i - 1; j++) tenCount *= 10;
		result += nums[i] * tenCount;
	}

	return result;
}

void CompleteSearch1()
{
	vector<int> in;
	set<pair<int,int> > checkList;
	int N, result = 0;
	int input_num, input_count;
	int size;
	cin >> N;
	for (int k = 1; k <= N; k++)
	{
		
		stack<pair<vector<int>, int> > que;
		cin >> input_num >> input_count;
		in = setVector(input_num);


		int maxNum = input_num;
		size = in.size();
		que.push(make_pair(vector<int>(in), input_count));

		while (!que.empty())
		{
			int reserve_count = que.top().second;

			in = vector<int>(que.top().first);
			que.pop();

			if (reserve_count == 0)
			{
				maxNum = maxNum < getResult(in) ? getResult(in) : maxNum;
			}


			else if ((reserve_count > 0) && (checkList.find(make_pair(getResult(in), reserve_count)) == checkList.end()))
			{
				for (int i = 0; i < size - 1; i++)
				{
					for (int j = i + 1; j < size; j++)
					{
						vector<int> vector_temp(in);
						vector_temp[i] = in[j];
						vector_temp[j] = in[i];

						que.push(make_pair(vector_temp, reserve_count - 1));
					}
				}


				checkList.insert(make_pair(getResult(in), reserve_count ));
			}
		}


		cout << "#" << k << " " << maxNum << endl;
	}
}

void Print(const vector<int>& vec)
{
	for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout.width(5);
		cout << * it << " ";
	}
	cout << endl;
}

double getForce(const double x1, const double x2, const double m)
{
	return (double)m / (double)(x1 - x2)/(double)(x1 - x2);
}

double BinarySearch(const vector<int> left[2], const vector<int> right[2])
{
	bool isBig;
	bool isEnd = false;

	const int COD = 0;
	const int WEIGHT = 1;

	double minX = *(left[COD].rbegin());
	double maxX = *(right[COD].begin());
	double pos_X;
	double left_F = 0, right_F = 0;
	int left_size = left[COD].size();
	int right_size = right[COD].size();

	while (1)
	{
		pos_X = (minX + maxX) / 2.0f;
		for (int i = 0; i < left_size; i++)
		{
			left_F += getForce(pos_X,(double)left[COD][i],(double)left[WEIGHT][i]);
		}

		for (int i = 0; i < right_size; i++)
		{
			right_F += getForce(pos_X, (double)right[COD][i], (double)right[WEIGHT][i]);
		}

		if (left_F == right_F || maxX-minX < 0.00000000001) break;
		isBig = left_F < right_F;

		if (isBig)
		{
			maxX = pos_X;
		}

		else minX = pos_X;
		left_F = right_F = 0;
	}
	
	return pos_X;
}

double getEPoint(const vector<int> infos[2], int ind)
{
	const int COD = 0;
	const int WEIGHT = 1;
	double result = 0;

	vector<int> left[2];
	vector<int> right[2];
	for (int i = 0; i < 2; i++)
	{
		int j = 0;
		for (; j <= ind; j++)
		{
			left[i].push_back(infos[i][j]);
		}

		for (; j < infos[0].size(); j++)
		{
			right[i].push_back(infos[i][j]);
		}
	}

	//cout << "left" << endl;
	//for (int i = 0; i < 2; i++)
	//{
	//	Print(left[i]);
	//	cout << endl;
	//}

	//cout << "right" << endl;
	//for (int i = 0; i < 2; i++)
	//{
	//	Print(right[i]);
	//	cout << endl;
	//}

	result = BinarySearch(left, right);
	return result;
}

void CompleteSearch2()
{
	const int COD = 0;
	const int WEIGHT = 1;

	int N;
	cin >> N;
	for (int k = 1; k <= N; k++)
	{
		vector<int> Stars[2];
		int temp, cod, wei;
		cin >> temp;
		for (int i = 0; i < temp; i++)
		{
			cin >> cod ;

			Stars[COD].push_back(cod);
		}

		for (int i = 0; i < temp; i++)
		{
			cin >> wei;

			Stars[WEIGHT].push_back(wei);
		}
		cod = Stars[COD].size();
		vector<double> result;
		for (int i = 0; i < cod-1; i++)
		{
			result.push_back(getEPoint(Stars, i));
		}

		cout << "#" << k << " ";
		for (auto it : result)
		{
			cout.setf(ios::fixed);
			cout.precision(10);
			cout << it << " ";
		}
		cout << endl;
	}
}