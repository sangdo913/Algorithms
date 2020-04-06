#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;
char str[200001];
int arr[200001];
int n;
int conv[256];
int dr[256];
int dc[256];

int main(){
    freopen("0Text.txt", "r", stdin);
    int tc;
    cin >> tc;
    dr['U'] = -1;
    dr['D'] = 1;
    dc['L'] = -1;
    dc['R'] = 1;
    while(tc--){
        map<pair<int,int> ,int> mp;
        map<pair<int,int>, int> diff;
        map<pair<int, int>, pair<int,int>> pos;
        cin >> n;
        cin >> str;
        int res = 0x3f3f3f3f;
        int a, b;
        int x = 0, y = 0;
        int cnt = 1;
        mp[{0,0}] = 1;
        diff[{0,0}] = 0x3f3f3f3f;
        for(int j = 0;j < n; ++j){
            cnt++;
            x+= dr[str[j]];
            y += dc[str[j]];
            //  cout << x << ' ' << y << endl;
            if(mp[{x,y}] == 0){
                diff[{x,y}] = 0x3f3f3f3f;
                mp[{x,y}] = cnt;
            }
            else{
                int len = cnt- mp[{x,y}];
                
                if(res > len){
                    res = len;
                    a = mp[{x,y}];
                    b = cnt-1;
                }
                mp[{x,y}] = cnt;
            }
        }
        // cout<<"===========\n";
        if(res == 0x3f3f3f3f) cout << -1 << endl;
        else cout << a << ' ' << b << endl;
    }
    return 0;
}