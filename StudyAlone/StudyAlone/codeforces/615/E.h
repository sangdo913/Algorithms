#include<iostream>
#include<vector>
#include<map>
using namespace std;
map<int, int> mp;

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<vector<int> > vec(n, vector<int>(m));
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> vec[i][j];
        }
    }
    int res = 0;
    vector<vector<int> > splane(n, vector<int>(m));
    for(int j = 0; j < m; ++j){
        int mmin = 0x3f3f3f3f;
        for(int i = 0; i < n; ++i){
            mp[i*m+j+1] = i;
            // cout << i*m + j+1 << " " << i << endl;
        }
        for(int i = 0; i < n; ++i){
            int p = mp[vec[i][j]];
            //  cout << "i : " << i << " p " <<  p << " vec " << vec[i][j] << endl;
            if(vec[i][j] %m  == (j + 1)%m && 1<= vec[i][j] && vec[i][j] <= m*n) 
                if(i >= p) splane[(i-p)][j]++;
                else splane[i+n-p][j]++;
        }
        for(int i = 0; i < n; ++i){
            int cnt = n + i;
            // if(i > n/2) n + (n-i); 
            cnt -= splane[i][j];
            // cout << " i " << i << ' '  << splane[i][j] << endl;
            if(mmin > cnt) mmin = cnt;
        }
        // cout << "mmin : " << mmin << endl;
        res += mmin;
    }
    cout << res;
    return 0;
}