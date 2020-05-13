#include<iostream>
#include<map>
#include<algorithm>
#include<vector>

using namespace std;
int arr[400000];
map<int,int> mp;


int main(){
    freopen("0Text.txt","r",stdin);
    int n, x;
    cin >> n>> x;
    int now = 0;
    for(int i = 0; i < n; ++i){
        cin >> arr[i];
        mp[arr[i] %x]++;
        while(mp[now%x] > 0) {
            mp[now%x]--;
            now++;
        }
        cout << now <<'\n';
    }

    return 0;
}