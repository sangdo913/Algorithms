#include <stdio.h>//µ¿1 ¼­2 ºÏ3 ³²4
#include <queue>
using namespace std;
struct dice {
   int top;
   int bottom;
   int down;
   int left;
   int right;
   int up;
};
int main() {
   int N, M, x, y, K, cmd;
   int map[20][20];
   dice d;
   d.top = 0;   d.left = 0;   d.right = 0;
   d.up = 0;   d.down = 0;   d.bottom = 0;
   scanf("%d %d %d %d %d", &N, &M, &x, &y, &K);
   for (int i = 0; i < N; i++)
   {
      for (int j = 0; j < M; j++)scanf("%d", &map[i][j]);
   }
   for (int i = 0; i < K; i++)
   {
      scanf("%d", &cmd);
      if (cmd == 2) {
         if (y - 1 >= 0)
         {
            y -= 1;
            if(i!=0)printf("%d\n", d.top);
            int temp;
            temp = d.top;
            d.top = d.right;
            d.right = d.bottom;
            d.bottom = d.left;
            d.left = temp;
            if (map[x][y] == 0)map[x][y] = d.bottom;
            else
            {
               d.bottom = map[x][y];
               map[x][y] = 0;
            }
         }
      }
      else if (cmd == 1) {
         if (y + 1 < M)
         {
            y += 1;
            if (i != 0)printf("%d\n", d.top);
            int temp;
            temp = d.top;
            d.top = d.left;
            d.left = d.bottom;
            d.bottom = d.right;
            d.right = temp;
            if (map[x][y] == 0)map[x][y] = d.bottom;
            else
            {
               d.bottom = map[x][y];
               map[x][y] = 0;
            }
         }
      }
      else if (cmd == 3) {//ºÏ
         if (x - 1 >= 0)
         {
            x -= 1;
            if (i != 0)printf("%d\n", d.top);
            int temp;
            temp = d.top;
            d.top = d.down;
            d.down = d.bottom;
            d.bottom = d.up;
            d.up = temp;
            if (map[x][y] == 0)map[x][y] = d.bottom;
            else
            {
               d.bottom = map[x][y];
               map[x][y] = 0;
            }
         }
      }
      else if (cmd == 4) {
         if (x + 1 < N)
         {
            x += 1;
            if (i != 0)printf("%d\n", d.top);
            int temp;
            temp = d.top;
            d.top = d.up;
            d.up = d.bottom;
            d.bottom = d.down;
            d.down = temp;
            if (map[x][y] == 0)map[x][y] = d.bottom;
            else
            {
               d.bottom = map[x][y];
               map[x][y] = 0;
            }
         }
      }
   }
   printf("%d\n", d.top);
}