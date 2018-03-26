#pragma once
#include<iostream>
#include<vector>

using namespace std;
int startCheck(const vector<char> &map , vector<char>  ::iterator &iter)
{
	int state = 0;
	const int ONE1 = 0;
	const int ZERO = 1;
	const int ONE2 = 2;
	const int END = -1;
	int result = -1;
	int oneCnt = 1, oneCnt2 = 0;
	int zeroCnt = 0;
	int info[5][4][5];
	info[2][1][1] = 0;
	info[2][2][1] = 1;
	info[1][2][2] = 2;
	info[4][1][1] = 3;
	info[1][3][2] = 4;
	info[2][3][1] = 5;
	info[1][1][4] = 6;
	info[3][1][2] = 7;
	info[2][1][3] = 8;
	info[1][1][2] = 9;

	while (state != END)
	{
		switch (state)
		{
		case ONE1:
			if (*iter == '1')
			{
				oneCnt++;
			}
			else
			{
				zeroCnt++;
				state = ZERO;
			}
			break;
		case ZERO:
			if (*iter == '0')
			{
				zeroCnt++;
			}
			else
			{
				oneCnt2++;
				state = ONE2;
			}
			break;

		case ONE2:
			if (*iter == '1')
			{
				oneCnt2++;
			}
			else
			{
				state = END;
			}
			break;
		}
		iter++;
	}

	iter--;
	return info[oneCnt][zeroCnt][oneCnt2];
}

int ValidCheck(const vector<int> &vals)
{
	int result = 0;

	int check = 0;
	for (int i = 0; i < 8; i++)
	{
		check += vals[i];
	}

	result = check;

	for (int j = 0; j < 8; j += 2)
	{
		check += vals[j] << 1;
	}

	if (check % 10 == 0)  return result;
	else return 0;
}


void SW1_1()
{
	vector<vector<char> > map;
	vector<int> nums;

	const int ZERO = (1 << 3) + (1 << 2) + 1;
	const int ONE = (1 << 4 )+ (1 << 3) + 1;
	const int TWO = (1 << 4) + (1 << 1) + 1;
	const int THREE = (1 << 5) + (1 << 4) + (1 << 3) + (1 << 2) + 1;
	const int FOUR = (1 << 5) + (1 << 1) + 1;
	const int FIVE = (1 << 5) + (1 << 4) + 1;
	const int SIX = (1 << 5) + (1 << 3) + (1 << 2) + (1<< 1) + 1;
	const int SEVEN = (1 << 5) + (1 << 4) + (1 << 3) + (1 << 1) + 1;
	const int EIGHT = (1 << 5) + (1 << 4) + (1 << 2) + (1 << 1) + 1;
	const int NINE = (1 << 3) + (1 << 1) + 1;

	int K;

	cin >> K;


	//init
	for (int k = 1; k <= K; k++)
	{
		int rows, cols;
		int num = 0;
		cin >> rows >> cols;
		map.clear();
		nums.clear();
		map.resize(rows);

		for (int i = 0; i < rows; i++)
		{
			map[i].resize(cols,10 );

			for (int j = 0; j < cols; j++)
			{
				cin >> map[i][j];
			}
		}

		bool StartEnd = false;
		int start;
		vector<char>::iterator iter;
		for (int i = 0; i < rows; i++)
		{
			for (iter = map[i].begin(); iter != map[i].end(); iter++)
			{
				if (*iter == '1')
				{
					start = startCheck(map[i], ++iter);
					StartEnd = true;
					break;
				}
			}

			if (StartEnd) break;
		}

		nums.push_back(start);
		int checkNum = 0;
		for (int i = 0; i < 7; i++)
		{
			char temp;
			for (int j = 0; j < 7; j++)
			{
				temp = *iter;
				checkNum = (checkNum << 1) + (int)(temp-'0');
				 iter++;
			}

			switch (checkNum)
			{
			case ONE:
				nums.push_back(1);
				break;
			case TWO:
				nums.push_back(2);
				break;
			case THREE:
				nums.push_back(3);
				break;
			case FOUR:
				nums.push_back(4);
				break;
			case FIVE:
				nums.push_back(5);
				break;
			case SIX:
				nums.push_back(6);
				break;
			case SEVEN:
				nums.push_back(7);
				break;
			case EIGHT:
				nums.push_back(8);
				break;
			case NINE:
				nums.push_back(9);
				break;

			case ZERO:
				nums.push_back(0);
				break;

			default: 
				cout << "ErroR\n";
				break;
			}
			checkNum = 0;
		}


		cout << "#" << k << " " << ValidCheck(nums)<<endl;


	}


}