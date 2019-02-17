#include<cstring>
#include<iostream>
#include<queue>

using namespace std;

int arr[100][100], n,m;
int arr2[100][100];
queue<int> que;

void func1(){
    for(int i = 0; i < n/2; i++){
        for(int j = 0; j < m; j++){
            arr[n-i-1][j] ^= arr[i][j] ^= arr[n-i-1][j] ^= arr[i][j];
        }
    }
}

void func2(){
    for(int j = 0; j < m/2; j++){
        for(int i = 0; i < n; i++){
            arr[i][j] ^= arr[i][m-1-j]^=arr[i][j] ^= arr[i][m-1-j];
        }
    }
}

void func3(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            arr2[j][n-1-i] = arr[i][j];
        }
    }

    memcpy(arr,arr2, sizeof(arr));
    
    n ^= m ^= n ^= m;
}

void func4(){
    for(int i = 0; i <n; ++i ){
        for(int j = 0; j < m; ++j){
            arr2[m-1-j][i] = arr[i][j];
        }
    }
    memcpy(arr,arr2,sizeof(arr));
    n^=m^=n^=m;
}

void load(int i1, int i2 ,int j1, int j2){
    for(int i = i1; i < i2; i++){
        for(int j = j1; j < j2; j++){
            arr[i][j] = que.front(), que.pop();
        }
    }
}
void save(int i1, int i2, int j1, int j2){
    for(int i = i1 ; i < i2; i++){
        for(int j = j1; j  < j2; ++j) que.push(arr[i][j]);
    }
}

void func5(){
    save(0,n/2, 0,m/2);
    save(0,n/2, m/2, m);
    save(n/2, n, m/2,m);
    save(n/2, n, 0,m/2);

    load(0,n/2, m/2,m);
    load(n/2, n, m/2, m);
    load(n/2, n, 0, m/2);
    load(0,n/2, 0,m/2);
}

void func6(){
    save(0,n/2, 0,m/2);
    save(0,n/2, m/2, m);
    save(n/2, n, m/2,m);
    save(n/2, n, 0,m/2);

    load(n/2, n, 0 ,m/2);
    load(0,n/2,0,m/2);
    load(0,n/2,m/2,m);
    load(n/2,n,m/2,m);
}

void(*func[7])() = {0, func1, func2, func3, func4, func5, func6};

int Do(){
    int r;
    cin >> n >> m >> r;

    for(int i = 0; i < n; i++){
        for(int j =0; j < m; j++){
            cin >> arr[i][j];
        }
    } 

    for(int i = 0; i < r; i++){
        int in; cin >> in;
        func[in]();
    }

    for(int i = 0; i < n; i++){
        for(int j = 0;j < m; j++) {
            cout << arr[i][j] << ' ' ;
        }
        cout << '\n';
    }

    return 0;
}