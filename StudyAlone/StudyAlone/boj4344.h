//평균은 넘겠지
//https://www.acmicpc.net/problem/4344
#include<iostream>

using namespace std;


int Do(){
    int n, c;
    cin >> c;

    int score[1000];

    while(c--){
        cin >> n;
        double sum = 0;

        for(int i = 0; i < n; i++) {
            cin >> score[i];
            
            sum+= score[i];
        }

        double avg = sum / n;

        int num = 0;
        for(int i = 0 ; i < n; i++) num += avg < score[i];

        cout.setf(ios_base::fixed);
        cout.precision(3);
        cout << (double)num / n * 100 <<'%'<< '\n';
    }

    return 0;
}