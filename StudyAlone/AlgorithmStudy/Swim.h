#include<cstdio>
#include<cstring>

//month : �ش� ���� ��¥ ����
//price : 1�� ����, 1 �� ����, 3�� ����, 12�� ����
//nm : 1��, 1�� �����̸� �����޷� �̵�, 3�� �����̸� 3�� �̵� 
//memoi[��] : �ش� �޷� �ö����� ���� �� ���� ����
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

        // ù �޿��� ������ ����.
        //������ �޿� �׳� 12�� ��ü ���Ÿ� �����Ѵ�.
        memoi[0] = 0;
        memoi[12] = price[3];

        for(int i = 0; i < 12; i++){
            //�� ���� ���, �� ���� ���
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