#include<iostream>

using namespace std;

long long arr[100000];
int mmin(int i1, int i2) {return i1 < i2 ?i1:i2; }

int D481(){
    long long possible[9];
    int cnt[3][5];
    for(int j = 0; j < 3; j++) for(int i = 0 ; i < 5; i++) cnt[j][i] = 0x3f3f3f3f;


    int n;
    cin >> n;

    if(n == 1){
        cout << 0;
        return 0;
    }

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

   possible[0] = -arr[0] + arr[1];
   possible[1] = possible[0] + 1;
   possible[2] =  possible[0] - 1;
   possible[3] = possible[0] +2;
   possible[4] = possible[0] - 2;

    int nums[3] = {-1,0,1};
    for(int ii = 0; ii < 3; ii++){
        for(int i = 0; i < 5; i++){
            int ccnt = ii != 1;
            int prev = arr[0] + nums[ii];
            int j = 1;
            for(; j < n; j++){
                if(arr[j] == prev + possible[i]) prev += possible[i];
                else if(arr[j]+1 == prev +possible[i]) {
                    prev = arr[j]+1; ccnt++;
                }
                else if(arr[j] -1 == prev + possible[i]) {
                    prev = arr[j]-1; ccnt++;
                }
                else break;
            }

            if(j == n){cnt[ii][i] = ccnt;}
        }
    }

    int res = 0x3f3f3f3f;
    for(int ii = 0; ii < 3; ii++) for(int i = 0; i < 5; i++){
        res = mmin(res, cnt[ii][i]);
    }
    cout << (res == 0x3f3f3f3f ? -1 : res);

    return 0;
}