#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>

using namespace std;

int BinaryGame()
{
    int n;
    scanf("%d",&n);
    int res = 0;
    int limit = sqrt(n);
    for(int i = 1 ; i<=limit; i++)
    {
        if( n%i == 0) 
        {
            res += i + n/i;
        }
    }
    if(limit*limit == n) res-=limit;
    printf("%d\n",res*5-24);
    return 0;
}