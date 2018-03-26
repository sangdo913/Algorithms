#include<iostream>

using namespace std;

struct RollDice_Dice
{
    int n; int m;
    int up,down,left,right,front,rear;
    int map[22][22];
    int positionX;
    int positionY;
    
    const int dx[5] = {0,1,-1,0,0};
    const int dy[5] = {0,0,0,-1,1};

    RollDice_Dice()
    {
        for(int i =0;i<22;i++)
        {
            for(int j = 0 ; j<22; j++) map[i][j] = -1;
        }
        down = left = right = front = rear = up = 0;
    }
    int print()
    {
       cout << up <<'\n'; 
    }
    
    void change()
    {
        if(map[positionY][positionX])
        {
            down = map[positionY][positionX];
            map[positionY][positionX] = 0;
        }
        else
        {
            map[positionY][positionX] = down;
        }
    }
    bool roll(int d)
    {
        int nextX = positionX + dx[d], nextY = positionY + dy[d];
        
        if(map[nextY][nextX] == -1) return false ;
        positionX = nextX;
        positionY = nextY;
        int temp;
        temp = up;
        switch(d)
        {
            case 1:
            up = left; left = down; down = right;
            right = temp;
            break;
            case 2:
            up = right; right = down; down = left;
            left = temp;
            break;
            case 3:
            up = front; front = down; down = rear;
            rear = temp;
            break;
            case 4:
            up = rear; rear = down; down = front;
            front = temp;
            break;


        }
        change();
        print();
    }
} RollDice_dice;

int RollDice()
{
    int k;
    int **map = (int**)RollDice_dice.map;
    int&n = RollDice_dice.n;
    int &m = RollDice_dice.m;
    cin >> RollDice_dice.n >> RollDice_dice.m >> RollDice_dice.positionY >> RollDice_dice.positionX >> k;
    RollDice_dice.positionX++; RollDice_dice.positionY++;
    
    for(int i = 1 ; i<=n;i++)
    {
        for(int j = 1 ; j<=m; j++)
        {
            cin >> ((int(*)[22])map)[i][j];
        }
    }
    int comm;
    for(int i  = k;i--;)
    {
        cin >> comm;
        RollDice_dice.roll(comm);
    }
    return 0;
}