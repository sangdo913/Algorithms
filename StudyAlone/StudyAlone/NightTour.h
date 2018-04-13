#include<iostream>
#include<cstring>

using namespace std;

struct Info{
    bool map[6][6];
    const int dc[8] = {1,2,2,1,-1,-2,-2,-1};
    const int dr[8] = {-2,-1,1,2,2,1,-1,-2};
    typedef struct cod{int r,c;} cod;
    cod check(cod c1, cod c2)
    {
        cod next;
        for(int d = 0; d < 8; d++)
        {
            next.r = c1.r + dr[d];
            next.c = c1.c + dc[d];
            if(next.r == c2.r && next.c == c2.c) return next;
        }
        next.r = -1; next.c = -1;
        return next;
    }

    bool init()
    {
        char comm[2];
        cod pos[36], res;
        int cnt = 35;
        int index = 0;
        cin >> comm[0] >> comm[1];

        pos[0].r = comm[0] - 'A';
        pos[0].c = comm[1] - '0' - 1;
        while(cnt--)
        {
            cin >> comm[0] >> comm[1];

            pos[index + 1].r = comm[0] - 'A';
            pos[index + 1].c = comm[1] - '0' -1 ;
            res = check(pos[index],pos[index+1]);
            if(res.r != -1 && !map[res.r][res.c])
            {
                map[res.r][res.c] = true;
                index++;
                continue;   
            }
            return false;
        }
        res = check(pos[0], pos[35]);
        if(res.r == -1 ) return false;
        return true;
    }

} info;
int NightTour()
{
    char res[2][8] ={"Invalid", "Valid"};
    int i = info.init();
    cout << res[i] << '\n';
    return 0;
}