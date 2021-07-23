// #include <bits/stdc++.h>
#include "user2.cpp"
#include<math.h>
#include<ctime>
#include<cstdio>

double coord[100000][3];
double coord1[100000][3];
int result[3] = {};
// extern void test(double coord[100000][3], int result[3]);
// extern void uest(double coord[100000][3], int result[3]);

static double mpow(double a) {
   return a * a;
}

   static unsigned long long seed = 5;
static unsigned short mrand() {
   return (unsigned short)((seed = (seed * 25214903917ULL + 11ULL)) >> 16);
}

double msqrt(double x) {
   return sqrt(x);
}

int main() {
   srand(time(nullptr));
    double base_cost = 0;
    double cost1 = 0;
    double cost2 = 0;
    int test_case = 1;
    for (register int k = 0; k < test_case; ++k) {
        seed = mrand();
        int cnt[17] = {};
        for (register int i = 0; i < 100000; ++i) {
            coord[i][0] = coord1[i][0] = mrand() / double(mrand() + 1);
            coord[i][1] = coord1[i][1] = mrand() / double(mrand() + 1);
            coord[i][2] = coord1[i][2] = mrand() / double(mrand() + 1);
            cnt[int(coord[i][0]) / (60000/17)]++;
        }

        printf("Test%d : ", k + 1);

        for (register int i = 0; i < 100000; ++i) {
            double min_dist = 1e15;
            for (register int j = 0; j < 3; ++j) {
                double dist = mpow(coord[i][0] - coord[result[j]][0]) + \
                    mpow(coord[i][1] - coord[result[j]][1]) + \
                    mpow(coord[i][2] - coord[result[j]][2]);

                if (dist < min_dist)
                min_dist = dist;
            }
            base_cost += msqrt(min_dist);
        }

        test(coord1, result);
        for (register int i = 0; i < 100000; ++i) {
            double min_dist = 1e15;
            for (int j = 0; j < 3; ++j) {
                double dist = mpow(coord[i][0] - coord[result[j]][0]) + \
                    mpow(coord[i][1] - coord[result[j]][1]) + \
                    mpow(coord[i][2] - coord[result[j]][2]);

                if (dist < min_dist)
                min_dist = dist;
            }
            cost1 += msqrt(min_dist);
        }
    }
    printf("base : %lf\n", base_cost / test_case);
    printf("result1 : %lf\n", cost1 / test_case);
}
   