#include<cstdio>

using namespace std;

int getNum(char* str)
{
    switch(str[0])
    {
        case 'Z':
        return 0;

        case 'O':
        return 1;

        case 'T':
        if(str[1] == 'W') return 2;
        else if(str[1] == 'H') return 3;

        case 'F':
        if(str[1] == 'O') return 4;
        else if(str[1] == 'I') return 5;

        case 'S':
        if(str[1] == 'I') return 6;
        else if(str[1] == 'V') return 7;

        case 'E':
        return 8;

        case 'N':
        return 9;
    }
}

int GNS_Level3()
{
    const char nums[10][4] = {"ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN"};

    int t;
    scanf("%d\n", & t);
    char in[4];

    for(int tc = 1; tc <= t; tc++)
    {
        int n, garbage, count[10] = {0};

        scanf("#%d %d\n", &garbage, &n);
        
        printf("#%d ", tc);

        while(n--)
        {
            scanf("%s \n", in);
            count[getNum(in)]++;
        }


        for(int i = 0 ; i < 10; i++)
        {
            while(count[i]--)
                printf("%s ", nums[i]);
        }
        printf("\n");
    }
    return 0;
}