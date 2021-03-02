#include<iostream>
#include<string>
#include<vector>

using namespace std;

string s[151][2];
int n, tc;

bool dfs(vector<int> &res, int i, int j){
    if(i == n){
        return true;
    }
    res.push_back(j);
    
    if(s[i+1][0] > s[i][j] && dfs(res,i+1, 0)) return true; 
    else if (s[i+1][1] > s[i][j] && dfs(res,i+1,1)) return true; 
    res.pop_back();
    return false;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    for(tc = 1; tc <= t; ++tc){
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> s[i][0];
            s[i][1] = string(s[i][0].rbegin(), s[i][0].rend());
        }
        s[n][0] = string("a");
        s[n][1] = string("a");
        printf("dale is best \n");
        vector<int> res;
        if(dfs(res, 0,0)){
            for(auto it : res) cout << it;
        }
        else{
            dfs(res,0,1);
            for(auto it : res) cout << it;
        }
        cout << '\n';
    }
    return 0;
}