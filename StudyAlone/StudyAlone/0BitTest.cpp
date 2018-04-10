#include<iostream>
#include<cstdio>

using namespace std;

int getZerosNum(int n)
{
    int cnt = 0;
    //0 이면 무한루프돌음..
    if(n == 0 ) return -1;

    while((n & 1) == 0)
    {
        cnt ++;
        n >>= 1;
    }
    return cnt;
}

void printBinary(unsigned n)
{
    while(n)
    {
        printf("%d", n&1);
        n >>= 1;
    }
    printf("\n");
}

int main()
{
    typedef unsigned int ui;

    //10 C 3의 경우

    //nCr 에서 r만큼 1의 개수를 늘려준다.
    ui bit = 0b111;

    // nCr에서 n만큼 쉬프팅을 해준다.
    ui max = (1 << 10);

    int cnt = 0;

    while(bit < max)
    {
        printBinary(bit);

        cnt++;

        //temp : 가장 하위에 있는 비트의 오른쪽을 모두 1로 만든다.
        int temp = bit | (bit - 1);
        
        // 하위에 0이 몇개 있는지 살펴본다.
        int zeroNum = getZerosNum(bit);
        /*
            temp + 1 :연속된 1에서 가장 앞에있는 1을 앞으로 옮긴다. 
            ~temp & -~temp : 가장 뒤에있는 0 비트찾고, 그 자리수를 1로 만든다.
                             여기에서 1 을 빼면 가장 뒤에있는 0 비트 뒤의 모든 수를 1로 만든다.
            0의 개수만큼 뒤로 가고, 맨 앞의 1 비트를 한칸 왼쪽으로 옮겼으므로, 한칸 더 뒤로 움직인다. 
        */
        bit = (temp + 1) | (((~temp & -~temp) - 1) >> (zeroNum + 1));
    }

    printf("\n10C3의 개수 : %d\n", cnt);

    return 0;
}