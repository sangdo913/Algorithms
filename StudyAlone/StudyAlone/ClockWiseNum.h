#include<cstring>
#include<iostream>

using namespace std;

int ClockWiseNum()
{
    int arr[7][7];
    int clockWiseArr[7][7];
    int t;
    int resArr[7][21];
    cin >> t;

    for(int tc = 1; tc <= t; tc++)
    {
        int n;
        cin >> n;

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> arr[i][j];


        int resCol = 0;
        for(int cnt = 0; cnt < 3; cnt++, resCol += n)
        {
            for(int i = 0; i < n; i++)
            {
                int nowRow = n - 1;
                for(int j = 0; j < n; j++, nowRow--)
                {
                    clockWiseArr[i][j] = arr[nowRow][i];            
                }
            }

            memcpy(arr,clockWiseArr,sizeof(arr));
            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n; j++)
                {
                    resArr[i][resCol + j] = arr[i][j];
                }
            }
        }

        cout << '#' << tc << '\n';
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < 3 * n; j++)
            {
                cout << resArr[i][j];
                if(j % n == n - 1) cout << ' ' ;                
            }
            cout << '\n';
        }
    }
    return 0;
}