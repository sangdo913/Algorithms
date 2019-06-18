//#include<iostream>
//#include<map>
//
//using namespace std;
//int h1, w1, h2, w2;
//string master[2000];
//string picture[2000];
//int idx, tidx;
//int check[2000][2000];
//
//struct TRIE {
//	int terminal;
//	TRIE* fail;
//	TRIE* arr[2];
//	TRIE() :fail(0), terminal(-1) { arr[0] = arr[1] = 0; }
//}tnode[2001*2000];
//
//TRIE root;
//TRIE* Q[5000000]; 
//
//void makefail() {
//	int fr, re;
//	fr = re = 0;
//	Q[re++] = &root;
//	root.fail = &root;
//
//	while (fr != re) {
//		TRIE* now = Q[fr++];
//
//		for (int i = 0; i < 2; ++i) {
//			TRIE* next = now->arr[i];
//			if (!next) continue;
//			if (now == &root) next->fail = &root;
//			else {
//				TRIE* des = now->fail;
//				while (des != &root && !des->arr[i]) des = des->fail;
//				if (des->arr[i]) des = des->arr[i];
//				next->fail = des;
//			}
//			if (next->fail->terminal != -1) next->terminal = next->fail->terminal;
//			Q[re++] = next;
//		}
//	}
//}
//
//int pic[2000];
//int kmp[2000];
//#include<string>
//
//int main() {
//	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
//	cin >> h1 >> w1 >> h2 >> w2;
//
//	for (int i = 0; i < h1; ++i) cin >> picture[i];
//	for (int i = 0; i < h2; ++i) cin >> master[i];
//
//	map<string, int> mp;
//
//	for (int i = 0; i < h1; ++i) {
//		auto it = mp.find(picture[i]);
//		if (it != mp.end()) {
//			pic[i] = it->second;
//		}
//		else {
//			mp[picture[i]] = i;
//			pic[i] = i;
//
//			TRIE* t = &root;
//			for (int j = 0; j < w1; ++j) {
//				int pos = picture[i][j] == 'o';
//				if (!t->arr[pos]) t->arr[pos] = &tnode[tidx++];
//				t = t->arr[pos];
//			}
//			t->terminal = i;
//		}
//	}
//
//	makefail();
//
//	int j = -1;
//	for (int i = 0; i < h1; ++i) {
//		kmp[i] = j;
//		while (j != -1 && pic[j] != pic[i]) j = kmp[j];
//		++j;
//	}
//
//	for (int i = 0; i < h2; ++i) for (int j = 0; j < w2; ++j) check[i][j] = -1;
//
//	for (int i = 0; i < h2; ++i) {
//		TRIE *now = &root;
//		for (int j = 0; j < w2; ++j) {
//			int pos = master[i][j] == 'o';
//
//			while (now != &root && !now->arr[pos])
//				now = now->fail;
//			if (now->arr[pos]) now = now->arr[pos];
//
//			if (now->terminal != -1) {
//				check[i][j] = now->terminal;
//			}
//		}
//	}
//
//	int res = 0;
//	for (int j = w1 - 1; j < w2; ++j) {
//		int w = 0;
//		for (int i = 0; i < h2; ++i) {
//			while (w != -1 && check[i][j] != pic[w]) w = kmp[w];
//			if (w == h1 - 1) {
//				res++;
//				w = kmp[w];
//				while (w != -1 && check[i][j] != pic[w]) w = kmp[w];
//			}
//			++w;
//		}
//	}
//	return !(cout << res);
//}

#include<iostream>

using namespace std;

char s[2001][2001];
char t[2001][2001];

int hp, wp, hm, wm;
typedef unsigned long long LL;
LL hashed [2001][2001];
LL hh, ww;
const int whash = 65537;
const int hhash = 5381;

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> hp >> wp >> hm >> wm;
	for (int i = 1; i <= hp; ++i) cin >> s[i] + 1;
	for (int i = 1; i <= hm; ++i) cin >> t[i] + 1;
	hh = 1; ww = 1;
	for (int i = 0; i < wp; ++i) ww *= whash;
	for (int i = 0; i < hp; ++i) hh *= hhash;

	for (int i = 1; i <= hp; ++i) {
		for (int j = 1; j <= wp; ++j) {
			hashed[i][j] = hashed[i - 1][j] * hhash + hashed[i][j - 1] * whash + s[i][j];
		}
	}
	LL value = hashed[hp][wp];
	int res = 0;

	for (int i = 1; i <= hm; ++i) {
		for (int j = 1; j <= wm; ++j) {
			hashed[i][j] = hashed[i - 1][j] * hhash + hashed[i][j - 1] * whash + t[i][j];
			LL size = hashed[i][j];
			if (i > hp) size -= hashed[i - hp][j]*hh;
			if (j > wp) size -= hashed[i][j - wp]*ww;
			if (i > hp && j > wp) size += hashed[i - hp][j - wp] * hh*ww;
			res += i >= hp && j >= wp && size == value;
		}
	}
	cout << res;
	return 0;
}