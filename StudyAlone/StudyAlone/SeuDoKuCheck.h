#include<iostream>

using namespace std;

struct Info{
    int map[9][9];
    void init()
    {
        for(int r = 0; r < 9; r++)
        {
            for(int j = 0; j < 9; j++)
            {
                cin >> map[r][j];
            }
        }
    }

    bool checkSuDoKu()
    {
        bool checkArr[10] = {false};

        bool result = true;
        for(int r = 0; r < 9; r++)
        {
            for(int c = 0; c < 9; c++)
            {
                if(checkArr[map[r][c]]) return false;
                checkArr[map[r][c]] = true;
            }

            memset(checkArr,false,sizeof(checkArr));
        }

        for(int c = 0 ; c < 9; c++)
        {
            for(int r = 0; r < 9; r++)
            {
                if(checkArr[map[r][c]]) return false;
                checkArr[map[r][c]] = true;
            }

            memset(checkArr,false,sizeof(checkArr));
        }

        for(int r = 0; r < 9; r+= 3)
        {
            for(int c = 0; c < 9; c+= 3)
            {
                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0 ; j < 3; j++)
                    {
                        if(checkArr[map[r + i][c + j]]) return false;
                        checkArr[map[r + i][c + j]] = true;
                    }
                }

                memset(checkArr,false,sizeof(checkArr));
            }
        }

        return true;
    }
} info;

int SeuDOKuCheck()
{
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int res = info.checkSuDoKu();
        cout << '#' << tc << ' ' << res << '\n';
    }
    return 0;
}