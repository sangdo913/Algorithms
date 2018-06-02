#include<cstdio>
struct Node
{
    int data;
    Node* next;
    Node* prev;

    Node()
    {
        next = prev = 0;
        data = 0;    
    } 
} _NODES[100000];

struct MyMalloc
{
    int index;

    int init()
    {
        index = 0;
    }

    Node* myMal()
    {
        return &_NODES[index++];
    }
}MyMalloc;

struct List
{
    Node* head;
    Node* cursor;
    Node* tail;
    Node dumm[2];

    List()
    {
        head = &dumm[0];
        tail = &dumm[1];

        head->next = tail;
        tail->prev = head;

        cursor = tail;
    }
    void set()
    {
        cursor = head;
    }
    bool next(int &i)
    {
        if(cursor->next == tail)
        {
            return false;
        }

        cursor = cursor->next;
        i = cursor->data;
        return  true;
    }
    void init()
    {
        cursor = head->next;

        head->next = tail;
        tail->prev = head;
    }
    void insert(int d)
    {
        Node* newNode = MyMalloc.myMal();
        newNode->data = d;
        newNode->prev = tail->prev;
        newNode->next = tail;

        tail->prev = newNode;
        newNode->prev->next = newNode;
    }

    void del()
    {
        cursor->prev-> next = cursor->next;
        cursor->next->prev = cursor->prev;
        cursor = cursor->prev;
    }
};

struct Hash
{
    List li[29999];

    int hash(int key)
    {
        return key % 29999;
    }

    Node* find(int i)
    {
        int idx = hash(i);

        li[idx].set();
        int data;
        while(li[idx].next(data))
        {
               if(data == i) return li[idx].cursor; 
        }

        return 0;
    }

    void insert(int i)
    {
        Node* n;
        if(find(i))
        {
           return; 
        }

        int idx = hash(i);
        li[idx].insert(i);
    }

    void init()
    {
        for(int i = 0; i < 29999; i++)
        {
            li[i].init();
        }
    }

    void del(int i)
    {
        if(find(i))
        {
            int idx = hash(i);
            li[idx].del();   
        }
    }
} hash;

void print(bool b)
{
    if(b) printf("TRUE\n");
    else printf("FALSE\n");
}
int main()
{
    for(int i = 0; i < 10; i++)
    {
        MyMalloc.init();
        hash.init();

        hash.insert(2);
        bool res = hash.find(2);

        print(res);
        print(hash.find(3));
        hash.insert(3);
        print(hash.find(3));
        hash.insert(1);
        hash.insert(1);
        hash.insert(1);
        print(hash.find(1));

        hash.insert(0);
        print(hash.find(0));
        hash.insert(29999);
        print(hash.find(29999));

        hash.del(0);
        print(hash.find(0));
        print(hash.find(29999));
        printf("\n"); 
    }
    return 0;
} 