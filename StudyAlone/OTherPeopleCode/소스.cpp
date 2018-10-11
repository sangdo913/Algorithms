#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#define lpi(n) for(int i=0;i<n;i++)
#define lpj(n) for(int j=0;j<n;j++)
using namespace std;
enum direction { north = 0, east, south, west };

int tc, n;
int dx[] = { 0,1,0,-1 };
int dy[] = { -1,0,1,0 };
vector<int> happy;
struct mol {
	int y;
	int x;
	int dir;
	int k;
	bool dead = 0;
	vector<mol*> pairs;
};

pair<int, int> getdis(mol* a, mol* b) {
	return make_pair(abs(a->x - b->x), abs(a->y - b->y));
}
vector<mol*> v;
bool comp(pair<mol*, int> a, pair<mol*, int> b) {
	return a.second < b.second;
}
void checkmol(mol* a) {
	vector<pair<mol*, int>> candidate;
	lpi(v.size()) {
		if (v[i] != a) {
			if (v[i]->dir != a->dir) {
				if (a->dir == 0 && v[i]->x == a->x && a->y < v[i]->y && v[i]->dir == (a->dir + 2) % 4) { //수직으로 만나는 경우
					candidate.push_back(make_pair(v[i], (getdis(v[i], a).second) / 2));
				}
				if (a->dir == 2 && v[i]->x == a->x && a->y > v[i]->y && v[i]->dir == (a->dir + 2) % 4) { //수직으로 만나는 경우
					candidate.push_back(make_pair(v[i], (getdis(v[i], a).second) / 2));
				}
				if (a->dir == 1 && v[i]->y == a->y && a->x < v[i]->x && v[i]->dir == (a->dir + 2) % 4) { //수평으로 만나는 경우
					candidate.push_back(make_pair(v[i], (getdis(v[i], a).first) / 2));
				}
				if (a->dir == 3 && v[i]->y == a->y &&a->x > v[i]->x && v[i]->dir == (a->dir + 2) % 4) { //수평으로 만나는 경우
					candidate.push_back(make_pair(v[i], (getdis(v[i], a).first) / 2));
				}
				if (getdis(a, v[i]).first == getdis(a, v[i]).second) { //수직 수평거리가 같을때
					if (a->dir == north && v[i]->y > a->y) {//북쪽으로 가고 있으면 지금 보다 높이 있는 애들만
						if (v[i]->dir == east && a->x > v[i]->x) candidate.push_back(make_pair(v[i], getdis(v[i], a).second)); // 서쪽에서 동쪽으로 오는 애들
						if (v[i]->dir == west && a->x < v[i]->x)  candidate.push_back(make_pair(v[i], getdis(v[i], a).second));//동쪽에서 서쪽으로 오는애들
					}
					if (a->dir == south && v[i]->y < a->y) {//남쪽으로 가고 있으면
						if (v[i]->dir == east && a->x > v[i]->x) candidate.push_back(make_pair(v[i], getdis(v[i], a).second));// 서쪽에서 동쪽으로 오는 애들
						if (v[i]->dir == west && a->x < v[i]->x)  candidate.push_back(make_pair(v[i], getdis(v[i], a).second));//동쪽에서 서쪽으로 오는애들
					}
					if (a->dir == east && v[i]->x > a->x) { //동쪽으로 가고 있으면 
						if (v[i]->dir == north && a->y > v[i]->y) candidate.push_back(make_pair(v[i], getdis(v[i], a).first)); // south에서 north으로 오는 애들
						if (v[i]->dir == south && a->y < v[i]->y)  candidate.push_back(make_pair(v[i], getdis(v[i], a).first));//north에서 south으로 오는애들
					}
					if (a->dir == west && v[i]->x < a->x) { //동쪽으로 가고 있으면 
						if (v[i]->dir == north && a->y > v[i]->y) candidate.push_back(make_pair(v[i], getdis(v[i], a).first)); // south에서 north으로 오는 애들
						if (v[i]->dir == south && a->y < v[i]->y) candidate.push_back(make_pair(v[i], getdis(v[i], a).first));//north에서 south으로 오는애들
					}
				}
			}
		}
	}
	sort(candidate.begin(), candidate.end(), comp);
	lpj((int)candidate.size()) {
		if (candidate[j].second == candidate[0].second) {
			a->pairs.push_back(candidate[j].first);
		}
	}
}
void kill(mol* a) {
	lpi(a->pairs.size()) {
		lpj(a->pairs[i]->pairs.size()) {
			if (a == a->pairs[i]->pairs[j]) {
				a->dead = 1;
				a->pairs[i]->dead = 1;
			}
		}
	}
}
int main()
{
	scanf("%d", &tc);
	for (int s = 0; s < tc; s++) {
		scanf("%d", &n);
		v.clear();
		lpi(n) {
			int y, x, dir, k;
			scanf("%d %d %d %d", &x, &y, &dir, &k);
			if (dir == 1) dir = 2;
			else if (dir == 2) dir = 3;
			else if (dir == 3) dir = 1;
			mol* tmp = new mol;
			tmp->x = 2 * x; tmp->y = 2 * y; tmp->dir = dir; tmp->k = k; tmp->dead = 0;
			v.push_back(tmp);
		}
		int ans = 0;
		for (int k = 0; k < (int)v.size(); k++) {
			checkmol(v[k]);
		}
		lpi(v.size()) {
			kill(v[i]);
		}
		lpi((int)v.size()) {
			if (v[i]->dead) {
				ans += v[i]->k;
			}
			//delete(v[i]);
		}
		happy.push_back(ans);
	}
	lpi(happy.size()) printf("#%d %d\n", i + 1, happy[i]);
	return 0;
}