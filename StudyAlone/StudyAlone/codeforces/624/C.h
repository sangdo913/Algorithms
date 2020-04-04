#include<iostream>
#include<string>
#include<vector>
#include<string.h>
using namespace std;

int conv[256];
int cnt[26][200001];
int p[200001];
char str[200002];
int sums[26][200002];

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    freopen("0Text.txt", "r", stdin);
    int tc;
    cin >> tc;
    for(int i = 'a'; i <= 'z'; ++i) conv[i] = i-'a';
    while(tc--){
        int a, b;
        cin >> a >> b;
        cin >> str+1;
        for(int i = 0; i < b; ++i){
            cin >> p[i];
        }
        int size = 0;
        size = a;
        for(int i =1; i <= size;++i){
            for(int j = 0; j < 26; ++j) sums[j][i] = 0;
        }
        for(int i = 1; i <= size; ++i){
            for(int j = 0; j < 26; ++j) {
               sums[j][i] += sums[j][i-1]; 
            }
            sums[conv[str[i]]][i]++;
        }
        vector<int> vec(26,0);
        for(int i = 0; i < b; ++i){
            for(int j = 0; j < 26; ++j){
                vec[j]+= sums[j][p[i]];
            }
        }
        for(int i = 0; i < 26; ++i){
            vec[i] += sums[i][size];
        }
        for(int i = 0; i < 26; ++i){
            cout << vec[i] << ' ';
        }
        cout << '\n';
    }
    return 0;
}