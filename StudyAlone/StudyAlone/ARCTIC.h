#include<iostream>

using namespace std;
int  n; 
double x[100], y[100];
int p[100];
int getp(int i){
    if(p[i] < 0) return i;
    else return p[i] = getp(p[i]);
}

void join(int a, int b){
    int pa = getp(a), pb = getp(b);
    if(p[pa] > p[pa]){
        pa^=pb^=pa^=pb;
    }
    p[pa] += p[pb];
    p[pb] = pa;
}
double cald(int a, int b){
    return (x[a] - x[b])*(x[a]-x[b]) + (y[a]-y[b])*(y[a]-y[b]);
}

bool decision(double d){
    for(int i = 0; i < n; ++i) p[i] = -1;
    for(int i = 0; i < n; ++i) for(int j = 0;j < n;++j){
        if(i==j )continue;
        double dist = cald(i,j);
        int pi = getp(i), pj = getp(j);
        if(dist <= d && pi != pj) join(i,j);
    }

    for(int i = 1; i < n; ++i) if(getp(i) !=getp(0)) return false;
    return true;
}

double bs(){
    double s = 0, e = 1e10, m = (s+e)/2;

    for(int i = 0; i < 100; ++i){
        m = (s+e)/2;
        if(decision(m)) e =m;
        else s = m;
    }
    return m;
}
double root(double n){
    double s = 0, e = n, m = (s+e)/2;
    for(int i = 0; i < 100; ++i){
        m = (s+e)/2;
        if(m*m > n) e = m; 
        else s  = m;
    }
    return m;
}


int Do(){
    int c;
    cin >> c;
    cout.setf(ios_base::fixed);
    cout.precision(2);
    while(c--){
        cin >> n;
        for(int i = 0; i < n; ++i) cin >> x[i] >> y[i];
        cout << root(bs()) << '\n';
    }
    return 0;
}