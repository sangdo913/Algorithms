#include<iostream>

using namespace std;

typedef int BLOCK[4][4];
typedef BLOCK DATA;

int heights[60000];

inline void cpy(BLOCK dst, BLOCK in)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            dst[i][j] = in[i][j];
        }
    }
}

inline int maxBLOCK(BLOCK &b)
{
    int max = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0;  j < 4; j++)
        {
            max = b[i][j] > max ? b[i][j] : max;
        }
    }
    return max;
}

inline void maxADJ(BLOCK &b, int max)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            b[i][j] = max - b[i][j];
        }
    }
}
struct Heap
{
    typedef int DATA;

    DATA *arr;
    int maxSize, size;
    Heap()
    {
        maxSize = 100;
        arr = new DATA[maxSize];
        size = 0;
    }
    ~Heap()
    {
        delete[] (arr);
    }
    void clear()
    {
        maxSize = 100;
        size = 0;
        delete[] arr;

        arr = new DATA[maxSize];
    }

    int parent(int node)
    {
        return node >> 1;
    }
    int left(int node)
    {
        return (node << 1);
    }

    int right(int node)
    {
        return (node << 1) + 1;
    }

    int getChild(int node)
    {
        int l = left(node), r = right(node);
        if(l > size)
        {
            return 0;
        }
        else if(r > size)
        {
            return l;
        }
        else
        {
            if(arr[l] < arr[r]) return r;
            else return l;
        }
    }

    void push(DATA data)
    {
        size++;
        if(size == maxSize)
        {
            maxSize <<= 1;
            DATA* newARR = new DATA[maxSize];
            for(int i = 0; i < size; i++)
            {
                newARR[i] = arr[i];
            }
            delete[] arr;
            arr = newARR;
        }

        int index = size, p = parent(index);
        while(p != 0 && arr[p] < data)
        {
            arr[index] = arr[p];
            index = p;
            p = parent(index);
        }
        arr[index] = data;
    }

    DATA pop()
    {
        DATA ret = arr[1];

        int index = 1, c = getChild(index);
        size--;

        while(c && arr[size + 1] < arr[c])
        {
            arr[index] = arr[c];
            index = c;
            c = getChild(index);
        }

        arr[index] = arr[size + 1];
        return ret;
    }
} heap[60000];

int firstIndex;

struct List
{
    typedef struct NODE
    {
        DATA value;
        int index;
        NODE* next;
        NODE* prev;

        NODE()
        {
            prev = next = 0;
        }
    } Node;

    Node* head;
    Node* tail;
    Node* cursor;
    int size;

    void clear()
    {
        cursor = head->next;
        Node* del;
        while(cursor != tail)
        {
            del = cursor;
            cursor = cursor->next;
            delete(del);
        }
        head->next = tail;
        tail->prev = head;
    }

    List()
    {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    ~List()
    {
        cursor = head;
        NODE* del;
        while(cursor)
        {
            del = cursor;
            cursor = cursor->next;
            delete(del);
        }
    }

    void insert(DATA data)
    {
        Node* newNode = new Node();

        cpy(newNode->value, data);
        newNode->prev = tail->prev;
        newNode->next = tail;
        tail->prev->next = newNode;
        tail->prev  = newNode;
        newNode->index = firstIndex++;
    }

    void first()
    {
        cursor = head->next;
    }
    
    bool next(BLOCK& d, int& index)
    {
        if(cursor == tail) return false;
        
        cpy(d, cursor->value);
        index = cursor->index;
        cursor = cursor->next;
        return true;
    }
};

inline void reverse(BLOCK bl)
{
    for(int i = 0; i < 4; i++)
    {
        int temp;
        temp = bl[i][0];
        bl[i][0] = bl[i][3];
        bl[i][3] = temp;

        temp = bl[i][2];
        bl[i][2] = bl[i][1];
        bl[i][1] = temp;
    }
}
inline void rotate(BLOCK dst)
{
    BLOCK temp;

    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            temp[i][j] = dst[3 - j][i];
        }
    }
    cpy(dst, temp);    
}

bool isSame(BLOCK a, BLOCK b)
{
    for(int i = 0 ; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if(a[i][j] != b[i][j]) return false;
        }
    }

    return true;
}

struct Hash{
    List list[29999];
    int pair[60000];

    int k;
    int check(BLOCK& in)
    {
        int min = in[0][0];
        bool isOkay = true;
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                isOkay &= min == in[i][j];
                min = min > in[i][j] ? in[i][j] : min;
            }
        }

        return isOkay ? -1 : min;
    }

    int adjust(BLOCK& in, int min)
    {
        for(int i = 0 ; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                in[i][j] -= min;
            }
        }
    }

    int hash(const BLOCK& in)
    {
        int key = 0;
        int cnt = 1;
        for(int i = 0 ; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                key += in[i][j];
                key *= 1254;
                key %= k;
            }
        }

        return key % k ;
    }

    int find(BLOCK& in)
    {
        int key = hash(in);
        BLOCK find[4], check;
        cpy(find[0], in);

        for(int i = 1; i < 4; i++)
        {
            cpy(find[i], find[i-1]);
            rotate(find[i]);
        }

        int index = -1;

        for(int i = 0 ; i < 4; i++)
        {
            key = hash(find[i]);
            list[key].first();
            
            while(list[key].next(check, index))
            {
                if(isSame(find[i], check))
                {
                    return index;
                }
            }
        }

        return -1;
    }

    void insert(BLOCK& in)
    {
        int minHeight = check(in);
        if(minHeight == -1) return;
        
        adjust(in, minHeight);

        int index = find(in);
        if(index != -1)
        {
            heap[index].push(minHeight);
        }

        else
        {
            int key = hash(in);
            heap[firstIndex].push(minHeight);            
            heights[firstIndex] = in[0][0];
            pair[firstIndex] = firstIndex + 1;
            list[key].insert(in);

            reverse(in);
            int max = maxBLOCK(in);
            maxADJ(in, max);

            key = hash(in);
            pair[firstIndex] = firstIndex - 1;
            heights[firstIndex] = in[0][3];
            list[key].insert(in);
        }
    }

    int findMax()
    {
        BLOCK key;
        int index;
        int res = 0;

        for(int i = 0; i < firstIndex; i += 2)
        {
            while(heap[i].size && heap[i+1].size)
            {
                res += heap[i].pop() + heap[i+1].pop() + heights[i] + heights[i + 1];
            }
        }
        return res;
    }
    Hash()
    {
        k = 29999;
    }
    void clear()
    {
        for(int i = 0 ; i < 29999; i++)
        {
            list[i].clear();
        }
    }
};

Hash h;

void init()
{
    h.clear();

    for(int i = 0; i < firstIndex; i++)
    {
        heap[i].clear();
    }
    firstIndex = 0;
}

int makeBlock(int module[][4][4])
{
    init();

    for(int i = 0; i < 30000; i++)
    {
       h.insert(module[i]);
    }

    int res = h.findMax();
    return res;
}