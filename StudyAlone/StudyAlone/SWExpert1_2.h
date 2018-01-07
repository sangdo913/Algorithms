//#pragma once
//#include<iostream>
//#include<vector>
//#include<set>
//#include<cmath>
//#include<algorithm>
//
//const int ZERO = (1 << 3) + (1 << 2) + 1;
//const int ONE = (1 << 4) + (1 << 3) + 1;
//const int TWO = (1 << 4) + (1 << 1) + 1;
//const int THREE = (1 << 5) + (1 << 4) + (1 << 3) + (1 << 2) + 1;
//const int FOUR = (1 << 5) + (1 << 1) + 1;
//const int FIVE = (1 << 5) + (1 << 4) + 1;
//const int SIX = (1 << 5) + (1 << 3) + (1 << 2) + (1 << 1) + 1;
//const int SEVEN = (1 << 5) + (1 << 4) + (1 << 3) + (1 << 1) + 1;
//const int EIGHT = (1 << 5) + (1 << 4) + (1 << 2) + (1 << 1) + 1;
//const int NINE = (1 << 3) + (1 << 1) + 1;
//
//int info[5][4][5];
//using namespace std;
//
//int getReulst(const vector<int> &map, vector<int>::iterator &iter, const int gongSize);
//int checkStart(const vector<int> &map, vector<int>::iterator &iter, int &gongSize);
//int getNum(int i1, int i2, int i3, int& gongSize);
//int conv(const char a);
//int validCheck(vector<int>::iterator begin, vector<int> :: iterator end);
//void SW1_2()
//{
//	set<int> s;
//
//	for (int i = 0; i < 5; i++)
//	{
//		for (int j = 0; j < 4; j++)
//		{
//			for (int j2 = 0; j2 < 5; j2++)
//			{
//				info[i][j][j2] = -1;
//			}
//		}
//	}
//	info[2][1][1] = 0;
//	info[2][2][1] = 1;
//	info[1][2][2] = 2;
//	info[4][1][1] = 3;
//	info[1][3][2] = 4;
//	info[2][3][1] = 5;
//	info[1][1][4] = 6;
//	info[3][1][2] = 7;
//	info[2][1][3] = 8;
//	info[1][1][2] = 9;
//
//	int K;
//	cin >> K;
//	for (int k = 1; k <= K; k++)
//	{
//		vector<vector<int> >vals;
//		vector<int> result;
//		
//		int rows, cols;
//
//		cin >> rows >> cols;
//
//		vals.resize(rows);
//
//		for (int i = 0; i < rows; i++)
//		{
//			vals[i].resize(cols);
//			char temp;
//			for (int j = 0; j < cols; j++)
//			{
//				cin >> temp;
//
//				vals[i][j] = conv(temp);
//			}
//		}
//		int gongSize;
//		int cnt = 0;
//		//delete same rows;
//		for (int i = 0; i < rows; i++)
//		{
//			for (int j = 0; j < cols; j++)
//			{
//				if (vals[i][j] != 0)
//				{
//					//cout <<"cnt : " <<++cnt <<  " i: " << i << " j : " << j << endl;
//					int storJ = j;
//
//
//					int sameRows = 0;
//					int sameCols = 0;
//					while (storJ<cols && vals[i][storJ] != 0)
//					{
//						sameCols++;
//						storJ++;
//					}
//
//					storJ = i;
//					while (storJ < rows && vals[storJ][j] != 0 && vals[storJ][j] == vals[i][j])
//					{
//						sameRows++;
//						storJ++;
//					}
//
//					for (int i2 = i + 1; i2 < i+sameRows; i2++)
//					{
//						for (storJ = j; storJ < j+sameCols; storJ++)
//						{
//							vals[i2][storJ] = 0;
//						}
//					}
//
//					j = storJ;
//
//				}
//			}
//		}
//
//
//		for (int i = 0; i < rows; i++)
//		{
//			vector<int>::iterator iter = vals[i].begin();
//			int start = checkStart(vals[i], iter, gongSize);
//			while (start >= 0)
//			{
//				vector<int> tempResult;
//
//				tempResult.push_back(start);
//				for (int j = 0; j < 7; j++)
//				{
//					start = checkStart(vals[i], iter, gongSize);
//					tempResult.push_back(start);
//				}
//;				
//	/*			for (auto it : tempResult) cout << it << " ";
//				cout << endl;*/
//
//				auto iter2 = tempResult.begin();
//				while (iter2 != tempResult.end())
//				{
//
//					int value = validCheck(iter2, iter2 +7);
//					iter2 += 8;
//					result.push_back(value);
//				}
//				start = checkStart(vals[i], iter, gongSize);
//				//if(iter == vals[i].end()) break;
//				
//			}
//		}
//
//		int res = 0;
//		for (auto it : result) res += it;
//		cout << "#" << k << " " << res << endl;
//	}
//
//}
//
//
//
//int getReulst(const vector<int> &map, vector<int>::iterator &iter, const int gongSize)
//{
//
//	return 0;
//}
//int conv(const char a)
//{
//	if (a >= 'a' && a <= 'f')
//	{
//		return a - 'a'+10;
//	}
//
//	else if (a >= 'A' && a <= 'F')
//	{
//		return a - 'A' + 10;
//	}
//
//	else
//		return a - '0';
//}
//
//int reulst(const vector<int> &map, vector<int>::iterator &iter)
//{
//	return 0;
//}
//
//int checkStart(const vector<int> &map, vector<int>::iterator &iter, int &gongSize)
//{
//	int oneCnt = 0, oneCnt2 = 0, zeroCnt = 0;
//
//
//	const int START = 0;
//	const int ONE1 = 1;
//	const int ZERO = 2;
//	const int ONE2 = 3;
//	const int END = -1;
//	int state = START;
//	int cnt = 0, tempCNT = 0;
//
//	while (state != END)
//	{
//		if (iter == map.end() && oneCnt == 0) return -1;
//		//if (*iter == 0 )
//		//{
//		//	if (oneCnt2 > 0) break;
//		//	iter++;
//		//	continue;
//		//}
//
//		switch (state)
//		{
//		case START:
//			if (((*iter) & 8) ==8 )
//			{
//				oneCnt++;
//				state = ONE1;
//			}
//			break;
//
//		case ONE1:
//			if (((*iter) & 8) == 8)
//			{
//				oneCnt++;
//			}
//			else
//			{
//				zeroCnt++;
//				state = ZERO;
//			}
//			break;
//		case ZERO:
//			if (((*iter) & 8) == 0)
//			{
//				zeroCnt++;
//			}
//			else
//			{
//				oneCnt2++;
//				state = ONE2;
//			}
//			break;
//
//		case ONE2:
//			if (((*iter) & 8) == 8 )
//			{
//				oneCnt2++;
//			}
//			else
//			{
//				state = END;
//			}
//			break;
//		}
//		cnt++;
//		*iter = *iter << 1;
//
//		if (cnt == 4)
//		{
//			cnt = 0;
//			*iter = 0;
//			if(iter != map.end()) iter++;
//		}
//	}
//
//	int result = getNum(oneCnt, zeroCnt, oneCnt2, gongSize);
//	*iter  = (*iter & 0xF)>>cnt;
//	return result;
//}
//
//int getNum(int i1, int i2, int i3, int &gongSize)
//{
//	int Min = min(i1,i2);
//	Min = min(Min, i3);
//	int gong;
//	for (int i = 1; i <= Min; i++)
//	{
//		gong = i1%i == 0 && i2%i == 0 && i3%i == 0 ? i : gong;
//	}
//	gongSize = gong;
//	return info[i1/gong][i2/gong][i3/gong];
//}
//
//
//int validCheck(vector<int>::iterator begin, vector<int> ::iterator end)
//{
//	int result = 0;
//	int sum = 0;
//	for (auto iter = begin; iter != end; iter++)
//	{
//		sum += *iter;
//	}
//	sum += *end;
//	result = sum;
//	for (auto iter = begin; iter != (end-1); iter+=2)
//	{
//		sum += *iter << 1;
//	}
//	sum += (*(end - 1) << 1);
//	//if (sum % 10 != 0) cout << result << endl;
//	return (sum %10 == 0 ) ? result : 0;
//}