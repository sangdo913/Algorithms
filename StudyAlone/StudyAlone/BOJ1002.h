#include<iostream>
#include<cmath>
using namespace std;

#define DIST(x,y) (((x)-(y))*((x)-(y)))

int Do(){
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

    int tc;
    cin >> tc;
    while(tc--){
        int x1, y1, r1, x2, y2, r2;

        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        if(x1 == x2 && y1 == y2){
            if(r1 == r2) cout << -1 << '\n';
            else cout << 0 << '\n';
        }
        else{
            int d = DIST(x1,x2) + DIST(y1, y2);
            int d2 = (r1+r2)*(r1+r2);
            if(d == d2){
                cout << 1 << '\n';
            }
            else if(d > d2){
               cout << 0 << '\n'; 
            }
            else{
                double dd1 = sqrt((double)d) + (double)r1;
                double dd2 = sqrt((double)d) + (double)r2;
                if(dd1 < (double)r2 || dd2 < double(r1)){
                    cout << 0 << '\n';
                }
                else if(dd1 == (double)r2 || dd2 == (double)r1) cout << 1 << '\n';
                else cout << 2 << '\n';
            }
        }
    }
    return 0;
}