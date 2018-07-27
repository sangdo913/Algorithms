//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWR8UbE6-1ADFAUr

#include<cstdio>
#include<cstring>
struct info {
	int rate, team;
};
info rate[201];
info temp[201];
int index[2][10000];

void mergeSort(int le, int m, int ri) {
	int l = le, k = le, r = m + 1;

	while (l <= m && r <= ri) {
		temp[k++] = rate[l].rate < rate[r].rate ? rate[l++] : rate[r++];
	}
	while (l <= m) temp[k++] = rate[l++];
	while (r <= ri) temp[k++] = rate[r++];

	int len[2] = { 0, 0};
	for (int i = le; i <= ri; i++) {
		
		rate[i] = temp[i];
		index[temp[i].team][len[temp[i].team]++] = temp[i].rate;
	}
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge( m + 1, r);
		mergeSort( l, m, r);
	}
}

const int MOD = 1000000007;
int pro[2][101];
int size[2];

void swap(int &i1, int &i2, int *index) {
	int temp = index[i1];
	index[i1] = index[i2];
	index[i2] = temp;
}


void RR(int st, int dt, int *idx) {
	int temp = idx[dt ];
	for (int i = dt; i >st; i--) {
		idx[i] = idx[i - 1];
	}
	idx[st] = temp;
}

void LR(int st, int dt, int *idx) {
	int temp = idx[st];
	for (int i = st; i < dt; i++) {
		idx[i] = idx[i + 1];
	}
	idx[dt ] = temp;
}

void p(int* idx, int depth, int right) {
	if (depth == right) {
		for (int i = 0; i < right; i++) {
			printf("%d ", idx[i]);
		}
		int w = 0;

		for (int i = 0; i < right; i++) {
			w += index[0][i] > index[1][i];
			printf("%c ", index[0][i] > index[1][i] ? 'W' : 'L');
		}
		pro[0][w]++;
		printf("\n");
	}

	for (int i = depth; i < right; i++) {
		RR(depth, i,idx);
		p(idx, depth + 1, right);
		LR(depth, i,idx);
	}
}



int ManagerWorry(){
    int t;
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++){
		int n;
		scanf("%d\n", &n);
		int t;
		for (int i = 1; i <= n; i++){
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 0;
		}
		for (int i = n+1; i <= 2*n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 1;
		}

		merge(1, 2*n );
		memset(pro, 0, sizeof(pro));
		size[0] = size[1] = 0;

		size[rate[1].team]++;
		pro[0][rate[1].team] = 1;

		memset(pro, 0, sizeof(pro));
		int cnt = 1;
		p(index[1],0, n);

		//for (int i = 2; i <= 2 * n; i++) {
		//	info score = rate[i];
		//	size[score.team]++;
		//	if (size[0] > size[1] && score.team == 0) {
		//		pro[cnt % 2][0] = pro[cnt%2^1][0];

		//		for (int j = 1; j <= size[1]; j++) {
		//			//이전꺼 그대로 냅두면 그대로!
		//			//이전꺼에서 승리한 거랑 바꾸면 승리 그대로!
		//			//이전꺼에서 패배한 거랑 바꾸면 승리 + 1!
		//			pro[cnt % 2][j] = pro[(cnt % 2) ^ 1][j] * (j + 1) + pro[cnt%2^1][j-1] * (size[0] - j + 1);
		//		}
		//		cnt++;
		//	}
		//	else if(size[0] < size[1] && score.team == 1){
		//		pro[cnt % 2][0] = pro[cnt % 2 - 1][0] * size[1];
		//		for (int j = 0; j <= size[0]; j++) { 
		//			//이전꺼에서 승리한 것이랑 바꾸면 승리 -1!
		//			//이전꺼에서 패배한 것이랑 바꾸면 그대로!
		//			//이전꺼에서 그대로 냅두면 그대로!
		//			pro[cnt % 2][j] = pro[(cnt % 2) ^ 1][j]*(size[1] - j) + pro[cnt%2^1][j+1]*(j+1);
		//		}

		//		cnt++;
		//	}
		//	else if(score.team == 0){
		//			for (int i = 1; i < size[0]; i++) {
		//				pro[cnt % 2][i] = pro[cnt % 2][i - 1];
		//			}
		//			pro[cnt % 2][0] = 0;
		//		}
		//}

		

		printf("#%d ", tc);
		for (int i = 0; i <= n; i++) {
			printf("%d ", pro[0][i]);
		}
		printf("\n");
    }
    return 0;
}