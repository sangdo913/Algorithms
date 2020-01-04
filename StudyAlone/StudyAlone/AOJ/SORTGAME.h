#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int n;
vector<unsigned char> dist[9];
int statedp[9][8][8];
int getstate(int arr[8]){
    return 0;
}

int conv(int arr[8]){
    int ret = 0;
    for(int i = 0; i < n; ++i){
        ret *=n;
        ret += arr[i];
    }
    return ret;
}
void tostate(int arr[8], int state){
    for(int i = n-1; i >=0; --i){
        arr[i] = state%n;
        state /=n;
    }
}

int arr[8];
int nowarr[8];

void bfs(){
    int num = 1;
    for(int i = 0; i < n; ++i){
       num*=n;
    }
    dist[n].resize(num, 100);
    queue<int> Q;
    int state = conv(arr);
    dist[n][state] = 0;
    Q.push(state);

    while(!Q.empty()){
        state = Q.front(); Q.pop();
        tostate(nowarr, state);

        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                for(int i = 0; i < 8; ++i) arr[i] = nowarr[i];
                for(int c = 0; c < (j-i+1)/2; ++c){
                    int temp = arr[i+c];
                    arr[i+c] = arr[j-c];
                    arr[j-c] = temp;
                }
                int nextstate = conv(arr);

                if(dist[n][state] + 1 >= dist[n][nextstate]) continue;
                dist[n][nextstate] = dist[n][state] + 1;
                Q.push(nextstate);
            }
        }
    }
}

int nums[8];

int main(){
    freopen("0Text.txt", "r", stdin);
    for(int i= 1; i <=8; ++i) for(int j = 0; j < 8; ++j) for(int k = 0; k < 8; ++k) statedp[i][j][k] = -1;

    for(int i = 1; i <= 8; ++i){
        n = i;
        for(int j = 0; j < i; ++j) arr[j] = j;
        bfs();
    }
    int c;
    scanf("%d\n", &c);
    for(int  tc = 1; tc <= c; ++tc){
        scanf("%d\n", &n);
        for(int i = 0; i < n; ++i){
            scanf("%d", &arr[i]);
            nums[i] = arr[i];
        }

        for(int i = 1; i < n; ++i){
           int j = i;
           while(j && nums[j] < nums[j-1]){
               int temp = nums[j-1];
               nums[j-1] = nums[j];
               nums[j] = temp;
               j--;
           } 
        }

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j){
                if(arr[i] == nums[j]) {
                    arr[i] = j;
                    break;
                }
            }
        }

        printf("%d\n", dist[n][conv(arr)]);
    }
    return 0;
}