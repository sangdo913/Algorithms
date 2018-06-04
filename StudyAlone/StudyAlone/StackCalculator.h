#include<iostream>
#include<stack>

using namespace std;

struct CalculatorInfo
{
    typedef enum PRIORITY {braket = 3, MUL = 1, PLUS = 2, braketST = 0} PRIORITY;
    typedef enum TYPE {OP = 0, OPPEREND = 1} TYPE;
    char type[255], priority[255];
    char str[1000];
    int index;

    int cal()
    {
        int res = 0;
        stack<int> operends;
        for(int i = 0; i < index; i++)
        {
            if(type[str[i]] == OPPEREND) operends.push(str[i] - '0');
            else
            {
                int i1 = operends.top(); operends.pop();
                int i2 = operends.top(); operends.pop();
                switch(str[i])
                {
                    case '+':
                    operends.push(i1 + i2);
                    break;

                    case '*':
                    operends.push(i1 * i2);
                    break;
                }
            }
        }
        return operends.top();
    }

    void initType()
    {
        for(char c = '0'; c <= '9'; c++)
        {
            type[c] = OPPEREND;
        }
        type['('] = type [')'] = type['+'] = type['*'] = OP;
        priority[')'] = braket;
        priority['('] = braketST;
        priority['+'] = PLUS;
        priority['*'] = MUL;
    }

    void init()
    {
        int len; char in;
        stack<char> operators;

        int res = 0; index = 0;

        scanf("%d\n", &len);
        while(len--)
        {
            scanf("%c \n", &in);
            if(type[in] == OPPEREND)
            {
                str[index++] = in;
            }
            else
            {
                while(operators.size() && priority[in] >= priority[operators.top()])
                {
                    if(operators.top() == '(') break;
                    str[index++] = operators.top();
                    operators.pop();
                }
                if(in != ')') operators.push(in);
                else
                {
                    operators.pop();
                }
            }
        }
        while(operators.size())
        {
            str[index++] = operators.top();
            operators.pop();
        }
    }
} info;

int StackCalculator()
{
    int t = 10;

    info.initType();

    for(int tc = 1; tc <= 10; tc++)
    {
        info.init();
        printf("#%d %d\n", tc, info.cal());
    }
}