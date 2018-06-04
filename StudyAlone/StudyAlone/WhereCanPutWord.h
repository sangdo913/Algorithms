#include<iostream>
#include<cstring>

using namespace std;

struct Info
{
    typedef struct cod { int r, c; } cod;
    
    bool map[17][17];

    int n, k, wordNum;
    cod wordPos[225];

    void init()
    {
        cin >> n >> k;
        wordNum = 0;
        memset(map,false,sizeof(map));

        for(int r = 1; r <= n; r++)
        {
            for(int c = 1; c <= n; c++)
            {
                cin >> map[r][c];
                if(map[r][c])
                {
                    if(!map[r-1][c] || !map[r][c-1])
                    {
                        wordPos[wordNum].r = r;
                        wordPos[wordNum++].c = c;
                    }

                }
            }
        }
    }

    int getWord(cod p)
    {
        bool canMake = false;
        int res = 0;

        if(!map[p.r - 1][p.c])
        {
            canMake = true;
            for(int r = 0; r < k; r++)
            {
                if(!map[p.r + r][p.c]) 
                {
                    canMake = false;
                    break;
                }
                else if(r == k - 1 && map[p.r + k][p.c]) canMake = false;
            }
            res += canMake;
        }


        if(!map[p.r][p.c - 1])
        {
            canMake = true;

            for(int c = 0; c < k; c++)
            {
                if(!map[p.r][p.c + c]) 
                {
                    canMake = false;
                    break;
                }
                else if(c == k - 1 && map[p.r][p.c + k]) canMake = false;
            }
            res += canMake;                
        }
    
        return res;
    }
    int getWordNum()
    {
        int res = 0;
        for(int i = 0; i < wordNum; i++)
        {
            res += getWord(wordPos[i]);
        }
        return res;
    }
    
} info;

int WhereCanPutWord()
{
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        cout << '#' << tc << ' ' << info.getWordNum() << '\n';
    }
    return 0;
}