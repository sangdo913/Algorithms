#include<stdio.h>

struct NODE{
    int v, i, lid;
    int priority;
    int size;
    NODE *l, *r;
}nodes[500000];
int nid;

NODE root;

struct NODEPAIR{
    NODE* left, *right;
};

NODEPAIR split(NODE* root, NODE* key){
    NODEPAIR res;
    if(!root){
        return {0,0};
    }

    if (root->v < key->v) {
        res = split(root->r, key);
        root->r = res.left;
        return {root, res.right};
    }
    else{
        res = split(root->l, key);
        root->l = res.right;
        return {res.left, root};
    }
}

void insert(NODE* root, NODE* key){
    NODE* p = 0;
    NODE* n = root;
    NODEPAIR res;
    while(n && n->priority > key->priority){
        p = n;
        if(n->v < key->v){ n = n->r; }
        else{ n = n->l;}
    }
    res = split(n,key);
    key->l = res.left;
    key->r = res.right;

    if(p->v > key->v){p->l = key; }
    else{ p->r = key;}
}

NODE* merge(NODE* left, NODE* right){
    if(!right && !left) return 0;
    if(!left) return right;
    if(!right) return left;
    NODE* res;
    if(left->priority < right->priority){
        res = right;;
        res->l= merge(left, res->l);
    }
    else{
        res = left;
        res->r = merge(res->r, right);
    }
    return res;
}

void del(NODE* root, int key){
    NODE* p = 0;
    NODE* n = root;
    while(n&&n->v != key){
        p = n;
        if(key < n->v)  n = n->l;
        else n = n->r; 
    }
    if(n) {
        n = merge(n->l, n->r);
        if(p->v > key) p->l = n;
        else p->r = n;
    }
}

NODE* find(NODE* root, int key){
    while(root && root->v != key){
        if(root->v == key) return root;
        if(root->v < key) root = root->r;
        else root = root->l;
    }
    return root;
}

struct LNODE{
    int num;
    LNODE *prev, *next;
}lnode[500000];
int lidx;
int K,N;

#define RAND(x) ((((long long)(x)* 214013LL + 3251011LL)&0xfffffff))
LNODE head;

int ain(){
    scanf("%d %d", &K, &N);
    char in[9];
    int sid;
    head.next = head.prev = &head;
    int rand = 13246;
    root.v = root.priority = 0x3f3f3f3f;
    N= 10; 

    int cnt = 0;
    while(N--){
        scanf("%s", in);
        rand = RAND(rand);
        if(rand %7){
            for(int i = 0; i < 8; ++i){
                    rand = RAND(rand);
                    in[i] = rand % 10 + '0';
            }
            
            sid = 0;
            for(int i = 0; i < 8; ++i){
                sid = sid* 10 + in[i]-'0';
            }
        }
        else {
            printf("same ");
            rand = RAND(rand);
            sid = lnode[rand%lidx].num;
        }
        printf("%d: %d\n", cnt++, sid);
        NODE* res = find(&root, sid);
        if(!res){
            LNODE &ln = lnode[lidx];
            ln.prev = head.prev;
            ln.next = &head;
            ln.num = sid;

            head.prev->next = &ln;
            head.prev = &ln;

            NODE &nn = nodes[nid];
            nn.i = nid++;
            nn.lid = lidx++;
            rand = RAND(rand);
            nn.priority = rand;
            nn.v = sid;
            insert(&root, &nn);
        }
        else{
            int lid = res->lid;

            lnode[lid].prev->next = lnode[lid].next;
            lnode[lid].next->prev = lnode[lid].prev;
            lnode[lid].prev = head.prev;
            lnode[lid].next = &head;

            head.prev->next = lnode +lid;
            head.prev = lnode + lid;
        }
    }

    LNODE* cursor = head.next; 

    char out[9] = {};

    //K=10000;
     cnt = 0;
     //printf("\n");
    while(K--&& cursor != &head){
        int v = cursor->num;

        for(int i = 7; i >=0; --i ){
            out[i] =  v%10 + '0';
            v/=10;
        }
       printf("%s\n", out);
        cursor= cursor->next;
    }

    del(&root, 61670181);
    int x =1;
    return 0;
}