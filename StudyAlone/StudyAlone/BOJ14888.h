#include<iostream>

using namespace std;

int nums[11];
int opers[4];
int res[2] = {(int)0x80000000, 0x7fffffff};
int n;

void f(int depth, int num){
    if(depth == n){
        res[0] = res[0] < num ? num : res[0];
        res[1] = res[1] > num ? num : res[1];
        return;
    }

    for(int i = 0; i < 4; i++){
        if(opers[i]){
            opers[i]--;
            switch(i){
                case 0:
                    f(depth+1, num+nums[depth]);
                break;
                case 1:
                f(depth+1, num-nums[depth]);
                break;

                case 2:
                f(depth+1, num*nums[depth]);
                break;

                case 3:
                f(depth+1, num/nums[depth]);
                break; 
            }
            opers[i]++;
        }
    }
}

int Do(){
    cin >> n;
    for(int i = 0; i < n; i++) cin >> nums[i];
    for(int i = 0; i < 4; i++) cin >> opers[i];

    f(1, nums[0]);
    cout << res[0] << '\n' << res[1];

    return 0;
}