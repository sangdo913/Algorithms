#include<iostream>
#include<string>
using namespace std;
#define MAX(x,y) ((x) > (y) ? (x) : (y))
int g[200001];
int t;
int ng[200001];
int sa[200001];
int cnt[200001];
int cnt2[200001];
int order[200001];
int lca[200001];
int inv[200001];
class Solution {
public:
	string longestDupSubstring(string S) {
		int l = S.size();
		S.push_back(0);
		int gn = -1;
		for (int i = 0; i < l; ++i) g[i] = S[i]-'a'+1, gn = MAX(gn,g[i]);
		for (int i = 0; i < l; ++i) sa[i] = i;
		g[l] = 0;
		t = 1;
		while (t < l) {
			for (int i = 0; i <= gn; ++i) cnt[i] = 0,cnt2[i] = 0;
			for (int i = 0; i < l; ++i) {
				cnt[g[i]]++;
				if(i+t < l) cnt2[g[i + t]]++;
				else cnt2[0]++;
			}
			for (int i = 1; i <= gn; ++i) cnt[i] += cnt[i - 1], cnt2[i] += cnt2[i-1];
			for (int i = 0; i < l; ++i) 
				order[--cnt2[i + t < l ? g[i+t] : 0]] = i;
			for (int i = l-1; i >= 0; --i) {
				sa[--cnt[g[order[i]]]] = order[i];
			}
			ng[0] = 1;
			for (int i = 1; i < l; ++i) {
				if (g[sa[i]] == g[sa[i - 1]] && g[sa[i] + t] == g[sa[i - 1] + t]) ng[sa[i]] = ng[sa[i - 1]];
				else gn = ng[sa[i]] = ng[sa[i - 1]] + 1;
			}
			for (int i = 0; i < l; ++i) {
				g[i] = ng[i];
			}
			t <<= 1;
		}
		string res;
		for(int i = 0; i < l; ++i) inv[sa[i]] = i;
		int len = 0;
		for (int i = 0; i < l; ++i) {
			int idx = inv[i];
			if (!idx) continue;
			int prev = sa[idx - 1];
			while (S[i + len] == S[prev + len])++len;
			lca[idx] = len;
			if (res.size() < len) {
				res = string(S.begin() + i, S.begin() + i + len);
			}
			if (len) len--;
		}
		return res;
	}
};