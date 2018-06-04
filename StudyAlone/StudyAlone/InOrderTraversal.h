#include<cstdio>

struct InOrder
{
    char nodes[101];
    int n;

    int getLeft(int index)
    {
        return index << 1;
    }

    int getRight(int index)
    {
        return (index << 1 ) + 1;
    }

    void traversal(int index)
    {
        if(index > n)
        {
            return;
        }

        traversal(getLeft(index));
        printf("%c", nodes[index]);
        traversal(getRight(index));
    }
    void init()
    {
        scanf("%d\n", & n);

        int node, left, right;
        for(int i = 0; i < n; i++)
        {
            scanf("%d ", &node);
            if(getLeft(node) > n)
            {
                scanf("%c", &nodes[node]);
            }
            else if(getRight(node) > n)
            {
                scanf("%c %d", &nodes[node], &left);
            }
            else
            {
                scanf("%c %d %d", &nodes[node], &left, &right);
            }
        }
    }
} info;

int InOrderTraversal()
{
    int t = 10;
    for(int tc = 1; tc <= 10; tc++)
    {
        info.init();
        printf("#%d ", tc);
        info.traversal(1);
        printf("\n");
    }
    return 0;
}