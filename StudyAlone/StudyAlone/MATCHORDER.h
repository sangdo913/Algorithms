#include<iostream>

using namespace std;

int temp[100];
int russia[100];
int korea[100];
int n;

void mergeSort(int arr[100], int s, int e) {
	int l = s, m = (s +e ) / 2, r = m + 1, k = s;

	while (l <= m && r <= e) temp[k++] = arr[l] < arr[r] ? arr[l++] : arr[r++]; 

	while (l <= m) temp[k++] = arr[l++];
	while (r <= e) temp[k++] = arr[r++];

	for (int i = s; i <= e; ++i) arr[i] = temp[i];
}

void merge(int arr[100], int s, int e) {
	if (s < e) {
		int m = (s + e) / 2;
		merge(arr, s, m);
		merge(arr, m + 1, e);
		mergeSort(arr, s, e);
	}
}

int main() {
	int k;
	int n; 
	cin >> k;
	while (k--) {
		cin >> n;
		for (int i = 0; i < n; ++i) cin >> russia[i];
		for (int i = 0; i < n; ++i) cin >> korea[i];

		merge(russia, 0, n-1);
		merge(korea, 0, n - 1);

		int ki = 0;
		int res = 0;
		for (int ri = 0; ri < n; ++ri) {
			while (ki < n && russia[ri] > korea[ki]) ki++;
			res += ki < n;
			ki++;
		}
		cout << res << '\n';
	}
	return 0;
}