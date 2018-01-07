#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<map>
using namespace std;

class BeomJoonClass
{
public:
	 const int A = 1;
	 const int P = 0;
	 const int H = 2;
	 const int PT = 3;
	 const int PG = 4;
	 const int I = 5;

	 int CNT;
	 int size;
	 vector<vector<int> > edges;
	 vector<int> info[6];
	map<pair<int, vector<bool> >, int> memoi[5][35];
	map<vector<bool>, pair<int, vector<int> > > h_memoi[5][35];
	 int max_value;
	 vector<int> max_path;
	 vector<int> min_hotel;


	void dfs2(vector<bool> &check, const int &to, int reserved, const int &days, int count, vector<int> &path, int pg)
	{
		CNT++;
		for (int i = 0; i < size; i++)
		{
			if (i == 0 && count != days) continue; //돌아가는 날이 아닌데 공항
			if (reserved + info[PT][i] + edges[to][i] > 540) continue; // 길이 540 이상
			if (check[i])
			{
				//	if(info[I][i] != H)
				continue;// 이미 방문
			}

			// 마지막날
			if (info[I][i] == A)
			{
				path.push_back(i + 1);
				if (max_value < pg)
				{
					max_value = pg;
					max_path.clear();
					max_path.insert(max_path.begin(), path.begin(), path.end());
				}
			}

			else if (info[I][i] == H)
			{
				if (days == count || to == i)
				{
					continue;
				}

				path.push_back(i + 1);
				//check[i] = true;
				dfs2(check, i, 0, days, count + 1, path, pg);
			}

			else
			{
				if (count != days && reserved + info[PT][i] + edges[to][i] + min_hotel[i] > 540)
				{
					continue;
				}
				if (count == days && reserved + info[PT][i] + edges[to][i] + edges[i][0] > 540) {
					continue;
				}
				check[i] = true;

				path.push_back(i + 1);
				dfs2(check, i, reserved + info[PT][i] + edges[to][i], days, count, path, pg + info[PG][i]);
				check[i] = false;
			}

			if (path.begin() != path.end()) path.erase(path.begin() + path.size() - 1);
		}
	}

	//int dfs(vector<bool> check, const int &to, int reserved, const int &days, int count, vector<int> &path)
	//{
	//	if (to == 0 && count == days + 1)
	//	{
	//		return 0;
	//	}

	//	if (memoi[count][to].find(make_pair(to, check)) != memoi[count][to].end()) return memoi[count][to].find(make_pair(to, check))->second;

	//	bool can_do = false;

	//	if (count < days  && reserved + min_hotel[to] > 540) return -350;
	//	else if (count == days && reserved + edges[to][0] > 540) return -350;

	//	int ret = 0;

	//	int size = info[PG].size();
	//	int store;

	//	vector<int> max_path(path);

	//	for (int i = 0; i < size; i++)
	//	{
	//		if (to == 0 && i == 0) continue;
	//		if (count != days  && i == 0) continue;
	//		if (count == days  && info[I][i] == H) continue;
	//		//if (info[I][to] == H && info[I][i] == H) continue;
	//		if (count != days  && reserved + info[PT][i] + edges[to][i] + min_hotel[i] > 540) continue;
	//		if (count == days  && reserved + info[PT][i] + edges[to][i] + edges[i][0] > 540) continue;

	//		int pg = info[PG][i];

	//		if (!check[i] && reserved + info[PT][i] + edges[to][i] <= 540)
	//		{
	//			vector<bool> temp(check);
	//			int next_count = info[I][i] == H ? count + 1 : count;
	//			int next_reserved = info[I][i] == H ? 0 : reserved + info[PT][i] + edges[to][i];
	//			vector<int> next_path;
	//			next_path.push_back(i + 1);

	//			temp[i] = info[I][i] == P;
	//			if (ret < pg + (store = (dfs(temp, i, next_reserved, days, next_count, next_path))))
	//			{

	//				max_path = path;
	//				max_path.insert(max_path.end(), next_path.begin(), next_path.end());
	//				ret = pg + store;
	//				temp[i] = false;

	//				auto tem = make_pair(to, temp);
	//				if (memoi[next_count][to].find(tem) == memoi[next_count][to].end()) memoi[next_count][to].insert(make_pair(tem, ret));
	//				else
	//				{

	//					memoi[next_count][to].find(tem)->second = (memoi[next_count][to].find(tem)->second > ret) ? memoi[next_count][to].find(tem)->second : ret;
	//				}
	//			}
	//		}
	//	}
	//	path.swap(max_path);
	//	return ret;
	//}

	//typedef struct Data {
	//	int node;
	//	int PG;
	//	int PT;
	//	int day;
	//	int flag;
	//	vector<int> path;
	//	vector<bool> check;
	//	vector<bool> visit;
	//} D;

	//int solve(int days)
	//{
	//	stack<D> sta;
	//	vector<bool> visit;
	//	vector<int> path;

	//	int size = edges.size();

	//	visit.resize(size, false);

	//	D start = { 0,0,0,0,A,vector<int>(), vector<bool>(size,false),vector<bool>(size,false) };
	//	sta.push(start);

