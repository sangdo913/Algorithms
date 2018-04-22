#include<cstdio>

using namespace std;

int PrintReverse()
{
    int n;
    scanf("%d\n", &n);

    while(n)
    {
        printf("%d ", n);
        n--;
    }
    printf("\n");
    return 0;
}