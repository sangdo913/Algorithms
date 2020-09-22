#include<vector>
#include<iostream>
using namespace std;

int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        vector<int> remains;
        int n, x, y;
        cin >> n >> x >> y;
        int diff = y-x;
        for(int i = 1; i <= diff; ++i){
            if(diff%i == 0) remains.push_back(i);
        }
        for(int i = 0; i < remains.size(); ++i){
            int num = diff/remains[i] + 1;
            if(num <= n){
                int r = n-num;
                int a = x-remains[i];
                vector<int> vec;
                for(int v = x; v <= y; v+= remains[i]){
                    vec.push_back(v);
                }
                while(a > 0 && r > 0){
                    vec.push_back(a);
                    r--;
                    a-= remains[i];
                }
                while(r--){
                    y += remains[i];
                    vec.push_back(y);
                }
                for(auto v : vec){
                    cout << v << ' ';
                }
                cout << endl;
                break;
            }
        }
    }
    return 0;
}