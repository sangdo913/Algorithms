#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;
long long people[1000000];
int TestManage()
{
    long long res = 0;
    int n;
    long long a, b;

    scanf("%d", &n);
    for(int  i = 0; i < n; i++)
        scanf("%lld", &people[i]);

    scanf("%lld %lld\n", &a, &b);

    res += n;
    for(int i = 0 ; i < n; i++)
    {
        res += (people[i] > a? people[i] - a + b-1 : 0) / b; 
    }

    printf("%lld\n", res);
    return 0;
}