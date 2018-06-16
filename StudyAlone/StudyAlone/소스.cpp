#include"NUMB3RS.h"

int main()
{
	NUMB3RS();
	
	return 0;
}
//#include<cstdio>
//#include<cstring>
//int town[51][51];
//int q[51], ways[51];
//int n, d, p;
//double cache[51][101];
//double numbers(int townNumber, int days) {
//	if (!days) return (townNumber == p ? 1.0 : 0.0);
//	double& ret = cache[townNumber][days];
//	if (ret != 2) return ret;
//	ret = 0;
//	for (int j = 0; j<n; j++)
//		if (town[townNumber][j]) ret += numbers(j, days - 1) / ways[j];
//	return ret;
//}
//
//int main() {
//	int c;
//	scanf("%d", &c);
//	while (c--) {
//		memset(town, false, sizeof(town));
//		memset(ways, 0, sizeof(ways));
//		scanf("%d %d %d", &n, &d, &p);
//
//		for (int i = 0; i < n; i++)
//		{
//			for(int j = 0; j <= d; j++)
//
//				cache[i][j] = 2;
//		}
//
//		for (int i = 0; i<n; i++) {
//			for (int j = 0; j<n; j++) {
//				scanf("%d", &town[i][j]);
//				if (town[i][j]) ways[i] += 1;
//			}
//		}
//		int t;
//		scanf("%d", &t);
//		for (int i = 0; i<t; i++) scanf("%d", &q[i]);
//		for (int i = 0; i<t; i++) {
//			if (i == t - 1) printf("%.10lf", numbers(q[i], d));
//			else printf("%.10lf ", numbers(q[i], d));
//		}
//		printf("\n");
//	}
//	return 0;
//}