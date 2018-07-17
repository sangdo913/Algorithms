#include<cstdio>

int dfs(int depth) {
	dfs(depth + 1);
	return 0;
}
int main()
{
	dfs(0);
	return 0;
}