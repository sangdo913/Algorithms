#include<cstdio>

int CannotSeeMotherPhabet()
{
    bool motherPhabet[255] = {false};
    motherPhabet['a'] = motherPhabet['e'] = motherPhabet['i'] = motherPhabet['o'] = motherPhabet['u'] = true;

    int t;
    char str[51], res[50];
    scanf("%d\n", &t);

    for(int tc = 1; tc <= t; tc++)
    {
        int len = 0,i = 0;

        scanf("%s\n", str);

        while(str[i])
        {
            if(!motherPhabet[str[i]])
            {
                res[len++] = str[i];
            }
            i++;
        }
        printf("#%d ", tc);
        for(int i = 0; i < len; i++)
        {
            printf("%c", res[i]);
        }
        printf("\n");
    }

    return 0;
}