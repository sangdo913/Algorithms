﻿#include<cstdio>
#include<cstring>
struct info {
	int rate, team;
};
info rate[201];
info temp[201];
int index[2][10000];

long long permu[101];
long long all[101];
void mergeSort(int le, int m, int ri) {
	int l = le, k = le, r = m + 1;

	while (l <= m && r <= ri) {
		temp[k++] = rate[l].rate < rate[r].rate ? rate[l++] : rate[r++];
	}
	while (l <= m) temp[k++] = rate[l++];
	while (r <= ri) temp[k++] = rate[r++];

	int len[2] = { 0, 0 };
	for (int i = le; i <= ri; i++) {

		rate[i] = temp[i];
		index[temp[i].team][len[temp[i].team]++] = temp[i].rate;
	}
}

void merge(int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		merge(l, m);
		merge(m + 1, r);
		mergeSort(l, m, r);
	}
}

const int MOD = 1000000007;
long long pro[101][101][101];
int size[2];

void swap(int &i1, int &i2, int *index) {
	int temp = index[i1];
	index[i1] = index[i2];
	index[i2] = temp;
}


void RR(int st, int dt, int *idx) {
	int temp = idx[dt];
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
	idx[dt] = temp;
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
		all[w]++;
		printf("\n");
	}

	for (int i = depth; i < right; i++) {
		RR(depth, i, idx);
		p(idx, depth + 1, right);
		LR(depth, i, idx);
	}
}


int main() {
	int t;
	scanf("%d\n", &t);
	permu[0] = 1;
	for (int i = 1; i <= 100; i++) {
		permu[i] = permu[i - 1] * i;
		permu[i] %= MOD;
	}

	for (int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d\n", &n);
		int t;
		for (int i = 1; i <= n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 0;
		}
		for (int i = n + 1; i <= 2 * n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 1;
		}

		merge(1, 2 * n);
		memset(pro, 0, sizeof(pro));
		size[0] = size[1] = 0;
		int ex = 0;

		int cidx = 0, pt = 0;

		pro[0][0][0] = 1;
		memset(pro, 0, sizeof(pro));
		int cnt = 1;
		p(index[1],0, n);

		for (int i = 1; i <= 2 * n; i++) {
			size[rate[i].team]++;

			if (rate[i].team == pt) {
				ex++;

				for (int idx = 0; idx <= cidx; idx++) {
					for (int j = 0; j < ex; j++) {
						pro[i][idx][j] = pro[i - ex][idx][j] * permu[ex];
						pro[i][idx][j] %= MOD;
					}
				}

				if (pt == 0) {
					for (int j = 1; j <= size[pt]; j++) {
						for (int k = 1; k <= ex; k++) {
							//패 승 초 // 승 초 형식
							//k 전, 앞 초과 - k + 1, j 그대로 -> k-1 or size[pt] - ex
							//k 전, 앞 승리 - k + 1, j 그대로 -> j- k or 0

							//k 전, 앞 패배 - k + 1, j + 1 -> size[pt] - ex -k -j + 2 or 0 

							//뒤 초과 - k 그대로, j 그대로 -> ex - k
							//뒤 승   - k 그대로, j 그대로 -> k or j

							int idx1 = 0, idx2 = 0, idx3 = 1;
							idx1 += k - 1 > size[pt] - ex ? size[pt] - ex : k - 1;
							idx1 += j - k > 0 ? j - k : 0;
							idx2 += size[pt] - ex - k - j + 2 > 0 ? size[pt] - ex - k - j + 2 : 0;
							idx3 += k > j ? j : k;
							idx3 += ex - k;
							pro[i][j][k] = pro[i - 1][j][k - 1] * (idx1)+pro[i - 1][j - 1][k] * (idx2)+pro[i - 1][j][k] * idx3;
						}
					}
				}
				else {
					for (int j = 1; j <= size[pt]; j++) {
						for (int k = 1; k <= ex; k++) {
							//패 승 초 // 승 초 형식
							//k 전, 앞 초과 - k + 1, j 그대로 -> k-1 or size[pt] - ex
							//k 전, 앞 패배 - k + 1, j 그대로 -> size[pt] - ex -k -j + 2 or 0 

							//k 전, 앞 승리 - k + 1, j - 1 -> j-k or 0

							//뒤 초과 - k 그대로, j 그대로 -> ex - k

							//뒤 승   - k 그대로, j 그대로 -> k or j

							int idx1 = 0, idx2 = 0, idx3 = 1;
							idx1 += k - 1 > size[pt] - ex ? size[pt] - ex : k - 1;
							idx1 += j - k > 0 ? j - k : 0;
							idx2 += size[pt] - ex - k - j + 2 > 0 ? size[pt] - ex - k - j + 2 : 0;
							idx3 += k > j ? j : k;
							idx3 += ex - k;
							pro[i][j][k] = pro[i - 1][j][k - 1] * (idx1)+pro[i - 1][j - 1][k] * (idx2)+pro[i - 1][j][k] * idx3;
						}
					}
				}
			}
		}


		//for (int i = 1; i <= 2 * n; i++) {
		//	while (rate[i].team == pt) {
		//		size[pt]++;
		//		i++;
		//	}

		//	if (size[pt] > sizeMax) {
		//		for (int j = sizeMax + 1; j <= size[pt]; j++) {
		//			if (pt == 0) {

		//			}
		//		}
		//		sizeMax = size[pt];
		//	}


		//	i--;
		//	pt = rate[i].team;
		//	
		//	if (size[pt] <= sizeMax) continue;

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

		//

		printf("#%d ", tc);
		for (int i = 0; i <= n; i++) {
			printf("%lld ", all[i]);
		}
		printf("\n");
	}
	return 0;
}