	//	int max_value = 0;

	//	while (!sta.empty())
	//	{
	//		//CNT++;
	//		bool isPush = false;
	//		/*	if (start.day == days && start.flag == A)
	//			{
	//			}
	//	*/
	//	/// go next node
	//		if (start.day < days - 1)
	//		{
	//			for (int i = 1; i < size && !isPush; i++)
	//			{
	//				if (start.PT + edges[start.node][i] + info[PT][i] + min_hotel[i]> 540) continue;
	//				if (start.PT + edges[start.node][i] + info[PT][i] > 540) continue;
	//				if (i == start.node) continue;
	//				if (start.check[i]) continue;
	//				if (!start.visit[i])
	//				{
	//					isPush = true;
	//					start.check[i] = true;
	//					sta.push(start);
	//					start.flag = info[I][i];
	//					start.path.push_back(i + 1);
	//					for (int i = 0; i < start.check.size(); i++) start.check[i] = false;

	//					if (start.flag == H)
	//					{
	//						start.day++;
	//						start.PT = 0;
	//						start.visit[i] = false;
	//					}
	//					else
	//					{
	//						start.visit[i] = true;
	//						start.PT += info[PT][i] + edges[start.node][i];
	//						start.PG += info[PG][i];
	//					}

	//					start.node = i;
	//				}
	//			}
	//		}

	//		//final day
	//		else
	//		{
	//			for (int i = 0; i < size && !isPush; i++)
	//			{
	//				if (info[I][i] == H) continue;
	//				if (start.PT + edges[start.node][i] + info[PT][i] + edges[i][0] > 540) continue;
	//				if (start.PT + edges[start.node][i] + info[PT][i] > 540) continue;
	//				if (start.check[i]) continue;
	//				if (!start.visit[i])
	//				{
	//					isPush = true;
	//					start.check[i] = true;
	//					sta.push(start);
	//					start.flag = info[I][i];
	//					start.path.push_back(i + 1);
	//					for (int i = 0; i < start.check.size(); i++)start.check[i] = false;

	//					if (start.flag == A)
	//					{
	//						if (start.PG > max_value)
	//						{
	//							max_value = start.PG;
	//							max_path.swap(start.path);
	//						}

	//						start = sta.top();
	//						sta.pop();
	//						isPush = true;
	//					}
	//					else
	//					{
	//						start.visit[i] = true;
	//						start.PT += info[PT][i] + edges[start.node][i];
	//						start.PG += info[PG][i];
	//					}
	//					start.node = i;
	//				}
	//			}
	//		}

	//		if (!isPush)
	//		{
	//			start = sta.top();
	//			sta.pop();
	//		}
	//	}

	//	return max_value;
	//}


	void BeomJoon()
	{
		int N, M, K;

		cin >> K;

		for (int k = 1; k <= K; k++)
		{
			cin >> N >> M;
			CNT = 0;
			size = N;
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 35; j++)
					memoi[i][j].clear();

			max_path.clear();
			for (int i = 0; i < edges.size(); i++)
			{
				edges[i].clear();
			}
			edges.clear();

			for (int i = 0; i < 6; i++) info[i].clear();


			edges.resize(N);
			for (int i = 0; i < N; i++)
			{
				edges[i].resize(N);
			}

			min_hotel.clear();
			min_hotel.resize(N);
			max_value = 0;
			int temp, temp2;
			char temp3;
			//input
			for (int i = 0; i < N; i++)
			{
				for (int j = i + 1; j < N; j++)
				{
					cin >> temp;
					edges[i][j] = temp;
					edges[j][i] = temp;
				}
			}


			for (int i = 0; i < 6; i++)
			{
				info[i].clear();
			}

			for (int i = 0; i < N; i++)
			{
				cin >> temp3;
				switch (temp3)
				{
				case 'A':
					info[A].push_back(i);

					info[PT].push_back(0);
					info[PG].push_back(0);
					info[I].push_back(A);
					break;
				case 'P':
					cin >> temp >> temp2;
					info[PT].push_back(temp);
					info[PG].push_back(temp2);
					info[P].push_back(i);
					info[I].push_back(P);
					break;
				case 'H':
					info[H].push_back(i);
					info[PT].push_back(0);
					info[PG].push_back(0);
					info[I].push_back(H);
					break;
				}
			}

			for (int i = 0; i < N; i++)
			{
				min_hotel[i] = 50000;
				for (int j = 0; j < info[H].size(); j++)
				{
					min_hotel[i] = min_hotel[i] > edges[i][info[H][j]] ? edges[i][info[H][j]] : min_hotel[i];
				}
			}



			vector<bool> ch(info[PG].size(), false);

			vector<int> path;

			dfs2(ch, 0, 0, M, 1, path, 0);
			//max_value = dfs(ch, 0, 0, M, 1, path);
			//max_value = solve(M);
			cout << "#" << k << " " << max_value;
			for (int i = 0; i < max_path.size(); i++)
			{
				cout << " " << max_path[i];
			}

			cout << endl;

			cout << CNT << endl;
		}
	}
};