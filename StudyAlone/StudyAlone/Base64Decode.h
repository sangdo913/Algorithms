#include<cstdio>

int length(char* str)
{
    int res = 0;
    while(*str)
    {
        res++;
        str++;
    }
    return res;
}

void print(const int code[4])
{
    int n = 0;
    n += code[0] << 18;
    n += code[1] << 12;
    n += code[2] << 6;
    n += code[3];

    char alpha[3];
    alpha[0] = (n & 0b111111110000000000000000) >> 16;
    alpha[1] = (n & 0b1111111100000000) >> 8;
    alpha[2] = n & 0b11111111;
    
    printf("%c%c%c", alpha[0],alpha[1], alpha[2]);
}

int Base64Decode()
{
    char str[100001];   
    int t, len;
    int conv[255];

    int st = 0;
    for(int i = 'A'; i <= 'Z'; i++)
    {
        conv[i] = st++;
    }

    for(int i = 'a'; i <= 'z'; i++)
    {
        conv[i] = st++;
    }

    for(int i = '0'; i <='9'; i++)
    {
        conv[i] = st++;
    }

    conv['+'] = st++;
    conv['/'] = st++;

    scanf("%d\n", &t);
    for(int tc = 1; tc <= t; tc++)
    {
        scanf("%s", str);
        len = length(str); 

        printf("#%d ", tc);
        for(int i = 0; i < len; i += 4)
        {
            int nums[4] = { conv[str[i]], conv[str[i + 1]] , conv[str[i+2]], conv[str[i+3]]};
            print(nums);
        }
        printf("\n");
    }
    return 0;
}