//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//#include<vector>
//using namespace std;
//
//#define maxs_times 540
//int N, M, W[36][36], times[36], star[36], maxs;
//char type[36];
//bool visit[36];
//vector<vector<int> >info;
//void init() {
//	maxs = 0;
//	info.clear();
//	for (int i = 0; i < 36; i++) {
//		times[i] = star[i] = type[i] = 0;
//		visit[i] = false;
//		for (int j = 0; j < 36; j++) {
//			W[i][j] = 0;
//		}
//	}
//}
//int nearhotel(int location) {
//	int min = 241, near;
//	for (int k = 1; k <= N; k++) {
//		if ((type[k] == 'H') && (min > W[location][k])) {
//			min = W[location][k];
//			near = k;
//		}
//	}
//	return near;
//}
//
//void dfs(vector<int> f, int ttimes, int tstar, int day) {
//	int from = f.back();
//	visit[from] = true;
//	if (maxs < tstar) {
//		maxs = tstar;
//		info[day] = f;
//	}
//	for (int next = 1; next <= N; next++) {
//		if (next != from && type[next] == 'P' && !visit[next]) {
//			int ntimes = ttimes + W[from][next] + times[next];
//			int nstar = tstar + star[next];
//			bool flag;
//			if (day == M - 1) flag = ((ntimes + W[next][1]) <= maxs_times);
//			else flag = ((ntimes + W[from][nearhotel(next)]) <= maxs_times);
//			if (flag) {
//				f.push_back(next);
//				dfs(f, ntimes, nstar, day);
//				visit[next] = false;
//				f.pop_back();
//			}
//		}
//	}
//}
//int main() {
//	int T;
//	//freopen("sample_input.txt", "r", stdin);
//	cin >> T;
//
//	for (int tc = 1; tc <= T; tc++) {
//		int ans = 0;
//		cin >> N >> M;
//		info = vector<vector<int> >(M);
//		for (int i = 1; i <= N - 1; i++) {
//			for (int j = i + 1; j <= N; j++) {
//				int t;
//				cin >> t;
//				W[i][j] = W[j][i] = t;
//			}
//		}
//		for (int i = 1; i <= N; i++) {
//			cin >> type[i];
//			if (type[i] == 'A') continue;
//			else if (type[i] == 'P') {
//				cin >> times[i] >> star[i];
//				continue;
//			}
//			else if (type[i] == 'H') continue;
//		}
//		vector<int> start;
//		start.push_back(1);
//		int day = 0;
//		while (day < M) {
//			dfs(start, 0, 0, day);
//			start.erase(start.begin(), start.end());
//			if (maxs == 0) break;
//			ans += maxs;
//			maxs = 0;
//
//			start.push_back(nearhotel(info[day].back()));
//			for (int i = 0; i < info[day].size(); i++) {
//				visit[info[day][i]] = true;
//			}
//			day++;
//		}
//
//
//		cout << "#" << tc << " " << ans << " ";
//		if (ans == 0) { cout << endl; continue; }
//		
//		for (int i = 0; i < info.size(); i++) {
//			for (int j = 1; j < info[i].size(); j++) {
//				cout << info[i][j] << " ";
//			}
//			cout << 1;
//		}
//
//		cout << endl;
//		init();
//
//	}
//	return 0;
//}