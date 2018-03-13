#include<iostream>
#include<vector>
#include<deque>
using namespace std;
vector<pair<int, int>> vec;
vector<bool> visit;
deque<int> dq;
int N;
void req(int n, int dir)
{
	printf("%d --", n);
	if (dq.size() >= N)return;
	else {
		for (int i = 0; i<N; i++)
		{
			if (!visit[i] && n != i)
			{
				if (dir == -1 && vec[n].first == vec[i].second)
				{
					printf(" left %d left ", i);
					dq.push_front(i);
					visit[i] = true;
					req(i, -1);
					visit[i] = false;
					//dq.pop_front();
				}
				else if (dir == 1 && vec[n].second == vec[i].first)
				{
					printf(" right %d right ", i);
					dq.push_back(i);
					visit[i] = true;
					req(i, 1);
					visit[i] = false;
					//  dq.pop_back();
				}
			}
		}
	}
}
int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 0; t<T; t++)
	{
		scanf("%d", &N);
		vec.clear();
		for (int n = 0; n<N; n++)
		{
			int a, b;
			scanf("%d %d", &a, &b);
			vec.push_back(make_pair(a, b));
			visit.push_back(false);
		}
		dq.clear();
		dq.push_back(0);
		visit[0] = true;
		req(0, 1);
		req(0, -1);
		printf("#%d ", t + 1);
		for (int i = 0; i<dq.size(); i++)printf("%d %d ", vec[dq[i]].first, vec[dq[i]].second);
		printf("\n");
	}
}


