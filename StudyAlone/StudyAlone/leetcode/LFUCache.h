#include<iostream>
#include<vector>
#include<queue>
#define KEYMAX 1000001

using namespace std;
struct LIST{
    int value;
    int freq;
    LIST *parent;
    LIST *n, *p;
    LIST *next, *prev;
};

vector<LIST> nodes;
vector<int> check;
vector<LIST> pool;
LIST li;
int id = 0;
int c;
int cnum;

class LFUCache {
public:
    LFUCache(int capacity) {
        check.clear();
        check.resize(KEYMAX, 0);
        pool.clear();
        pool.resize(0);
        li.next = li.prev = &li;
        nodes.resize(KEYMAX);
        
        for(int i = 0; i < KEYMAX; ++i) nodes[i].freq = 0;
        pool.resize(KEYMAX);
        for(int i = 0; i < pool.size(); ++i) pool[i].freq = i;
        c = capacity;
        cnum = 0;
    }
    
    int get(int key) {
        if(c == 0) return -1;
        int ret;
        if(check.size() <= key){
            while(check.size() != key+1) {
                check.push_back(0);
                nodes.push_back(LIST());
                nodes.back().p = &nodes.back();
                nodes.back().n = &nodes.back();
            }
        }

        if(check[key]){
            ret = nodes[key].value;
            nodes[key].freq++;
            change_freq(key);
        }
        else{
            return -1;
        }
        return ret;
    }
    
    void put(int key, int value) {
        if(c == 0) return;
        if(check[key]){
            nodes[key].value = value;
            nodes[key].freq++;
            change_freq(key);
        }
        else{
            check[key] = 1;
            nodes[key].value = value;
            nodes[key].freq = 1;

            if(cnum == c){
                LIST *del = li.next->n;
                del->p->n = del->n;
                del->n->p = del->p;
                check[del-&nodes[0]] = 0;

                if(del->parent->n == del->parent){
                    del->parent->next->prev= del->parent->prev;
                    del->parent->prev->next = del->parent->next;
                }
            }
            else cnum++;

            if(li.next->freq != 1){
                pool[1].next = li.next;
                pool[1].prev = &li;
                pool[1].p = pool[1].n = &pool[1];
                li.next->prev = &pool[1];
                li.next = &pool[1];
            }

            nodes[key].p = pool[1].p;
            nodes[key].n = &pool[1];
            pool[1].p = pool[1].p->n = &nodes[key];
            nodes[key].parent = &pool[1];
        }
    }

    void change_freq(int key){
            nodes[key].p->n = nodes[key].n;
            nodes[key].n->p = nodes[key].p;

            if(nodes[key].parent->n == nodes[key].parent){
                nodes[key].parent->prev->next = nodes[key].parent->next;
                nodes[key].parent->next->prev = nodes[key].parent->prev;
            }

            if (nodes[key].parent->next == &li || nodes[key].parent->next->freq != nodes[key].freq) {
                LIST* nl = &pool[nodes[key].freq];
                nl->prev = nodes[key].parent->next->prev;
                nl->next = nodes[key].parent->next;
                nl->prev->next = nl->next->prev = nl;
                nl->p = nl->n = &nodes[key];
                nodes[key].p = nodes[key].n = nl;
                nodes[key].parent = nl;
            }
            else {
                LIST* p = nodes[key].parent->next;
                nodes[key].p = p->p;
                nodes[key].n = p;
                p->p->n = &nodes[key];
                p->p = &nodes[key];
                nodes[key].parent = p;
            }
        }
};

int main(){
    freopen("0Text.txt", "r", stdin);
    int n, comm, k,v;
    int capacity;
    cin >> capacity;
    cin >> n;
    LFUCache lfu(capacity);
    while(n--){
        cin >> comm;
        if(comm == 0){
            cin >> k;
            cout << lfu.get(k);
            cout << endl;
        }
        else{
            cin >> k >> v;
            lfu.put(k,v);
        }
    }
    
    return 0;
}