#include<iostream>
#include<algorithm>
#include<string>
#include<vector>

using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);

    int T;
    cin >> T;
    for(int tc = 0; tc < T; ++tc){
        int n;
        cin >> n;
        vector<pair<int, int>> vec(n);
        for(int i = 0; i < n; ++i){
            cin >> vec[i].first >> vec[i].second;
        }
        pair<int, int> st = {0,0};
        sort(vec.begin(), vec.end());
        for(int i = 0; i < n-1; ++i){
            if(vec[i].second > vec[i+1].second){
                cout << "NO\n";
                goto END2;
            }
        }
        cout << "YES\n";
        for(int i = 0; i < n; ++i){
            while(vec[i].first != st.first){
                cout << 'R';
                st.first++;
            }
            while(vec[i].second != st.second){
                cout << 'U';
                st.second++;
            }
        }
        cout << '\n';
        continue;
        END2:
        int debug =1;
    }
    return 0;
}