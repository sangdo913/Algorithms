///*
//sw expert 1798
//*/
//
//#include <iostream>
//#include <stack>
//#include <vector>
//using namespace std;
//
//struct str {
//	char pos;
//	int cost = 0;
//	int happy = 0;
//};
//int Travel_Time[35][35] = { 0 };
//str info[35];
//int visited[35] = { 0 };
//int m;
//int n;
//int MAX_happy = 0;
//int result_day;
//vector<int> result;
//void DFS(vector<int> a, int num, int cost, int day, int happy);
//bool ispromising(int x, int y, int cost, int day);
//
//int main() {
//	ios::ios_base::sync_with_stdio(false);
//	int Case;
//
//	int temp;
//	char Class;
//	int Cost, Happy;
//
//	cin >> Case;
//	for (int c = 0; c <Case; c++) {
//
//		cin >> n >> m;
//
//		for (int i = 0; i < n; i++) {
//			for (int j = i + 1; j < n; j++) {
//				cin >> temp;
//				Travel_Time[i][j] = temp;
//				Travel_Time[j][i] = temp;
//			}
//		}
//		for (int i = 0; i < n; i++) {
//			Travel_Time[i][i] = 10000;
//		}
//		/*
//		for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//		cout << Travel_Time[i][j] << " ";
//		}
//		cout << "\n";
//		}*/
//
//		for (int i = 0; i < n; i++) {
//			cin >> Class;
//			if (Class == 'A' || Class == 'H') {
//				info[i] = { Class, 0, 0 };
//				continue;
//			}
//			cin >> Cost >> Happy;
//			info[i] = { Class, Cost, Happy };
//		}
//		/*
//		for (int i = 0; i < n; i++) {
//		cout << i + 1 << " : " << info[i].pos << " " << info[i].cost << " " << info[i].happy << '\n';
//
//		}*/
//		MAX_happy = 0;
//		result_day = 0;
//		vector <int> a;
//		a.push_back(0);
//		visited[0] = 1;
//		DFS(a, 0, 0, 0, 0);
//		//cout << "관광 날짜 : " << result_day + 1 << "\n";
//		//cout << "최대 만족도 : " << MAX_happy << "\n";
//		cout << "#" << c + 1 << " " << MAX_happy << " ";
//		for (int i = 1; i < result.size(); i++) {
//			cout << result[i] + 1 << " ";
//		}
//		cout << "\n";
//		result.clear();
//
//	}
//
//
//
//
//}
//
//
//void DFS(vector<int> a, int num, int cost, int day, int happy) {
//
//	//Stack a = Stack(40);
//	int new_cost;
//	int current_happy;
//
//	for (int i = 1; i < n; i++) {
//
//		new_cost = cost + Travel_Time[num][i] + info[i].cost;
//
//		if (ispromising(num, i, new_cost, day)) {
//
//			visited[i] = 1;
//			a.push_back(i);
//			current_happy = happy + info[i].happy;
//
//			if (info[i].pos == 'H') {
//				visited[i] = 0;
//				new_cost = 0;
//				day++;
//			}
//			else {
//				if (day == m - 1 && new_cost + Travel_Time[i][0] <= 540) {
//					if (MAX_happy < current_happy) {
//						MAX_happy = current_happy;
//						result = a;
//						result_day = day;
//						result.push_back(0);
//						//cout << "=======================\n";
//						//cout << "중간 코스트 : " << new_cost << "\n";
//						//cout << "중간 관광 날짜 : " << result_day + 1 << "\n";
//						//cout << "중간 만족도 : " << MAX_happy << "\n";
//						//cout << "중간 경로 : ";
//						//for (int i = 1; i < a.size(); i++) {
//						//   cout << a[i] + 1 << " ";
//						//}
//						//cout << "\n";
//						//cout << "=======================\n";
//					}
//				}
//			}
//			DFS(a, i, new_cost, day, current_happy);
//			if (info[i].pos == 'H') {
//				day--;
//			}
//			a.pop_back();
//			visited[i] = 0;
//		}
//
//
//	}
//}
//bool ispromising(int x, int y, int cost, int day) {
//
//	if ((cost <= 540) && !visited[y]) {
//
//		if (day != m - 1) {
//			if (cost == Travel_Time[x][y]) return 0; // 호텔 -> 호텔 or 공항 -> 호텔
//			if (cost < 400 && info[y].pos == 'H') return 0;
//			else {
//				return 1;
//			}
//
//		}
//		else { // 당일에는
//			if (info[y].pos == 'H') return 0;
//			else {
//				return 1;
//			}
//		}
//	}
//	return 0;
//
//}