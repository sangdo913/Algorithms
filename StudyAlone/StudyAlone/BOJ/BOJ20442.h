#include<iostream>
#include<string>

using namespace std;
string str;
int nums[3000001];

int main() {
    freopen("0Text.txt", "r", stdin);
    cin >> str;
    int knum= 0;
    int nsize = 0;
    for(int i = 0; i < str.size(); ++i){
        if(str[i] == 'K') knum++;
        else {
            nums[nsize++] = knum;
            knum = 0;
        }
    }
    nums[nsize++] = knum;
    int i = 0, j = nsize-2;
    int res = 0;
    while(i <= j){
        int l = nums[i];
        int r = nums[j+1];
        res = max(res, min(l,r)*2 + j-i+1);
        if(l < r) ++i;
        else if(r > l) --j;
        else {
            if(i == j) break;
            if(nums[i+1] > nums[j]) --j;
            else ++i;
        }
    }
    printf("%d\n", res);

    return 0;
}