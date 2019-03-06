#include<iostream>

using namespace std;

int A[10][10], N, K;
int d[3][20];

bool simul(){
    int turn[3] = {0};
    int win[3] = {0};
    int p1 = 0, p2 = 1;

    while(true){
        if((p1 == 0 && turn[p1] == N) ||(p2 == 0 && turn[p2] == N)) return false;
        int np1, np2;
        int w1 = d[p1][turn[p1]++];
        int w2 = d[p2][turn[p2]++];
        if(A[w1][w2] == 2){
            np1 = p1;
            win[p1]++;
        }
        else if(A[w1][w2] == 1){
            np1 = p1 > p2 ? p1 : p2;
            win[np1]++;
        }
        else{
            win[p2]++;
            np1 = p2;
        }
        np2 = 3-p1-p2;
        
        if(win[p1] == K){
            return p1 == 0;
        }
        else if(win[p2] == K){
            return p2 == 0;
        }
        p1 = np1; p2 = np2;
    }
}

void swap(int&a, int &b){
    int temp = a;
    a = b;
    b= temp;
}

bool perm(int l){
    if(l == N){
        return simul();
    }

    for(int i = l; i < N; i++){
        swap(d[0][i],d[0][l]);
        int res = perm(l+1);
        if(res) 
            return res;
        swap(d[0][i], d[0][l]);
    }
    return false;
}

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
   cin >> N >> K;
   for(int i = 1; i <= N; i++){
       for(int j = 1; j <= N; j++){
           cin >> A[i][j];
       }
   } 

   for(int i = 0; i < 20; i++) cin >> d[1][i];
   for(int i = 0; i < 20; i++) cin >> d[2][i];
   for(int i = 0; i < 9; i++){ d[0][i]= i+1;}
   cout << perm(0);
   return 0;
}
