#include<iostream>

using namespace std;

int arr[200001];
int color[200001];
int main(){
    freopen("0Text.txt", "r", stdin);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int max = 1;
        for(int i = 0; i < n; ++i){
            cin >> arr[i];
        }
        color[0] = 1;
        bool change = false;
        int idx = 0;
        for(int i = 1; i < n; ++i){
            if(arr[i-1] != arr[i]){
                color[i] = 3-color[i-1];
                max = max < color[i] ? color[i] : max;
            }
            else{
                color[i] = color[i-1];
                change = true;
                idx = i;
            }
        }
        if(arr[n-1] != arr[0] && color[n-1] == color[0]){
            if(change){
                for(int i = idx; i < n; ++i){
                    color[i] = 3-color[i];
                }
            }
            else{
                color[n-1] = 3;
                max = 3;
            }
        }
        cout << max <<endl;
        for(int i = 0; i < n; ++i){
            cout << color[i] << ' ' ;
        }
        cout << endl;
    }
    return 0;
}