#include<iostream>

using namespace std;

int people[2][367];
int conv[256];
int ans1, ans2, ans3, ans4, ans5; 

#define MAX(x, y) ((x) > (y) ? (x) : (y))

int Do(){
    conv['S'] = 0;
    conv['T'] = 1;

    int n;
    cin >> n;

    while(n--){
        char s; int f, t;
        cin >> s >> f >> t;

        ans5 = MAX(ans5, t - f + 1);

        for(int i = f; i <= t; i++){
            if(people[0][i] == 0 && people[1][i] == 0) ans1++;
            people[conv[s]][i]++;
        }
    }

    for(int i = 1; i <= 366; i++){
        ans2 = MAX(ans2, people[0][i] + people[1][i]);
        if(people[0][i] == people[1][i] && people[0][i]){
            ++ans3;
            ans4 = MAX(ans4 , people[0][i] + people[1][i]);
        }
    }

    cout << ans1 << '\n' << ans2 << '\n' << ans3 << '\n' << ans4 << '\n' << ans5;
    return 0;
}