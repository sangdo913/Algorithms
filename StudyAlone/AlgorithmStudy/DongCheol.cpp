#include<cstdio>
#include<cstring>

double p[16][16];
double memoi[16][1<<16];
int n;

double max(double d1, double d2)
{
    return d1 > d2 ? d1 : d2;
}

double maxP(int now, int visit){
    if(now == n){
        return 1;
    }

    double &ret = memoi[now][visit];
    if(ret >= -1){
        return ret;
    }

    ret = 0;
    for(int i = 0; i < n; i++){
        if(visit & (1 << i)) continue;
        
        int nv = visit | (1 << i);
        
        ret = max(ret, maxP(i, nv) * p[now][i]);
    }

    return ret;
}

int main()
{
    int tc;
    scanf("%d\n", &tc);

    for(int  t = 1; t <= tc; t++){
        scanf("%d\n", &n);
    
    }
    return 0;
}