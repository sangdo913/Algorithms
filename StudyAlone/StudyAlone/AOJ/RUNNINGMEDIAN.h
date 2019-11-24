#include<stdio.h>

int myheap[2][200001];
int hsize[2];
bool cmp1(int a, int b) { return a < b; }
bool cmp0(int a, int b) { return a > b; }

void insert(int* myheap, int *hsize, bool (*cmp)(int i, int j), int i) {
	int c = ++*hsize;
	int p = c / 2;
	while (p && cmp(i,myheap[p])) {
		myheap[c] = myheap[p];
		c = p;
		p = c / 2;
	}
	
	myheap[c] = i;
}

int getchild(int *arr,int hsize, bool (*cmp)(int i, int j),int idx ) {
	int l = idx * 2, r = l + 1;
	if (hsize < l) return 0;
	if (hsize < r) { return l; }
	if (cmp(arr[l],  arr[r])) return l;
	return r;
}

int pop(int *myheap, int *hsize, bool (*cmp)(int i, int j)) {
	int res = myheap[1];
	int data = myheap[(*hsize)--];
	int p = 1;
	int c = getchild(myheap, *hsize, cmp,p);
	while (c && cmp(myheap[c] , data)) {
		myheap[p] = myheap[c];
		p = c;
		c = getchild(myheap, *hsize, cmp, p);
	}
	myheap[p] = data;
	return res;
}

int main() {
	int tc;
	scanf("%d", &tc);
	while (tc--) {
		int n, a, b;
		scanf("%d %d %d", &n, &a, &b);

		int num = 1983;

		hsize[0] = hsize[1] = 0;
		int res = 0;
		res = myheap[0][++hsize[0]] = num;

		for(int i = 1; i < n; ++i){
			num = ((long long)num*a + b) % 20090711;
			if (myheap[0][1] < num) insert(myheap[1], &hsize[1], cmp1,num);
			else insert(myheap[0], hsize, cmp0, num);

			while (hsize[0] && myheap[0][1] > myheap[1][1]) {
				insert(myheap[1], hsize+1, cmp1, pop(myheap[0], hsize, cmp0));
			}

			while (hsize[1] < hsize[0]) {
				insert(myheap[1], hsize + 1, cmp1, pop(myheap[0], hsize, cmp0));
			}

			while (hsize[0] < hsize[1]) {
				insert(myheap[0], hsize, cmp0, pop(myheap[1], hsize + 1, cmp1));
			}
			res = (res + myheap[0][1])%20090711;
		}
		printf("%d\n", res);
	}
	return 0;
}