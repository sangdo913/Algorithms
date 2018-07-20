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
	b b;
	
	A *t = &b.getA(0);
	t->a = 10;
	t->b = 20;

	t = &b.getA(2);
	t->a = -50;
	t->b = 250;

	printf("t1 a : %d t1 b : %d\n", b.getA(0).a, b.getA(0).b);
	printf("t2 a : %d t2 b : %d\n", b.getA(2).a, b.getA(2).b);

	return 0;
}