#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
int path[7][7] = {
    {28, 20, 16, 13, 9, 5},
    {5,4,3,2,1,0},
    {0,8,12,15,19,23},
    {23,24,25,26,27,28},
    {5,7,11,14,17,21,23},
    {0,6,10,14,18,22,28}
};

int size[7] = {5,5,5,5,6,6};

struct COD{
    int r, c;
    void set(int a, int b){
        r = a; c = b;
    }
    COD(){
        r = c = 0;
    }
};

COD pos[29];

char map[32][33] ={
   "..----..----..----..----..----..",
"..    ..    ..    ..    ..    ..",
"| \\                          / |",
"|  \\                        /  |",
"|   \\                      /   |",
"|    ..                  ..    |",
"..   ..                  ..   ..", 
"..     \\                /     ..", 
"|       \\              /       |", 
"|        \\            /        |", 
"|         ..        ..         |", 
"|         ..        ..         |", 
"..          \\      /          ..", 
"..           \\    /           ..", 
"|             \\  /             |", 
"|              ..              |", 
"|              ..              |", 
"|             /  \\             |", 
"..           /    \\           ..", 
"..          /      \\          ..", 
"|         ..        ..         |", 
"|         ..        ..         |", 
"|        /            \\        |", 
"|       /              \\       |", 
"..     /                \\     ..", 
"..   ..                  ..   ..", 
"|    ..                  ..    |", 
"|   /                      \\   |", 
"|  /                        \\  |", 
"| /                          \\ |", 
"..    ..    ..    ..    ..    ..", 
"..----..----..----..----..----..",
};

int getgo(string s)
{
    int bnum = 0;
    for(int i = 0; i < 4; i++){
        if(s[i] == 'F'){
            bnum++;
        }
        
    }
    return bnum ? bnum : 5;
}

bool isupper(char c){
    return c >= 'A' && c<='Z';
}

int conv[256][2];

struct MAL{
    int pos;
    bool started;
    bool end;
    int path;
    int now;
    MAL(){
      pos = 28;
      started = false;
      end = false;
      path = 0;
      now = 0;  
    }
}mals[256];

void moveto(string s, int p){
    bool flag = isupper(s[0]);

    bool get = false;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            if(map[pos[p].r + i][pos[p].c + j] != '.'){
                if(flag ^ isupper(map[pos[p].r + i][pos[p].c + j]))
                {
                    get = true;
                    break;
                }
            }
        }
    }

    if(get){
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++) {
                    char &c = map[pos[p].r + i][pos[p].c + j];

                    if(c !=   '.'){
                        mals[c].started = false;
                        mals[c].now = mals[c].path ;
                        mals[c].pos = 28;
                        c = '.';
                    }
                }
        }
    }

    for(int i = 0; i < s.size(); i++){
        int dr = conv[s[i]][0];
        int dc = conv[s[i]][1];
        map[pos[p].r + dr][pos[p].c + dc] = s[i];
    }
}

string getmoves(int p){
    string res;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            char &c = map[pos[p].r+i][pos[p].c+j];
            if(c !='.' ){
                res.push_back(c);
                c = '.';
            }
        }
    }
    return res;
}

void removemal(string s){
    for(int i = 0; i < s.size(); i++){
        mals[s[i]].end = true;
    }

    for(int i = 0; i <2; i++){
        for(int j = 0; j< 2; j++){
            map[pos[28].r + i][pos[28].c + j] = '.';
        }
    }
}

int BOJ15778(){
    pos[0].set(0,0);
    pos[1].set(0,6);
    pos[2].set(0,12);
    pos[3].set(0,18);
    pos[4].set(0,24);
    pos[5].set(0,30);
    pos[6].set(5,5);
    pos[7].set(5,25);
    pos[8].set(6,0);
    pos[9].set(6,30);
    pos[10].set(10,10);
    pos[11].set(10,20);
    pos[12].set(12,0);
    pos[13].set(12,30);
    pos[14].set(15,15);
    pos[15].set(18,0);
    pos[16].set(18,30);
    pos[17].set(20,10);
    pos[18].set(20,20);
    pos[19].set(24,0);
    pos[20].set(24,30);
    pos[21].set(25, 5);
    pos[22].set(25,25);
    pos[23].set(30,0);
    pos[24].set(30,6);
    pos[25].set(30,12);
    pos[26].set(30,18);
    pos[27].set(30,24);
    pos[28].set(30,30);

    conv['a'][0] = conv['A'][0] = 0;
    conv['a'][1] = conv['A'][1] = 0;

    conv['b'][0] = conv['B'][0] = 0;
    conv['b'][1] = conv['B'][1] = 1;

    conv['c'][0] = conv['C'][0] = 1;
    conv['c'][1] = conv['C'][1] = 0;

    conv['d'][0] = conv['D'][0] = 1;
    conv['d'][1] = conv['D'][1] = 1;


    int cnt = 0;
    
    int n;
    cin >> n;

    
    while(n--){
        char mal;
        string yut;
        string gomal;

        cin >> mal  >> yut;
        if(!mals[mal].started){
            mals[mal].started = true;
            mals[mal].pos = 28;
            mals[mal].now = 0;
            mals[mal].path = 0;
            gomal.push_back(mal);
        }
        else{
            gomal = getmoves(mals[mal].pos);
        }

        int k = getgo(yut);
        if(k + mals[mal].now > size[mals[mal].path])
        {
            int resume = k + mals[mal].now - size[mals[mal].path];
            switch(mals[mal].path){
                case 0:
                case 1:
                case 2:
                    for(int i = 0; i < gomal.size(); i++){
                        mals[gomal[i]].path++;
                        mals[gomal[i]].now = resume;
                    }
                    break;
                case 3:
                case 5:
                    removemal(gomal);
                    break;
                case 4:
                    for(int i = 0; i < gomal.size(); i++){
                        mals[gomal[i]].path = 3;
                        mals[gomal[i]].now = resume;
                    }
            }
        }
        else{
            for(int i = 0; i < gomal.size(); i++){
                mals[gomal[i]].now += k;
            }
        }

        if(mals[gomal[0]].end) continue;

        for(int i = 0; i < gomal.size(); i++){
            mals[gomal[i]].pos = path[mals[gomal[i]].path][mals[gomal[i]].now];
            MAL& m = mals[gomal[i]];
            switch(m.pos){
                case 0:
                   m.path = 5;
                   m.now = 0; 
                break;
                case 5:
                    m.path = 4;
                    m.now = 0;
                break;
                case 14:
                    m.path =5;
                    m.now = 3;
                break;
            }
        }


        
        moveto(gomal, mals[mal].pos);
    }

    for(int i = 0 ; i <32 ;i++){
        for(int j = 0; j < 32; j++){
            cout << map[i][j];
        }
        cout << '\n';
    }
    return 0;
}