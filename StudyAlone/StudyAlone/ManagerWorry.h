//https://www.swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWR8UbE6-1ADFAUr

#include<cstdio>
#include<cstring>

/////////////
#include<stdlib.h>
#include<time.h>
////////////

struct info {
	int rate, team;
};
info rate[201];
info temp[201];

int ind[2][10000];
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
		ind[temp[i].team][len[temp[i].team]++] = temp[i].rate;
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
long long pro[201][101][101];
int size[2];

////////////////////
long long all[101];

void swap(int &i1, int &i2, int *ind) {
	int temp = ind[i1];
	ind[i1] = ind[i2];
	ind[i2] = temp;
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
			//printf("%d ", idx[i]);
		}
		int w = 0;

		for (int i = 0; i < right; i++) {
			w += ind[0][i] > ind[1][i];
			//printf("%c ", ind[0][i] > ind[1][i] ? 'W' : 'L');
		}
		all[w]++;
		//printf("\n");
	}

	for (int i = depth; i < right; i++) {
		RR(depth, i, idx);
		p(idx, depth + 1, right);
		LR(depth, i, idx);
	}
}

//////////////////////

int ManagerWorry() {
	int t;
	scanf("%d\n", &t);
	//////////////
	srand(time(NULL));
	///////////////
	//t = 10;
	for (int tc = 1; tc <= t; tc++) {
		int n;
		scanf("%d\n", &n);

		//n = 3;

		memset(ind, 0, sizeof(ind));

		int t;

		

		for (int i = 1; i <= n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 0;
		//	rate[i].rate = rand() % 10000;
		}
		for (int i = n + 1; i <= 2 * n; i++) {
			scanf("%d\n", &t);
			rate[i].rate = t;
			rate[i].team = 1;
		//	rate[i].rate = rand() % 10000;
		}

		merge(1, 2 * n);
		memset(pro, 0, sizeof(pro));

		memset(all, 0, sizeof(all));
		p(ind[1], 0, n);
		size[0] = size[1] = 0;
		int ex = 0;

		int pt = 0;

		int cnt = 1;
		pro[0][0][0] = 1;


		for (int i = 1; i <= 2 * n; i++) {
			size[rate[i].team]++;

			

			if (size[rate[i].team] < size[rate[i].team ^ 1]) {
				for (int idx = 0; idx <= size[pt]; idx++) {
					for (int j = 0; j <= ex; j++) {
						pro[i][idx][j] = pro[i - 1][idx][j];
					}
					ex--;
				}
				continue;
			}
			else if (size[rate[i].team] == size[rate[i].team ^ 1]) {
				for (int j = 0; j <= size[pt]; j++) {
					for (int k = 0; k <= ex; k++) {
						pro[i][j][0] += pro[i-1][j][k];
						pro[i][j][0] %= MOD;
					}
				}
			}
			else {
				if (size[rate[i].team] - size[rate[i].team ^ 1] == 1) {
					pt = rate[i].team;
					ex = 0;
				}

				if (rate[i].team == pt) {
					ex++;
					if (pt == 0) {
						for (int j = 0; j <= size[pt]; j++) {
							int imax = ex > size[pt] - ex ? size[pt] - ex : ex;
							for (int k = 0; k <= imax; k++) {
								//패 승 초 // 승 초 형식
								//앞 승리 - k + 1, j 그대로 -> j
							
								//앞 패배 - k + 1, j + 1 -> size[pt] - ex -k -j + 2< 0 ?  

								//뒤 전체 k 그대로, j 그대로 -> ex
								//앞 초과 - k 그대로, j 그대로 -> k > size[pt] - ex ? size[pt] - ex : k
								int idx1 = 0, idx2 = 0, idx3 = 0;
								int mi1, mi2;
								mi1 = k > 0 ? k - 1 : 0;
								mi2 = j > 0 ? j - 1 : 0;

								idx1 = j;
								idx2 = size[pt] - ex - mi1 - mi2 < 0 ? 0 : size[pt] - ex - mi1 - mi2 ;
								idx3 = ex;
								idx3 += size[pt] - ex < k ? size[pt] - ex : k;
								pro[i][j][k] = pro[i - 1][j][k] * idx3;
								pro[i][j][k] %= MOD;
								
								if (k) {
									pro[i][j][k] += pro[i - 1][j][k - 1] * (idx1);
									pro[i][j][k] %= MOD;
									if (j) pro[i][j][k] += pro[i - 1][j - 1][k - 1] * (idx2);
									pro[i][j][k] %= MOD;
								}
								
							}
						}
					}
					else {
						for (int j = 0; j <= size[pt]; j++) {
							int imax = ex > size[pt] - ex ? size[pt] - ex : ex;
							for (int k = 0; k <= imax; k++) {
								//패 승 초 // 승 초 형식

								//앞 패배 - k + 1, j + 1 ->  size[pt] - ex - k - j + 2 < 0 ? 0 : size[pt] - ex - k - j + 2 < 0;

								//앞 승리 - k + 1, j 그대로 -> j

								//뒤 전체 k 그대로, j + 1 -> ex
								//앞 초과 k 그대로, j + 1 -> k > size[pt] - ex ? size[pt] - ex : k
								int idx1 = 0, idx2 = 0, idx3 = 0;
								int mi1, mi2;
								mi1 = k > 0 ? k - 1 : 0;
								mi2 = j > 0 ? j - 1 : 0;

								idx1 = size[pt] - ex - mi1 - mi2 < 0 ? 0 : size[pt] - ex - mi1 - mi2 ;
								idx2 = ex - 1 < j ? j - ex + 1 : 0;
								idx3 = ex; 
								idx3 += size[pt] - ex < k ? size[pt] - ex : k;
								if (k) {
									pro[i][j][k] += pro[i - 1][j][k - 1] * (idx2);
									pro[i][j][k] %= MOD;
								}
								if (j) {
									pro[i][j][k] += pro[i - 1][j - 1][k] * idx3;
									pro[i][j][k] %= MOD;
									if (k) {
										pro[i][j][k] += pro[i - 1][j - 1][k - 1] * (idx1);
										pro[i][j][k] %= MOD;
									}
								}
							}
						}
					}

				}
			}
		}

		for(int j = 0; j <= n; j++)
			for (int i = 1; i <= n; i++) {
				pro[2 * n][j][0] += pro[2 * n][j][i];
				pro[2 * n][j][0] %= MOD;
			}

		for (int i = 0; i <= n; i++) {
			if (all[i] != pro[2 * n][i][0]) {
				printf("#%d ", tc);
				printf("false!\n");


				for (int i = 1; i <= n*2; i++) {
					if(rate[i].team == 0) printf("%d ",rate[i].rate);
				}
				printf("\n");
				for (int i = 1; i <= 2*n; i++) {
					if (rate[i].team == 1) printf("%d ", rate[i].rate);
				} printf("\n");
				for (int i = 0; i <= n; i++) {
					printf("%lld ", pro[2 * n][i][0]);
				}
				printf("\n");

				for (int i = 0; i <= n; i++) {
					printf("%lld ", all[i]);
				}
				printf("\n");
				break;
			}
		}
/*
		for (int i = 0; i <= n; i++) {
			printf("%lld ", pro[2*n][i][0]);
		}
		printf("\n");

		for (int i = 0; i <= n; i++) {
			printf("%lld ", all[i]);
		}
		printf("\n");*/
    }
    return 0;
}