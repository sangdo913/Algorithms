#include<cstdio>

float pow(float a, int cnt)
{
    float res = 1;
    while(cnt--)
    {
        res *= a;
    }
    return res;
}

int CompletePrimeThings()
{
    int t;
    scanf("%d\n", &t);

    float a, b;

    float comb18[19];
    float prime[7] = {2,3,5,7,11,13,17};
    for(int i = 0; i <= 18; i++)
    {
        comb18[i] = 1;
        for(int j = 0; j < i; j++)
        {
            comb18[i] *= (18 - j);
            comb18[i] /= j + 1;
        }
    }

    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%f %f\n", &a, &b);
        a /= 100.f;
        b /= 100.f;

        float revA = 1 - a;
        float revB = 1 - b;
        float prob = 0;
        float probA = 0;
        float probB = 0;
        for(int i = 0 ; i < 7; i++)
        {
            probA += comb18[(int)prime[i]]*pow(a,prime[i])*pow(revA, 18 - prime[i]);
            probB += comb18[(int)prime[i]]*pow(b,prime[i])*pow(revB, 18 - prime[i]);
        }
        prob = probA + probB - probA * probB;
        printf("#%d %f\n", tc, prob);
    }

    return 0;
}