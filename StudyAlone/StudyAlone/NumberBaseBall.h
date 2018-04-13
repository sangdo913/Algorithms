#include<iostream>
#include<cstring>

using namespace std;

struct Info
{
    enum {size = 9*8*7};
    char nums[size][3];
    bool possible[size];
    char numArr[9];

    int des;

    void swap(char &a, char &b)
    {
        char temp = a;
        a = b;
        b = temp;
    }

    void make(char temp[9], int length, int &index)
    {
        if(length == 3)
        {
            nums[index][0] = temp[0];
            nums[index][1] = temp[1];
            nums[index++][2] = temp[2];
            return;
        }

        for(int i = length; i < 9 ; i++)
        {
            swap(temp[i],temp[length]);
            make(temp, length + 1, index);
            swap(temp[length], temp[i]);
        }
    }

    void init()
    {
        int index = 0;
        
        memset(possible,true,sizeof(possible));

        for(int i = 0 ; i < 9; i++)
        {
            numArr[i] = i + '1';
        }

        make(numArr,0,index);
    }

    void eliminate(char num[3], int res[2])
    {
        for(int i = 0; i < size; i++)
        {
            if(!possible[i]) continue;
            int ch[2] = {0,0};
            check(nums[i],num,ch);
            possible[i] = res[0] == ch[0] && res[1] == ch[1];
        }
    }

    int getRes()
    {
        int res = 0;
        for(int i = 0 ; i < size; i++) res += possible[i];
        return res;
    }

    void check(char num[3], char myNum[3], int res[2])
    {
        int howmany[10] = {0};
        for(int i = 0; i < 3; i++)
        {
            howmany[num[i] - '0']++;
        }
        for(int i = 0 ; i < 3; i++)
        {
            if(howmany[myNum[i]-'0']) res[1]++;
        }
        for(int i = 0; i < 3; i++)
        {
            if(num[i] == myNum[i]) res[0]++;
        }
        res[1] -= res[0];
    }

} info;

int NumberBaseBall()
{
    info.init();
    int n;
    cin >> n;
    char num[4];
    int res[2];
    for(int i = 0 ; i < n; i++)
    {
        cin >> (char*)num >> res[0] >> res[1];
        info.eliminate(num,res); 
    }
    cout << info.getRes() << '\n';
    
    return 0;
}