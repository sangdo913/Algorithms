#include<cstdio>

int View()
{
    int t = 10, n;
    int arr[1000];
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%d\n", &n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d ", arr + i);
        }

        int res = 0;

        for(int i = 2; i < n - 2; i++)
        {
            int max = arr[i - 2];
            max = max > arr[i - 1] ? max : arr[i - 1];
            max = max > arr[i + 1] ? max : arr[i + 1];
            max = max > arr[i + 2] ? max : arr[i + 2];
            
            res += arr[i] > max ? arr[i] - max : 0;
        }
        
        printf("#%d %d\n", tc, res);
    }


    return 0;
}