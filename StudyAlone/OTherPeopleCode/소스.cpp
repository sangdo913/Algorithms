#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<tuple>

using namespace std;

int main() {
	vector<queue<pair<int, int> > > v;
	queue<pair<int, int> > q;

	q.push({ 1,3 });
	q.push({ 2,5 });
	v.push_back(q);

	while (v[0].size()) {
		int x, y;
		tie(x, y) = v[0].front();
		v[0].pop();

		cout << x << ' ' <<y << '\n';
	}

	return 0;
}