#define mymax(a, b) ((a)>(b)?(a):(b))
#define mymin(a, b) ((a)<(b)?(a):(b))

int get_score(int a[5]) {
   int num_cnt[6] = { 0 }; // k 가 등장한 횟수
   int cnt_num[6] = { 0 }; // k 번 나온 숫자의 수
   int max_cnt = 1; // 가장 많이 등장한 수의 횟수
   for (int i = 0; i < 5; i++) {
      num_cnt[a[i]]++;
      cnt_num[num_cnt[a[i]]]++;
      if (max_cnt < num_cnt[a[i]])
         max_cnt = num_cnt[a[i]];
   }
   if (max_cnt == 3) {// 우선순위 2
      int max_value = -1;
      int min_value = 6;
      for (int i = 1; i <= 5; i++)
         if (num_cnt[i] == 1 || num_cnt[i] == 2) {
            max_value = mymax(i, max_value);
            min_value = mymin(i, min_value);
         }
      return 400000 + 10 * max_value + min_value;
   }
   else if (max_cnt == 2 && num_cnt[2] == 2) {
      for (int i = 0; i < 4; i++)
         for (int j = i + 1; j < 5; j++)
            if (a[i] < a[j]) {
               int tmp = a[i];
               a[i] = a[j];
               a[j] = a[i];
            }
      int p = 0;
      for (int i = 0; i < 5; i++) {
         p *= 10;
         p += a[i];
      }
      return p + 300000;
   }
   else if (max_cnt == 2) {
      for (int i = 0; i < 4; i++)
         for (int j = i + 1; j < 5; j++)
            if (a[i] < a[j]) {
               int tmp = a[i];
               a[i] = a[j];
               a[j] = a[i];
            }
      int p = 0;
      for (int i = 0; i < 5; i++) {
         p *= 10;
         p += a[i];
      }
      return p + 200000;
   }

   else if (max_cnt == 4) {
      for (int i = 1; i <= 5; i++)
         if (num_cnt[i] == 1)
            return 500000 + i;
   }
   else if (max_cnt == 1) {
      return 1;
   }
   else if (max_cnt == 5) {
      return 0;
   }
}
bool equal(int a0[5], int b0[5], int a1[5], int b1[5]) {
   for (int i = 0; i < 4; i++) {
      for (int j = i + 1; j < 5; j++) {
         if (a0[i] < a0[j]) {
            int tmp = a0[i];
            a0[i] = a0[j];
            a0[j] = tmp;

            tmp = a1[i];
            a1[i] = a1[j];
            a1[j] = tmp;
         }
         if (b0[i] < b0[j]) {
            int tmp = b0[i];
            b0[i] = b0[j];
            b0[j] = tmp;

            tmp = b1[i];
            b1[i] = b1[j];
            b1[j] = tmp;
         }
      }
   }
   int a = 0;
   int b = 0;
   for (int i = 0; i < 5; i++) {
      a *= 10;
      a += a1[i];
      b *= 10;
      b += b1[i];
   }
   return a == b;
}


bool preprocessed = false;
int memo_score[3125];

int test(char *A[1000000][5], char *B[1000000][5])
{
   if (!preprocessed) {
      int a[5]; int ca[5];
      for (a[0] = 1; a[0] <= 5; a[0]++)
         for (a[1] = 1; a[1] <= 5; a[1]++)
            for(a[2] = 1; a[2] <= 5; a[2]++)
               for (a[3] = 1; a[3] <= 5; a[3]++)
                  for (a[4] = 1; a[4] <= 5; a[4]++) {
                     for (int i = 0; i < 5; i++) ca[i] = a[i];
                     int score = get_score(ca);
                     int idx = 0;
                     for (int i = 0; i < 5; i++) {
                        idx *= 5;
                        idx += (a[i] - 1);
                     }
                     memo_score[idx] = score;
                  }
      preprocessed = true;
   }

   int ans = 1000000;
   register int a; register int b;
   int a0_score, b0_score, a1_score, b1_score;
   for (int c = 0; c < 1000000; c++) {
      a = b = 0;
      for (int i = 0; i < 5; i++) {
         a *= 5;
         a += (A[c][i][0] - '1');
         b *= 5;
         b += (B[c][i][0] - '1');
      }
      a0_score = memo_score[a];
      b0_score = memo_score[b];
      if (a0_score != b0_score)
         continue;

      a = b = 0;
      for (int i = 0; i < 5; i++) {
         a *= 5;
         a += (A[c][i][1] - '1');
         b *= 5;
         b += (B[c][i][1] - '1');
      }
      a1_score = memo_score[a];
      b1_score = memo_score[b];
      if (a1_score != b1_score)
         continue;
      
      if (a0_score == 1 && b0_score == 1 && a1_score == 1 && b1_score == 1) { // 모두 우선순위가 5 인 경우
         int a0[5]; int a1[5]; int b0[5]; int b1[5];
         for (int i = 0; i < 5; i++) {
            a0[i] = A[c][i][0] - '0';
            b0[i] = B[c][i][0] - '0';
            a1[i] = A[c][i][1] - '0';
            b1[i] = B[c][i][1] - '0';
         }
         if (!equal(a0, b0, a1, b1))
            continue;
      }
      
      ans--;
   }
   return ans;
}