#include<cstdio>

double ccw(double x1, double y1, double x2, double  y2){
    return (x1*y2 - x2*y1);
}
double ABS(double ll1){
    return ll1 > 0 ? ll1 : -ll1;
}
int GetSquare(){
    double x[2], y[2];
    double s = 0;
    int n;
    scanf("%d\n", &n);

    scanf("%lf %lf\n%lf %lf\n", &x[n%2], &y[n%2], &x[(n+1)%2], &y[(n+1)%2]);
    s += ccw(x[n%2],y[n%2], x[(n+1)%2],y[(n+1)%2]);    
    n-=2;
    while(n--){
        scanf("%lf %lf\n", &x[(n+1)%2], &y[(n+1)%2]);
        s += ccw(x[n%2], y[n%2], x[(n+1)%2], y[(n+1)%2]);
    }
    printf("%.1lf\n", (double)(ABS(s))/2.0);
    return 0;
}