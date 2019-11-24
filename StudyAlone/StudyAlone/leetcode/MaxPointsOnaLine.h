#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<tuple>
#include<set>

using namespace std;

#define rint register int
int gcd(int a, int b) {
	int r;
	if (a < b) a ^= b ^= a ^= b;
	while (b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
#define MAX(x,y) ((x) > (y) ? (x) :(y))

struct cmp {
	bool operator()(const vector<int>& a, const vector<int>& b) {
		return a[0] < b[0];
	}
};

class Solution {
public:
	int maxPoints(vector<vector<int>>& points) {
		
		if (points.size() == 0) return 0;
		sort(points.begin(), points.end(), cmp());
		map<tuple<int, int, int>, int> mp;
		map<tuple<int, int, int>, int > check;
		int query = (int)0x8fffffff;
		vector<int> contain;
		vector<int> num(points.size());
		map<pair<int, int>, int> se;
		mp.clear();
		check.clear();
		int res = 0;
		int gn = 0;
		for (int i = 0; i < points.size(); ++i) {
			auto p = make_pair(points[i][0], points[i][1]);
			if (!se[p]) {
				contain.push_back(i);
				se[p] = i+1;
			}
			num[se[p]-1]++;
			res = MAX(res, num[se[p]-1]);
		}

		for (rint i1 = 0; i1 < contain.size(); ++i1) {
			++query;
			for (rint j1 = i1 + 1; j1 < contain.size(); ++j1) {
				int i = contain[i1];
				int j = contain[j1];
				
				int diffx = points[i][0] - points[j][0];
				int diffy = points[i][1] - points[j][1];

				if (!diffx) {
					if (check[{0, 1, points[i][0]}] < query) continue;
					check[{0, 1, points[i][0]}] = query;
					if (mp[{0, 1, points[i][0]}] == 0) {
						mp[{0, 1, points[i][0]}] = num[i] + num[j];
					}
					else mp[{0, 1, points[i][0]}]+=num[j];

					if (res < mp[{0, 1, points[i][0]}]) res = mp[{0, 1, points[i][0]}];
				}
				else if (!diffy) {
					if (check[{1, 0, points[i][1]}]< query) continue;
					check[{1, 0, points[i][1]}] = query;

					if (mp[{1, 0, points[i][1]}] == 0) {
						mp[{1, 0, points[i][1]}] = num[i] + num[j];
					}
					else mp[{1, 0, points[i][1]}]+=num[j];

					if (res < mp[{1, 0, points[i][1]}]) res = mp[{1, 0, points[i][1]}];
				}
				else {
					int g = gcd(diffx, diffy);
					diffx /= g;
					diffy /= g;
					int b = (long long)points[i][1] * diffx - (long long)points[i][0] * diffy;

					if (check[{diffx, diffy, b }] <query) continue;
					check[{diffx, diffy, b}] = query;

					if (!mp[{diffx, diffy, b}]) mp[{diffx, diffy, b}] = num[i] + num[j];
					else mp[{diffx, diffy, b}]+= num[j];

					if (res < mp[{diffx, diffy, b}]) res = mp[{diffx, diffy, b}];
				}
			}
		}
		return res;
	}
};

int main(){
	int n;
	int a, b;
	cin >> n;
	vector<vector<int> > v;
	for (int i = 0; i < n; ++i) {
		vector<int> vec;
		cin >> a >> b;
		vec.push_back(a);
		vec.push_back(b);
		v.push_back(vec);
	}

	cout << Solution().maxPoints(v);

	return 0;
}