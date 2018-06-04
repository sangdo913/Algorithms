#include<cstdio>
#include<cstring>

struct ARITHMETICINFO
{
    typedef enum oper {PL = -1, MUL = -2, MI = -3, DIV = -4} oper;
    
    typedef struct NODE
    {
        bool isOP;
        double value;
        char op;

        NODE* left;
        NODE* right;

        NODE()
        {
            left = right = NULL;
        }
        
        double getValue()
        {
            if(!isOP) return value;

            double l = left->getValue();
            double r = right->getValue();
            switch(op)
            {
                case '+':
                return l + r;
                break;

                case '*':
                return l * r;
                break;

                case '/':
                return l / r;
                break;

                case '-':
                return l - r;
                break;
            }
            return -100;
        }

    } NODE;

    NODE nodes[1001];

    bool conv[255];
    int size;

    void initConv()
    {
        memset(conv, false, sizeof(conv));

        conv['+'] = true;
        conv['*'] = true;
        conv['/'] = true;
        conv['-'] = true;
    }

    int getDigit(char num[10])
    {
        int res = 0;

        for(int i = 0 ; num[i] != '\n'; i++)
        {
            res *= 10;
            res += num[i] - '0';
        }

        return res;
    }
    void init()
    {
        scanf("%d\n", &size);

        int node, left, right;
        char value[10];
        int i;
        for(i = 0; i < size; i++)
        {
            scanf("%d ", &node);
            scanf(" %c", &value[0]);

            if(conv[value[0]])
            {
                scanf(" %d %d\n", &left, &right);
                nodes[node].isOP = true;
                nodes[node].left = &nodes[left];
                nodes[node].right = &nodes[right];
                nodes[node].op = value[0];
            }

            else
            {

                scanf("%c", &value[1]);
                for(int j = 1; value[j] != '\n'; j++)
                {
                    scanf("%c", &value[j+1]);
                }
                nodes[node].isOP = false;
                nodes[node].value = getDigit(value);
            }
        }
    }

    int getValue()
    {
        return (int) nodes[1].getValue();
    }

} info;

int arithmeticOperation()
{
    int t = 10;
    info.initConv();

    for(int tc = 1; tc <= 10 ; tc ++)
    {
        info.init();
        printf("#%d %d\n", tc, info.getValue());
    }
    return 0;
}