#include<cstring>
#include<cstdio>

struct YeongJoonCardCounting
{
    char cards[1001];
    int conv[255];
    int count[4];
    typedef enum nums {S = 0, D = 1, H = 2, C = 3} nums;
    bool cardCount[4][14];

    int length()
    {
        int i = 0;
        while(cards[i])
        {
            i++;
        }
        return i;
    }

    bool check(int i)
    {
        int num = (cards[i + 1] - '0') * 10 + cards[i + 2] - '0';
        if(cardCount[conv[cards[i]]][num]) return false;

        cardCount[conv[cards[i]]][num] = true;
        count[conv[cards[i]]]--;
        return true;
    }

    int* countCard()
    {
        int len = length();
        for(int i = 0; i < len; i += 3)
        {
            if(!check(i)) return NULL;
        }

        return count;
    }

    void init()
    {
        scanf("%s\n", cards);

        count[0] = count[1] = count[2] = count[3] = 13;
        memset(cardCount,false,sizeof(cardCount));
    }
} info;

int YeongJoonCardCounting()
{
    int t;
    scanf("%d\n", &t);

    info.conv['S'] = info.S;
    info.conv['D'] = info.D;
    info.conv['C'] = info.C;
    info.conv['H'] = info.H;

    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        int *res = info.countCard();
        if(res)
        {
            printf("#%d %d %d %d %d\n", tc, res[0], res[1], res[2], res[3]);
        }
        else
        {
            printf("#%d Error\n", tc);
        }
    }
    return 0;
}