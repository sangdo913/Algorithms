#include<cstdio>
#include<vector>

using namespace std;
int dfs(int depth) {
	dfs(depth + 1);
	return 0;
}

struct A {
	int a;
	int b;
};

struct b {
	A test[10];
	
	A& getA(int i) {
		return test[i];
	}
};

int main()
{
	long long n = 1;
	int i = 0;
	for (i = 0; n < 2100000000; n *= 3, i++) {
		printf("%d : %lld\n", i, n);
	}
	return 0;
}