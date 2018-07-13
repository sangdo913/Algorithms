#include<cstdio>
#include<cstring>

//month : 해당 달의 날짜 저장
//price : 1일 가격, 1 달 가격, 3달 가격, 12달 가격
//nm : 1일, 1달 기준이면 다음달로 이동, 3달 기준이면 3달 이동 
//memoi[달] : 해당 달로 올때까지 가장 싼 가격 저장
int month[12], memoi[13];
int price[4];
int nm[3] = {1,1,3};

int min(int i1, int i2){
    return i1 < i2 ? i1 : i2;
}

int Swim() {
    int t;
    scanf("%d\n", &t);

    for(int  tc = 1; tc <= t; tc++){
        
        for(int i = 0 ; i < 4; i++){
            scanf("%d \n", &price[i]);
        }

        for(int i = 0; i < 12; i++){
            scanf("%d \n", &month[i]);
        }
        
        for(int i = 1; i < 12; i++) memoi[i] = 987654321;

        // 첫 달에는 가격이 없다.
        //마지막 달에 그냥 12달 전체 구매를 저장한다.
        memoi[0] = 0;
        memoi[12] = price[3];

        for(int i = 0; i < 12; i++){
            //일 기준 계산, 달 기준 계산
            for(int j = 0; j < 3; j++){
                int nextM = i + nm[j];
                int p;

                p = j == 0 ? price[0] * month[i] : price[j];
                nextM = nextM > 12 ? 12 : nextM;

                memoi[nextM] =  min(memoi[nextM], memoi[i] + p);
            }
        }

        printf("#%d %d\n", tc, memoi[12]);
    }
    return 0;
}