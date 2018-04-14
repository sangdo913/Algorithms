#include<iostream>
#include<cstring>

using namespace std;

struct Info
{
    int s;
    long long n;
    int numOfDigit;
    char arr[10][23][13];
    int index;
    void init()
    {
        index = 0;
        memset(arr,0,sizeof(arr));
        cin >> s >> n;

    }
    void setDigit()
    {
        numOfDigit = 0;
        while(n)
        {
            draw(numOfDigit++, n%10);
            n /= 10;
        }
    }
    void print()
    {
            for(int r = 0; r < 2*s + 3; r++)
            {
                for(int i = numOfDigit-1; i >= 0; i--)
                {
                    for(int c = 0; c < s + 3 ; c++)
                    {
                        cout << arr[i][r][c];
                    }
                }

                cout << '\n';
            }
    }

    int drawRow(bool up, bool down, char arr[23][13],int col)
    {
        int c = 1;

        for(int i = 0; i < 2*s + 3; i++) arr[i][col] = ' ';

        if(up)
            for(c = 1; c <= s; c++)
            {
                arr[c][col] = '|';
            }

        if(down)
            for(c = s + 2; c <= 2*s + 1; c++ )
            {
                arr[c][col] = '|';
            }
        return 1;
    }

    int drawCol(bool top, bool mid, bool bottom, char arr[23][13], int col)
    {
        for(int c = 0 ; c < s; c++)
        {
            for(int i = 0 ; i < 2*s + 3; i++) arr[i][col+c] = ' ';

            arr[0][col+c] = top ? '-' : ' ';
            arr[s + 1][col+c] = mid ? '-' : ' ';
            arr[2*s + 2][col+c] = bottom ? '-' : ' ';
        }

        return s;
    }

    void draw(int in, long long num)
    {
        int index = 0;
        switch(num)
        {
            case 1:
            for(int i = 0 ; i < s + 1; i++) index += drawRow(false,false,arr[in],index);
            index += drawRow(true,true,arr[in], index);
            break;
            case 2:
            index += drawRow(false,true,arr[in],index);
            index += drawCol(true,true,true,arr[in],index);
            index += drawRow(true,false,arr[in],index);
            break;
            case 3:
            index += drawRow(false,false,arr[in],index);
            index += drawCol(true,true,true, arr[in], index);
            index += drawRow(true,true,arr[in], index);
            break;

            case 4:
            index += drawRow(true,false,arr[in], index);
            index += drawCol(false,true,false,arr[in],index);
            index += drawRow(true,true,arr[in],index);
            break;

            case 5:
            index += drawRow(true,false,arr[in],index);
            index += drawCol(true,true,true,arr[in],index);
            index += drawRow(false,true,arr[in],index);
            break;

            case 6:
            index += drawRow(true,true,arr[in],index);
            index += drawCol(true,true,true,arr[in],index);
            index += drawRow(false,true,arr[in],index);
            break;

            case 7:
            index += drawRow(false,false,arr[in],index);
            index += drawCol(true,false,false,arr[in],index);
            index += drawRow(true,true,arr[in],index);
            break;

            case 8:
            index += drawRow(true,true,arr[in],index);
            index += drawCol(true,true,true,arr[in],index);
            index += drawRow(true,true, arr[in],index);
            break;

            case 9:
            index += drawRow(true,false,arr[in],index);
            index += drawCol(true,true,true,arr[in],index);
            index += drawRow(true,true,arr[in],index);
            break;
            
            case 0:
            index += drawRow(true,true,arr[in],index);
            index += drawCol(true,false,true,arr[in],index);
            index += drawRow(true,true,arr[in],index);
            break;
        }
        index += drawRow(false,false,arr[in],index);
    }
} info;

int LCDTest()
{
    info.init();
    info.setDigit();
    info.print();

    return 0;
}
