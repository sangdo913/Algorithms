#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>

using namespace std;

vector < vector<string> > res;
vector<vector<int> > mynext;
vector<string> path;
vector<string> *words;
string *edw;

void dfs(int i) {
	if (!mynext[i].size()) {
		if(words->at(i-1) == *edw) res.push_back(path);
		return;
	}
	for (int j = 0; j < mynext[i].size(); ++j) {
		int nid = mynext[i][j] - 1;
		path.push_back(words->at(nid));
		dfs(nid+1);
		path.pop_back();
	}
}

class Solution {
public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		edw = &endWord;
		words = &wordList;
		res.clear();
		mynext.clear();
		mynext.resize(wordList.size() + 1);
		queue<int> Q;
		vector<int> visit(wordList.size()+1);
		string st = beginWord;

		Q.push(0);
		visit[0] = 0;
		for (int i = 1; i <= wordList.size(); ++i) visit[i] = 0x3f3f3f3f;
		int dist = 0;
		bool isend = false;

		while (!Q.empty()) {
			int cnt = Q.size();
			++dist;

			while (cnt--) {
				int idx = Q.front(); Q.pop();
				string now;
				if (idx == 0) {
					now = beginWord;
				}
				else now = wordList[idx - 1];
				if (now == endWord) {
					isend = true;
					goto END;
				}
				
				for (int i = 0; i < wordList.size(); ++i) {
					if (visit[i+1] < dist) continue;
					int diff = 0;
					for (int j = 0; j < beginWord.size(); ++j) {
						if (now[j] != wordList[i][j]) {
							diff++;
						}
					}
					if (diff == 1) {
						mynext[idx].push_back(i+1);
						
						if (!isend && visit[i + 1] != dist) {
							visit[i+1] = dist;
							Q.push(i + 1);
						}
					}
				}
			}
		}
		END:
	
		if (isend) {
			res.resize(0);
			path.resize(0);
			path.push_back(beginWord);
			dfs(0);
		}
		return res;
	}
};

int main() {
	freopen("0Text.txt", "r", stdin);
	int n;
	vector<string> vec;
	string s, e;
	cin >> s >> e;
	cin >> n;
	vec.resize(n);
	for (int i = 0; i < n; ++i) cin >> vec[i];
	auto res = Solution().findLadders(s,e,vec);
	for(int i = 0; i < res.size(); ++i){
		for(int j = 0; j < res[i].size(); ++j){
			cout << res[i][j] << ' ';
		}
		cout << endl ;
	}
	return 0;
}