#include<iostream>

using namespace std;

struct CubePaint
{
    long long x; long long y; long long z;
    long long a; long long b; long long c;
    int n;

    long long prev[1000];
    long long next[1000];
    void init()
    {
        cin >> x >> y >> z >> a >> b >> c >> n;

        for(int i = 0; i<n;i++)
        {
            prev[i] = 0;
            next[i] = 0;
        }
        prev[0] = 1;
    }

    void setNum(long long size,long long st, long long end)
    {
        long long num = end-st;
        long long share = num / n;
        long long r = num % n;
        long long temp[1000] = {0};

        for(int i = 0; i<n;i++)
        {
            temp[i] +=  share*size;
            if(share > 0) temp[i]-= prev[i];
            
            if(r) 
                for(int j = share == 0 ? 1 : 0; j<r; j++)
                {
                    temp[(i+j)%n] += prev[i];
                }
        }
        for(int i = 0 ; i<n;i++) next[i]+= temp[i];
    }

    void change()
    {
        for(int i = 0 ; i<n;i++) 
        {
            prev[i] = next[i];
            next[i] = 0;
        }
    }

    void plusPrev()
    {
        for(int i = 0 ; i<n;i++)
        {
            next[i]+= prev[i];
        }
        change();
    }

    void print(int tc)
    {
        cout <<'#' << tc;
        for(int i = 0 ; i <n; i++)
        {
            cout << ' ' << prev[i];
        }
        cout<< '\n';
    }

} CubePaint_info;

int CubePaint()
{
    int T;
    cin >> T;
    for(int tc=1;tc<=T;tc++)
    {
        CubePaint_info.init();
        long long &a = CubePaint_info.a;
        long long &b = CubePaint_info.b;
        long long &c = CubePaint_info.c;

        long long &x = CubePaint_info.x;
        long long &y = CubePaint_info.y;
        long long &z = CubePaint_info.z;

        CubePaint_info.setNum(1,a,x);
        CubePaint_info.setNum(1,0,a+1);
        CubePaint_info.plusPrev();

        CubePaint_info.setNum(x,b,y);
        CubePaint_info.setNum(x,0,b+1);
        CubePaint_info.plusPrev();

        CubePaint_info.setNum(x*y,c,z);
        CubePaint_info.setNum(x*y,0,c+1);
        CubePaint_info.plusPrev();

        CubePaint_info.print(tc);
    }
    return 0;
}