//#pragma once
//
//#include <iostream>
//
//using namespace std;
//int Winner_predict() {
//
//	int Case;
//
//	freopen("input.txt", "r", stdin);
//	setbuf(stdout, NULL);
//	scanf("%d", &Case);
//
//	for (int tc = 1; tc <= Case; tc++) {
//		long long N_int;
//		scanf("%lld", &N_int);
//		long long input = N_int;
//		N_int = (N_int) / 2 + 1;
//		int cnt = 0;
//		while (N_int != 1 && N_int != 2) {
//
//			if (cnt % 2 == 1 && N_int % 2 == 1) {
//				N_int /= 2;
//				N_int++;
//			}
//			else {
//				N_int /= 2;
//			}
//			cnt++;
//		}
//		if (input != 1 && cnt % 2 == 0 && N_int == 2) printf("#%d Alice\n", tc);
//		else if (input != 1 && cnt % 2 == 0 && N_int == 1) printf("#%d Alice\n", tc);
//		else if (input != 1 && cnt % 2 == 1 && N_int == 1)  printf("#%d Alice\n", tc);
//		else printf("#%d Bob\n", tc);
//	}
//	return 0;
//}
//
//
////#include <stdio.h>
////int main(void)
////{
////	int test_case;
////	int T;
////	setbuf(stdout, NULL);
////	scanf("%d", &T);
////	for (test_case = 1; test_case <= T; ++test_case)
////	{
////		long long int N, Temp = 8, R;
////		int n = 0;
////		scanf("%lld", &N);//1/4/4/16/16/64/64... 1 8 32 128
////		printf("#%d ", test_case);
////		R = 0;
////		while (N>R + 1)
////		{
////			R += Temp;
////			Temp *= 4;
////			n++;
////		}
////		if (N == 1)N++;
////		N = N - R - 1 + (Temp / 4);
////		if (N <= (Temp / 8))printf("Alice\n");
////		else  printf("Bob\n");
////	}
////	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
////}
////
////
//////#include<stdio.h>
//////#include<malloc.h>
//////int *student;
//////int *visit;
//////int *first;
//////
//////int dfs(int start, int current, int cnt) {//시작번호, 현재학생번호, 지나간 학생 수
//////
//////	if (visit[current]) {
//////		if (first[current] != start)
//////			return 0;
//////		return cnt - visit[current];//그룹을 만든 학생 수
//////	}
//////	first[current] = start;
//////	visit[current] = cnt;
//////	return dfs(start, student[current], cnt + 1);
//////}
//////
//////int main() {
//////
//////	int T;
//////	scanf("%d", &T);
//////
//////	int N;
//////	for (int testCase = 0; testCase < T; testCase++)
//////	{
//////		scanf("%d", &N);
//////
//////		student = (int*)malloc(sizeof(int)*(N + 1));
//////		visit = (int*)malloc(sizeof(int)*(N + 1));
//////		first = (int*)malloc(sizeof(int)*(N + 1));
//////
//////		for (int i = 1; i <= N; i++)
//////		{
//////			scanf("%d", &student[i]);
//////			visit[i] = 0;
//////		}
//////		int ans = 0;
//////		for (int i = 1; i <= N; i++) {
//////			if (!visit[i]) {
//////				ans += dfs(i, i, 1);
//////			}
//////		}
//////		printf("%d\n", N - ans);
//////	}
//////	return 0;
//////}
//////
//////
//////
////////#include <iostream>
////////#include <algorithm>
////////#include <vector>
////////#include <cstring>
////////using namespace std;
////////
////////int t, n, m;
////////int dist[100001];
////////int p[100001];
////////void swap(int &a, int &b)
////////{
////////	int tmp = a;
////////	a = b;
////////	b = tmp;
////////}
////////int find(int a)
////////{
////////	if (p[a] < 0) return a;
////////	dist[a] += dist[p[a]];
////////	int res = p[a] = find(p[a]);
////////	return res;
////////
////////}
////////
////////bool merge(int a, int b, int diff)
////////{
////////	int pa = find(a);
////////	int pb = find(b);
////////	if (pa == pb) return true;
////////
////////	if (p[pa] < p[pb])
////////	{
////////		swap(a, b);
////////		swap(pa, pb);
////////		diff = -diff;
////////	}
////////	dist[pa] = dist[b] + diff - dist[a];
////////	p[pb] += p[pa];
////////	p[a] = pb;
////////
////////	return false;
////////}
////////
////////int main()
////////{
////////	ios::sync_with_stdio(false);
////////	cin.tie(0);
////////	//freopen("input.txt", "r", stdin);
////////	//freopen("output.txt", "w", stdout);
////////	cin >> t;
////////	for (int testcase = 1; testcase <= t; testcase++)
////////	{
////////		cin >> n >> m;
////////		cout << "#" << testcase << " ";
////////		memset(dist, 0, sizeof(dist));
////////		memset(p, -1, sizeof(p));
////////		for (int i = 0; i < m; i++)
////////		{
////////			char tmp;
////////			cin >> tmp;
////////			if (tmp == '!')
////////			{
////////				int a, b, d;
////////				cin >> a >> b >> d;
////////				merge(a, b, d);
////////			}
////////			else {
////////				int a, b;
////////				cin >> a >> b;
////////				if (find(a) != find(b)) cout << "UNKNOWN ";
////////				else
////////				{
////////					cout << -dist[b] + dist[a] << " ";
////////				}
////////			}
////////		}
////////		cout << "\n";
////////
////////	}
////////}
////////
///////////*
//////////sw expert 1798
//////////*/
//////////
//////////#include <iostream>
//////////#include <stack>
//////////#include <vector>
//////////using namespace std;
//////////
//////////struct str {
//////////	char pos;
//////////	int cost = 0;
//////////	int happy = 0;
//////////};
//////////int Travel_Time[35][35] = { 0 };
//////////str info[35];
//////////int visited[35] = { 0 };
//////////int m;
//////////int n;
//////////int MAX_happy = 0;
//////////int result_day;
//////////vector<int> result;
//////////void DFS(vector<int> a, int num, int cost, int day, int happy);
//////////bool ispromising(int x, int y, int cost, int day);
//////////
//////////int main() {
//////////	ios::ios_base::sync_with_stdio(false);
//////////	int Case;
//////////
//////////	int temp;
//////////	char Class;
//////////	int Cost, Happy;
//////////
//////////	cin >> Case;
//////////	for (int c = 0; c <Case; c++) {
//////////
//////////		cin >> n >> m;
//////////
//////////		for (int i = 0; i < n; i++) {
//////////			for (int j = i + 1; j < n; j++) {
//////////				cin >> temp;
//////////				Travel_Time[i][j] = temp;
//////////				Travel_Time[j][i] = temp;
//////////			}
//////////		}
//////////		for (int i = 0; i < n; i++) {
//////////			Travel_Time[i][i] = 10000;
//////////		}
//////////		/*
//////////		for (int i = 0; i < n; i++) {
//////////		for (int j = 0; j < n; j++) {
//////////		cout << Travel_Time[i][j] << " ";
//////////		}
//////////		cout << "\n";
//////////		}*/
//////////
//////////		for (int i = 0; i < n; i++) {
//////////			cin >> Class;
//////////			if (Class == 'A' || Class == 'H') {
//////////				info[i] = { Class, 0, 0 };
//////////				continue;
//////////			}
//////////			cin >> Cost >> Happy;
//////////			info[i] = { Class, Cost, Happy };
//////////		}
//////////		/*
//////////		for (int i = 0; i < n; i++) {
//////////		cout << i + 1 << " : " << info[i].pos << " " << info[i].cost << " " << info[i].happy << '\n';
//////////
//////////		}*/
//////////		MAX_happy = 0;
//////////		result_day = 0;
//////////		vector <int> a;
//////////		a.push_back(0);
//////////		visited[0] = 1;
//////////		DFS(a, 0, 0, 0, 0);
//////////		//cout << "관광 날짜 : " << result_day + 1 << "\n";
//////////		//cout << "최대 만족도 : " << MAX_happy << "\n";
//////////		cout << "#" << c + 1 << " " << MAX_happy << " ";
//////////		for (int i = 1; i < result.size(); i++) {
//////////			cout << result[i] + 1 << " ";
//////////		}
//////////		cout << "\n";
//////////		result.clear();
//////////
//////////	}
//////////
//////////
//////////
//////////
//////////}
//////////
//////////
//////////void DFS(vector<int> a, int num, int cost, int day, int happy) {
//////////
//////////	//Stack a = Stack(40);
//////////	int new_cost;
//////////	int current_happy;
//////////
//////////	for (int i = 1; i < n; i++) {
//////////
//////////		new_cost = cost + Travel_Time[num][i] + info[i].cost;
//////////
//////////		if (ispromising(num, i, new_cost, day)) {
//////////
//////////			visited[i] = 1;
//////////			a.push_back(i);
//////////			current_happy = happy + info[i].happy;
//////////
//////////			if (info[i].pos == 'H') {
//////////				visited[i] = 0;
//////////				new_cost = 0;
//////////				day++;
//////////			}
//////////			else {
//////////				if (day == m - 1 && new_cost + Travel_Time[i][0] <= 540) {
//////////					if (MAX_happy < current_happy) {
//////////						MAX_happy = current_happy;
//////////						result = a;
//////////						result_day = day;
//////////						result.push_back(0);
//////////						//cout << "=======================\n";
//////////						//cout << "중간 코스트 : " << new_cost << "\n";
//////////						//cout << "중간 관광 날짜 : " << result_day + 1 << "\n";
//////////						//cout << "중간 만족도 : " << MAX_happy << "\n";
//////////						//cout << "중간 경로 : ";
//////////						//for (int i = 1; i < a.size(); i++) {
//////////						//   cout << a[i] + 1 << " ";
//////////						//}
//////////						//cout << "\n";
//////////						//cout << "=======================\n";
//////////					}
//////////				}
//////////			}
//////////			DFS(a, i, new_cost, day, current_happy);
//////////			if (info[i].pos == 'H') {
//////////				day--;
//////////			}
//////////			a.pop_back();
//////////			visited[i] = 0;
//////////		}
//////////
//////////
//////////	}
//////////}
//////////bool ispromising(int x, int y, int cost, int day) {
//////////
//////////	if ((cost <= 540) && !visited[y]) {
//////////
//////////		if (day != m - 1) {
//////////			if (cost == Travel_Time[x][y]) return 0; // 호텔 -> 호텔 or 공항 -> 호텔
//////////			if (cost < 400 && info[y].pos == 'H') return 0;
//////////			else {
//////////				return 1;
//////////			}
//////////
//////////		}
//////////		else { // 당일에는
//////////			if (info[y].pos == 'H') return 0;
//////////			else {
//////////				return 1;
//////////			}
//////////		}
//////////	}
//////////	return 0;
//////////
//////////}