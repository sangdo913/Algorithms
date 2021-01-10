#include<iostream>
#include<string>
#include<cstdlib>
#include<time.h>
#include<set>
#include<fstream>

using namespace std;

int main(){
    int res = 0;
    srand(time(0));
    fstream f("passwordList.txt");
    set<string> se;
    int n;
    f >> n;
    for(int i = 0; i < n; ++i){
        string in;
        f>> in;
        se.insert(in);
    }

    for(int j = 0; j< 2; ++j){
        while(true){
            string s;
            for(int i = 0; i < 5; ++i){
                s.push_back(rand()%10 + '0');
            }
            if(s[0] == '9') s[0] = (rand()%10 + '0');
            if(se.find(s) == se.end()){
                printf("%s\n", s.c_str());
                se.insert(s);
                break;
            }
        }
    }
    f.close();
    ofstream of("passwordList.txt");
    of << se.size() << '\n';
    for(auto str : se){
        of << str << '\n';
    }

    // for(int i = 0; i < 100; ++i){
    //     srand(time(0));
    //     int n = 69471;
    //     int cnt = 0;
    //     while(true){
    //         int j = rand()*rand()%100000;
    //         cnt++;
    //         if(n == j) break;
    //     }
    //     res+=cnt;
    //     printf("%d\n",cnt);
    //     _sleep(1000);
    // }
    // printf("avg: .5%lf\n", res/100.0);
    return 0;
}