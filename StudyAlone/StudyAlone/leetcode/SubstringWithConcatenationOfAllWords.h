#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

vector<int> kmptable;
vector<vector<bool> > check;

void makekmp(const string& s) {
	register int match = 0, i = 0;
	kmptable[i] = 0;
	for (register int i = 1; i < s.size(); ++i) {
		while (match && s[i] != s[match]) {
			match = kmptable[match-1];
		}
		if (i != match && s[i] == s[match]) match++;
		kmptable[i] = match;
	}
}

void makecheck(int id, const string &s, const string &t) {
	register int match = 0;
	for (register int i = 0; i < s.size(); ++i) {
		while (match && s[i] != t[match]) match = kmptable[match-1];
		
		if (s[i] == t[match]) match++;
		if (match == t.size()) {
			check[id][i-match+1] = true;
			match = kmptable[match-1];
		}
	}
}
vector<int>res;
vector<vector<int> > linecheck;
map<string, int> mp;
vector<int> dest;
class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		if (!words.size() || !s.size()) return vector<int>();
		kmptable.clear();
		check.clear();
		kmptable.resize(words[0].size());
		linecheck.clear();
		linecheck.resize(s.size(), vector<int>(words.size()));
		res.clear();
		mp.clear();
		dest.clear();
		dest.resize(words.size());
		check.resize(words.size(), vector<bool>(s.size(), false));
		int cnt = 0;
		for (int i = 0; i < words.size(); ++i) {
			if (mp.find(words[i]) != mp.end()) {
				dest[mp[words[i]]]++;
				continue;
			}
			mp[words[i]] = i;
			dest[i]++;

			makekmp(words[cnt]);
			makecheck(i, s, words[cnt]);
			for (int j = 0; j < s.size(); ++j) {
				if (check[cnt][j]) {
					for (register int k = -(int)words.size() + 1; k <= 0; ++k) {
						int idx = j + k * words[0].size();
						if (idx < 0 || s.size() <= idx) continue;
						linecheck[idx][i]++;
					}
				}
			}
			cnt++;
		}
		for (register int i = 0; i < s.size(); ++i) {
			bool isok = true;
			for (int j = 0; j < cnt; ++j) {
				if (dest[j] != linecheck[i][j]) {
					isok = false;
					break;
				}
			}
			if (isok) {
				res.push_back(i);
			}
		}
		return res;
	}
};

int main() {
	int n;
	string s,t; vector<string> words;
	cin >> s;
	cin >> n;
//	n = 5001;
	for (int i = 0; i < n; ++i) {
		cin >> t;
		words.push_back(t);
//		words.push_back("a");
	}

	vector<int> res = Solution().findSubstring(s, words);
	for (auto i : res) cout << i << ' ';
	return 0;
}