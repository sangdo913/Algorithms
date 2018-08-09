#pragma once
#include<cstdio>
#include<vector>

using namespace std;

int idxes[1001];
int grade[1001];
int temp[1001];
int pos;
void merge(int left, int right) {
	if (left < right) {
		int m = (left + right) / 2;

		merge(left, m);
		merge(m + 1, right);

		int l = left, r = right, k = left;

		while (l <= m && r <= right) {
			if (grade[idxes[l]] == grade[idxes[r]]) {
				temp[k++] = idxes[l] < idxes[r] ? idxes[l++] : idxes[r++];
				continue;
			}

			temp[k++] = grade[idxes[l]] > grade[idxes[r]] ? idxes[l++] : idxes[r++];
		}
		while (l <= m) temp[k++] = idxes[l++];
		while (r <= right) temp[k++] = idxes[r++];
		for (int i = left; i <= right; i++) {
			idxes[i] = temp[i];
			if (idxes[i] == 1) pos = i;
		}
	}
}
int CodeForce502A(){
	int n;
	scanf("%d\n", &n);
	
	for (int i = 1; i <= n; i++) {
		int scores[4];
		idxes[i] = i;
		scanf("%d %d %d %d\n", scores, scores + 1, scores + 2, scores + 3);
		grade[i] = scores[0] + scores[1] + scores[2] + scores[3];
	}

	merge(1, n);

	printf("%d\n", pos);
	return 0;

}