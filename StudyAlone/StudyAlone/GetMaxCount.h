#include<cstdio>

int GetMaxCount()
{
    int t;

    for(int tc = 0; tc < 10; tc++)
    {
        int score;
        int scores[101] = {0};
        scanf("%d\n", &t);

        for(int i = 0; i < 1000; i++)
        {
            scanf("%d ", &score);
            scores[score]++;
        }
        
        int maxScore = 0;
        for(int i = 1; i < 101; i++)
        {
            maxScore = scores[i] < scores[maxScore] ? maxScore : i;
        }

        printf("#%d %d\n", t, maxScore);
    }
    return 0;
}