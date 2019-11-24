#include<iostream>
#include<algorithm>
#include<set>
#include<cstdio>
#include<map>

using namespace std;
int N;
struct COD {
	int x, y;
};

bool operator<(const COD& a, const COD&b) {
	return a.x < b.x;
}

set<COD> se;
int main() {
	int tc; 
	scanf("%d", &tc);
	while (tc--) {
		scanf("%d", &N);
		se.clear();
		se.insert({ -1,0x3f3f3f3f });
		se.insert({0x3f3f3f3f,-0x3f3f3f3f });
		int res = 0;
		COD f;
		for (int i = 0; i < N; ++i) {
			scanf("%d %d", &f.x, &f.y);
			auto fx = se.upper_bound(f);
			auto iter = fx--;
			if (iter->y < f.y) {
				se.insert(f);

				while (fx != se.begin() && fx->y < f.y) {
					auto del = fx;
					fx--;
					se.erase(del);
				}
			}
			res += se.size()-2;
		}
		printf("%d\n", res);
	}

	return 0;
}
