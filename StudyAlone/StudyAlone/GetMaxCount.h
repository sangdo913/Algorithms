#include<cstdio>

int GetMaxCount()
{
    int t;
    scanf("%d\n", &t);


    for(int tc = 1; tc <= t; tc++)
    {
        int score;
        int scores[101] = {0};

        for(int i = 0; i < 1000; i++)
        {
            scanf("%d ", &score);
            scores[score]++;
        }
        int maxScore = 0;
        for(int i = 1; i < 1000; i++)
        {
            maxScore = scores[i] > scores[maxScore] ? i : maxScore;
        }

        printf("#%d %d\n", tc, maxScore);
    }
    return 0;
}