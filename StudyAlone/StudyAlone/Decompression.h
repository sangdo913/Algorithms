#include<cstdio>
#include<cstring>

struct Decompress
{
    int n;
    
    char alpha[10];
    int size[10];

    void init()
    {
        scanf("%d\n", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%c %d\n", &alpha[i], &size[i]);
        }
    }

    void print()
    {
        int col = 1;
        for(int i = 0; i < n; i++)
        {
            while(size[i]--)
            {
                printf("%c", alpha[i]);
                if(col++ % 10 == 0) printf("\n");
            }
        }
    }
}info;

int Decompression()
{
    int t;
    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        info.init();
        printf("#%d\n", tc);
        info.print();
    }
    return 0;
}