//https://www.acmicpc.net/problem/16196
//BOJ 16196 중국 신분증 번호
#include<iostream>

using namespace std;

int days[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

bool isYun(char years[4]){
    int y = 0;
    for(int i =0; i < 4; i++){
        y*=10; 
        y+= years[i]-'0';
    }
    return (y%4 == 0 && y %100 != 0) ||  y%400 == 0;
}

char rnum[50][7];
char nums[19];
int n;

bool checkregion(char reg[6]){
    for(int i = 0; i < n; i++){
        bool ch = true;
        for(int j = 0; j < 6; j++){
            if(reg[j] != rnum[i][j]){
                ch = false; break;
            }
        }
        if(ch) return true;
    }
    return false;
}

char code3(char nums[3]){
    int res = 0;
    for(int i =0; i < 3; i++){
        res *=10;
        res += nums[i] - '0';
    }

    res = res ? res % 2 : -1;
    if(res == -1) return 'I';
    return res ? 'M' : 'F';
}

char checkSum(){
    int checksum = 0;
    for(int i = 0; i < 17; i++){
        checksum += nums[i] - '0';
        checksum <<= 1;
        checksum %= 11;
    }
    int x = (12 - checksum)%11;
    return x == 10 ? 'X' : '0' + x;
}

bool checkDay(char ds[8]){
    bool isyun = isYun(&ds[0]);
    int y = 0;
    for(int i = 0; i < 4; i++){
        y*= 10;
        y+= ds[i] - '0' ;
    } 

    int m = 0 , d = 0;
    m = 10*(ds[4]-'0') + ds[5]-'0';
    d = 10*(ds[6]-'0')  + ds[7] - '0';
    if(y < 1900 || y > 2011) return false;
    if(m < 1 || m >12) return false;
    if(d < 1 || d > days[isyun][m]) return false;

    return true;
}

int BOJ16196(){
    cin >> nums;
    cin >> n;

    for(int i = 0; i < n; i++){
            cin >> rnum[i];
    }

    bool res = true;
    res &= checkregion(nums);
    res &= checkDay(nums + 6);
    char g = code3(nums + 14);
    res &= nums[17] == checkSum();

    if(res) cout << g;
    else cout << 'I';

    return 0;
}