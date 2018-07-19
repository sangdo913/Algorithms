#include<cstdio>
#include<vector>

using namespace std;
int dfs(int depth) {
	dfs(depth + 1);
	return 0;
}
int main()
{
	vector<int> vec;
	vec.push_back(1);
	printf("%d\n", vec.size());
	vec.clear();
	printf("%d\n", vec.size());
	return 0;
}