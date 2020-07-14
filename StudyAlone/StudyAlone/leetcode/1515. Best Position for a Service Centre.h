#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

double f(vector<vector<int>>& p, double x, double y){
    double res = 0;
    for(int i = 0; i < p.size(); ++i) {
        double x1 = (double)p[i][0]- x;
        double y1 = (double)p[i][1]-y;
        res += sqrt(x1*x1 +y1*y1);
    }
    return res;
}
vector<vector<int>> p;
double myx, myy, myf;

void myget(double x, double y, double e){
    double pl = e/10;
    for(double xx = x-e; xx <= x +e; xx += pl){
        for(double yy = y-e; yy <= y+e; yy+= pl){
            double v = f(p, xx, yy);
            if(v < myf){
                myx = xx;
                myy = yy;
                myf = v;
            }
        }
    }
}

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        p = positions;
        double xmin = 0, xmax = 100, ymin = 0, ymax = 100;
        int cnt = 100;
        myx = (xmin+xmax)/2, myy = (ymin+ymax)/2;
        myf = f(positions,myx,myy);
        double e = 100;
        while(e >= 10e-5){
            myget(myx,myy,e);
            e/=10;
        }
        
        return myf;
    }
};