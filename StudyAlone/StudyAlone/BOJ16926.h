#include<iostream>
#include<queue>

using namespace std;

int arr[300][300];
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

int Do(){
    int n, m, rcnt;
    cin >> n>> m >> rcnt;

    queue<int> que;

    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> arr[i][j];
    int tn = n, tm = m;
    int rotflag;
    int cnt = 0;
    int arrsize;

    while((n-2*cnt) && (m-2*cnt)){
        arrsize = 2*(n-2*cnt) + 2*(m-2*cnt) - 4;
        rotflag = rcnt % arrsize;

        for(int i = cnt; i < m - cnt; i++){
           que.push(arr[cnt][i]); 
        }

        for(int i = cnt + 1; i < n-cnt; i++){
            que.push(arr[i][m-cnt-1]);
        }

        for(int i = m - cnt -2; i >= cnt; i--){
            que.push(arr[n-cnt-1][i]);
        }

        for(int i = n-cnt-2; i> cnt; i--){
            que.push(arr[i][cnt]);
        }
        
        while(rotflag--){
            int num = que.front(); que.pop();
            que.push(num);
        }

        for(int i = cnt; i < m - cnt; i++){
           arr[cnt][i] = que.front(); que.pop();
        }

        for(int i = cnt + 1; i < n-cnt; i++){
            arr[i][m-cnt-1] = que.front(); que.pop();
        }

        for(int i = m - cnt -2; i >= cnt; i--){
            arr[n-cnt-1][i] = que.front(); que.pop();
        }

        for(int i = n-cnt-2; i > cnt; i--){
            arr[i][cnt] = que.front(); que.pop();
        }

        cnt++;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) cout << arr[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}