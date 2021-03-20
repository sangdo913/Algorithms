extern int check(unsigned char *key);

int valid[200];
int valid_sz;

int left[100], right[100];
int left_sz, right_sz;

unsigned char call_key[85000][200];
int call_key_cnt = 0;

void test(unsigned char *key)
{
    register int response;

    // 유효한 idx를 valid에 집어넣음.
    {
        for (register int i = 0; i < 200; ++i) valid[i] = i;
        valid_sz = 200;
    }

    left_sz = right_sz = 0;

    for (register int i = 1; i <= 255; ++i)
    {
        for (register int j = 0; j < 100; ++j) call_key[call_key_cnt][j] = i;
        response = check(call_key[call_key_cnt]);
        
        int pos = response >> 8;
        int equ = response & 0xFF;

        if (pos == 1) left[left_sz++] = i;
        else if (equ == 100) right[right_sz++] = i;

        ++call_key_cnt;
    }

    for (register int i = 0; i < 100; i++)
    {
        int first_num = left[i];
        int second_num = right[i];

        register int first_st = 0, first_ed;
        register int second_st, second_ed = valid_sz - 1;

        first_ed = (first_st + second_ed) >> 1;
        second_st = first_ed + 1;

        while (first_st < first_ed || second_st < second_ed)
        {
            register int first_mid = (first_st + first_ed) >> 1;
            register int second_mid = (second_st + second_ed) >> 1;

            for (register int j = first_st; j <= first_mid; ++j) call_key[call_key_cnt][valid[j]] = first_num;
            for (register int j = second_st; j <= second_mid; ++j) call_key[call_key_cnt][valid[j]] = second_num;
            
            response = check(call_key[call_key_cnt]) >> 8;

            if (response == 2) first_ed = first_mid, second_ed = second_mid;
            else if (response == 0) first_st = first_mid + 1, second_st = second_mid + 1;
            else
            {
                if (first_st == first_ed) second_st = second_mid + 1;
                else if (second_st == second_ed) first_st = first_mid + 1;
                else
                {
                    ++call_key_cnt;
                    for (register int j = first_st; j <= first_mid; ++j) call_key[call_key_cnt][valid[j]] = first_num;
                    response = check(call_key[call_key_cnt]) >> 8;

                    if (response == 1)
                    {
                        first_ed = first_mid;
                        second_st = second_mid + 1;
                    }
                    else
                    {
                        first_st = first_mid + 1;
                        second_ed = second_mid;
                    }
                }
            }

            ++call_key_cnt;
        }

        key[valid[first_st]] = first_num, key[valid[second_st]] = second_num;
        for (register int j = first_st; j < second_st - 1; ++j) valid[j] = valid[j + 1];
        for (register int j = second_st - 1; j < valid_sz - 2; ++j) valid[j] = valid[j + 2];
        valid_sz -= 2;
    }
}
