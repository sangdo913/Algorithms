#pragma once
#include<cstdio>
#include<cstring>

using namespace std;

int div[20][1 << 15][2] , len, m;
//e : 입력, digit : 정렬된 e
char e[16], digit[16], temp[16];
const int MOD = 1000000007;

int getLen()
{
	int i;
	for (i = 0; e[i]; i++);
	return i;
}

void mergeSort(int left, int m, int right)
{
	int l = left, r = m + 1, k = left;

	while (l <= m && r <= right)
	{
		if (digit[l] < digit[r]) temp[k++] = digit[l++];
		else temp[k++] = digit[r++];
	}

	while (l <= m) temp[k++] = digit[l++];
	while (r <= right) temp[k++] = digit[r++];

	for (int i = left; i <= right; i++) digit[i] = temp[i];
}

void merge(int left, int right)
{
	if (left < right)
	{
		int m = (left + right) / 2;
		merge(left, m);
		merge(m + 1, right);
		mergeSort(left, m, right);
	}
}

int setDiv(int index, int mod, int selected, bool lower)
{
	if(index == len){
		return lower && (mod == 0);
	}

	int &ret = div[mod][selected][lower];
	if (ret != -1) return ret;

	ret = 0;

	for (int next = 0; next < len; next++) {
		if (selected & (1 << next)) continue; //이미 선택된 인덱스 금지
		if (next != 0 && digit[next - 1] == digit[next] && ((selected & (1 << (next-1))) == 0)) continue; // 중복 선택 금지
		if (!lower && e[index] < digit[next]) continue; // 이미 작지 않은 상태인데 더 큰거 선택 금지

		int ns = selected | (1 << next);
		int nl = lower || (e[index] > digit[next]);
		int nm = (mod * 10 + digit[next] - '0') % m;

		ret += setDiv(index + 1, nm, ns, nl);
		ret %= MOD;
	}

	return ret;
}

int ZIMBABWE()
{
	int tc;
	scanf("%d\n", &tc);

	while (tc--)
	{
		scanf("%s %d\n", e, &m);

		memset(div, -1, sizeof(div));

		len = getLen();
		memcpy(digit, e, sizeof(e));

		merge(0, len -1);
		int res = setDiv(0, 0, 0, 0);
		printf("%d\n", res);
	}
	return 0;
}