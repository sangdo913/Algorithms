#include <string>
#include<iostream>
#include <vector>

#define ABS(a) (a) > 0 ? (a) : -(a)
using namespace std;

int solution(vector<int> cards) {
    int answer = -1;
    int sum = 0;
    for(int i = 0; i < cards.size();){
        int turn = 0;
        int me = 0;
        int d = 0;
        int show = 0;
        bool vs = true;
        if(i+4 > cards.size()) break;
        int card = cards[i++];
        if(card > 10) card = 10;
        if(card == 1) card = 11;
        me = card;
        card = cards[i++];
        if(card > 10) card = 10;
        if(card == 1) card = 11;
        d = card;
        card = cards[i++];
        if(card > 10) card = 10;
        if(card == 1 && 11 + me <= 21) card = 11;
        me += card;
        
        card = cards[i++];
        if(card > 10) card = 10;
        show = card;
        if(card == 1 && 11 + d <= 21) card = 11;
        d+= card;
        if(show == 1 || show >= 7){
            while(me < 17) {
                if(i == cards.size()){
                    vs = false;
                    break;
                }
                card = cards[i++];
                if(card > 10) card= 10;
                if(card == 1 && 11 + me <= 17) card = 11;
                me += card;
            }
        }
        while(2 <= show && show <= 3){
            while(me < 12){
                if(i == cards.size()){
                    vs = false; break;
                }
                card = cards[i++];
                if(card > 10) card = 10;
                if(card == 1 && 11 + me <= 12) card = 11;
                me+=card;
            }
        }
        if(vs == false) break;
        if(me != 21) {
            while(d < 17){
                if(i == cards.size()){
                    vs = false; break;
                }
                card = cards[i++];
                if(card > 10 ) card = 10;
                if(card == 1 && d  +11 <= 17)  card = 11;
                d += card;
            }
        }
        cout << me << ' ' << d << endl;
        int diff1 = ABS(21-me);
        int diff2 = ABS(21-d);
        if(diff1 < diff2){
            if(diff1 == 0) sum+=3;
            else sum+=2;
        }
        else if(diff1 > diff2) sum-=2;
    }
    return sum;
}

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    cin >> n;

    vector<int> vec;
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        vec.push_back(a);
    }
    cout << solution(vec) << endl;
    return 0;
}