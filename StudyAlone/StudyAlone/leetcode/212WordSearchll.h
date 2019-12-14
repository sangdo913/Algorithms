#include<iostream>
#include<vector>
#include<string>

using namespace std;

vector<vector<int>> myvisit;
vector<vector<char>> *myboard;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};

int query;

bool canmade(int i, int j, int l, string& s){
    if(l == s.size()) {
        return true;
    }
    if(i < 0 || j < 0 || i == (*myboard).size() || j == (*myboard)[0].size()) return false;
    if(s[l] != (*myboard)[i][j]) return false;
    if(myvisit[i][j] == query) return false;
    myvisit[i][j] = query;

    for(int d = 0; d < 4; ++d){
        int ni = i + dr[d];
        int nj = j + dc[d];
        if(canmade(ni,nj,l+1, s)) return true;
    }
    myvisit[i][j] = 0;
    return false;
}
class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ret;
    
        myboard = &board;
        myvisit.clear();
        myvisit.resize(board.size(), vector<int>(board[0].size()));
        int check =1;
        for(int k = 0; k < words.size(); ++k){
            for(int i = 0; i < board.size(); ++i){
                for(int j = 0; j <board[i].size();++j ){
                    query++;
                    if(canmade(i,j,0,words[k])){
                        ret.push_back(words[k]);
                        goto COMPLETE;
                    }
                }
            }
            COMPLETE:
            check = 1;
        }
        return ret;
    }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m, wl;
    
    vector<vector<char>> boards;
    vector<string> words;
    cin >> n >> m;
    cin >> wl;
    boards.resize(n, vector<char>(m));
    for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) cin >> boards[i][j];
    words.resize(wl);
    for(int i = 0; i < wl; ++i) cin >> words[i];
    auto v = Solution().findWords(boards, words);
    for(auto a : v){
        cout << a << endl;
    }
    return 0;
}
