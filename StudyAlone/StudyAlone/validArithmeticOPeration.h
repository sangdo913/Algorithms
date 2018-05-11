#include<cstdio>

struct validArithmeticOperationInfo
{
    char data[201];
    bool isOP[255];
    int size;
    void initOP()
    {
        for(int i = '0'; i <= '9'; i++)
        {
            isOP[i] = false;
        }

        isOP['+'] = isOP['-'] = isOP['*'] = isOP['/'] = true;
    }

    int getLeft(int index)
    {
        return index << 1;
    }

    int getRight(int index)
    {
        return (index << 1) + 1;
    }

    bool canCalculate()
    {
        scanf("%d\n", &size);
        bool res = size % 2;
        int i, left, right, node;
        char in;
        for(i = 1; i <= size; i++)
        {
            scanf("%d %c ", &node, &in);
            if(getLeft(node) <= size)
            {
                scanf("%d ", &left);
                if(getRight(node) <= size) scanf("%d\n", &right);
            }

            if(i <= (size >> 1)) res &= isOP[in];
            else res &= !isOP[in];
        }

        return res;
    }
} info;

int validArithmeticOPeration()
{
    info.initOP();
    for(int tc = 1; tc <= 10; tc++)
    {
        printf("#%d %d\n", tc, info.canCalculate());
    }
    return 0;
}