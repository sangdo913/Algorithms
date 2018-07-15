#pragma once
#include<cstdio>
#include<cstring>

double p[50][50] = { 0 };
int len[50], num[10],n, maxLen;
double res[50];
double W[200][200], tw[200][200]; //W : 슬라이딩 윈도우
double cw[200][200];

void initW() {
	memset(W, 0, sizeof(W));

	for (int i = 0, imax = (maxLen -1) * n; i < imax; i++) {
		W[i][i + n] = 1;
	}

	//슬라이딩 윈도우 행렬
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			W[(maxLen - 1)*n + i][(maxLen - len[j]) * n + j] = p[j][i];
		}
	}
}

void mul(double W1[200][200], double W2[200][200]) {
	double result[200][200] = { 0 };
	
	for (int i = 0, imax = maxLen * n; i < imax; i++) {
		for (int j = 0, jm = maxLen * n; j < jm; j++) {
			result[i][j] = 0;

			for (int k = 0, km = maxLen * n; k < km; k++) {
				result[i][j] += W1[i][k] * W2[k][j];
			}
		}
	}

	memcpy(W1, result, sizeof(result));
}

void pow(int n) {
	if (n == 0) {
		return;
	}

	if (n == 1) {
		memcpy(tw, W, sizeof(W));
		return;
	}

	pow(n / 2);
	memcpy(cw, W, sizeof(W));
	
	mul(W, cw);
	if (n & 1) {
		mul(W, tw);
	}
}

int max(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int GENIUS() {
	int t;
	scanf("%d\n", &t);
	
	while (t--) {
		int k, m;

		maxLen = 0;
		scanf("%d %d %d\n", &n, &k, &m);

		for (int i = 0; i < n; i++) {
			scanf("%d \n", &len[i]);
			res[i] = 0;
			maxLen = max(maxLen, len[i]);
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%lf \n", &p[i][j]);
			}
		}
		for (int i = 0; i < m; i++) {
			scanf("%d \n", &num[i]);
		}

		initW();
		pow(k);

		for (int i = 0; i < m; i++) {
			int ri = num[i];

			for (int st = 0; st < len[num[i]]; st++) {
				res[i] += W[(maxLen - st - 1)*n + ri][(maxLen - 1)*n];
			}
		}

		for (int i = 0; i < m; i++) printf("%.8lf ", res[i]);
		printf("\n");
	}

	return 0;
}