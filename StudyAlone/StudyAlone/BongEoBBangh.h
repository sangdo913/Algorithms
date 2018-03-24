//#pragma once
//#include<iostream>
//#include<cstdio>
//#include<queue>
//#include<algorithm>
//
//using namespace std;
//int GoldFish_ArriveTime[11112];
//int GoldFish_Fishes[11112];
//
//void GoldFish()
//{
//	int remainBoong = 0;
//	int arrive_time, N, M, K, T;
//	scanf("%d", &T);
//	char result[2][11] = { "Impossible" ,"Possible" };
//	for (int tc = 1; tc <= T; tc++)
//	{
//		scanf("%d %d %d", &N, &M, &K);
//		int i = N;
//		int arrive_time;
//
//		for (int i = 0; i < 11112; i++)
//		{
//			GoldFish_ArriveTime[i] = 0;
//			GoldFish_Fishes[i] = 0;
//		}
//		int max = -1;
//		for (int i = 0; i < N; i++)
//		{
//
//			if (tc == 981)
//			{
//				int x = 0;
//			}
//			scanf("%d", &arrive_time);
//			GoldFish_ArriveTime[arrive_time]++;
//			max = max > arrive_time ? max : arrive_time;
//		}
//
//		for (int i = 1; i <= max; i++)
//		{
//			GoldFish_Fishes[i] += GoldFish_Fishes[i - 1];
//			if (i% M == 0) GoldFish_Fishes[i] += K;
//		}
//
//		for (int i = 1; i <= max; i++)
//		{
//			GoldFish_ArriveTime[i] += GoldFish_ArriveTime[i - 1];
//		}
//		bool ispossible = true;
//		for (int i = 0; i <= max; i++)
//		{
//
//			ispossible = GoldFish_Fishes[i] >= GoldFish_ArriveTime[i];
//			if (!ispossible)
//			{
//				break;
//			}
//		}
//		printf("#%d %s\n", tc, result[ispossible]);
//	}
//}

//
//}
//
//
//
//
//
//
//
//#include <iostream>
//#include <algorithm>
//using namespace std;
//int arr[101] = { 0 };
//
//int main() {
//
//	int Case;
//	freopen("input.txt", "r", stdin);
//	setbuf(stdout, NULL);
//	scanf("%d", &Case);
//
//	for (int tc = 1; tc <= Case; tc++) {
//
//		int N, M, K;
//		int input;
//		int flag = 0;
//		scanf("%d %d %d", &N, &M, &K);
//
//
//		for (int i = 0; i < N; i++) {
//			scanf("%d", &input);
//			arr[i] = input;
//		}
//		sort(arr, arr + N);
//
//		int current_num;
//		for (int i = 0; i < N; i++) {
//			current_num = arr[i] / M * K - i;
//			if (current_num <= 0) {
//				flag = 1;
//			}
//		}
//
//		if (flag == 0) printf("#%d Possible\n", tc);
//		else printf("#%d Impossible\n", tc);
//	}
//
//}
//
#include <iostream>
#include <algorithm>
using namespace std;
int GoldFish()
{
	int test_case;
	int T;
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int N, M, K, t, Bang = 0;
		cin >> N >> M >> K;
		int *arr = new int[N+1];
		cout << "#" << test_case << " ";

		for (int i = 0; i < N; i++)
		{
			cin >> arr[i]; //arrives
		}

		sort(arr, arr + N);
		bool ans = true;
		int tt = 0, bb = 0; //bb 손님 ,시간
		while (tt <= arr[N - 1])
		{
			if (!(bb > 0 && (arr[bb] == arr[bb - 1])))
			{
				tt++;
				if (tt%M == 0)Bang += K;
			}

			if (arr[bb] == tt)
			{
				bb++;
				Bang--;
			}

			if (Bang<0) {
				ans = false;
				break;
			}
			//cout << Bang << endl;
		}
		if (ans)cout << "Possible" << endl;
		else cout << "Impossible" << endl;
		delete(arr);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}