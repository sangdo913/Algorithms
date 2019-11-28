#include<string>
#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

#define MAXCNT 1000000

struct NODE{
    string key;
    NODE *pa;
    int freq;
    NODE *next, *prev, *n, *p;
    NODE():freq(0){}
};
NODE exist, dummy;
unordered_map<string, NODE*> um;
vector<NODE> nodes;
int nid = 0;

vector<NODE> nums;
class AllOne {
public:
    /** Initialize your data structure here. */
    AllOne() {
        exist.prev = exist.next = &exist;
        nid = 0;
        nums.resize(MAXCNT);

        um.clear(); 
        nodes.resize(MAXCNT);
        for(int i = 0; i < MAXCNT; ++i) nodes[i].freq = i, nodes[i].p = nodes[i].n = &nodes[i];
        exist.next = exist.prev = &nodes[0];
        nodes[0].prev = nodes[0].next = &exist;
        nodes[0].n = nodes[0].p = &dummy;
        dummy.n = dummy.p = &nodes[0];
        exist.freq = -1;
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        NODE *n;
        if(um.find(key) != um.end()){
            n = um[key];
        }
        else{
            
            n = &nums[nid++];
            um.insert({key, n});
            n->key = key;
            n->pa = &nodes[0];
            n->p = nodes[0].p;
            n->n = &nodes[0];
            nodes[0].p->n = n;
            nodes[0].p = n;
        }
        n->freq++;

        if(n->pa->next->freq != n->freq){
                nodes[n->freq].prev = n->pa;
                nodes[n->freq].next = n->pa->next;

                n->pa->next->prev = &nodes[n->freq];
                n->pa->next = &nodes[n->freq];
        }
        
        n->n->p = n->p;
        n->p->n = n->n;
        if(n->pa->n == n->pa){
            n->pa->prev->next = n->pa->next;
            n->pa->next->prev = n->pa->prev;
        }
        n->n = &nodes[n->freq];
        n->p = nodes[n->freq].p;
        nodes[n->freq].p->n = n;
        nodes[n->freq].p = n;
        n->pa = &nodes[n->freq];
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        NODE * n;
        
        if(um.find(key) != um.end()){
            n = um[key];
        }
        else{
            return;
        }
        if(!n->freq) return;
        n->freq--;

        if(n->pa->prev->freq != n->freq){
                nodes[n->freq].prev = n->pa->prev;
                nodes[n->freq].next = n->pa;

                n->pa->prev->next = &nodes[n->freq];
                n->pa->prev = &nodes[n->freq];
        }
        
        n->n->p = n->p;
        n->p->n = n->n;
        if(n->pa->n == n->pa){
            n->pa->prev->next = n->pa->next;
            n->pa->next->prev = n->pa->prev;
        }
        n->n = &nodes[n->freq];
        n->p = nodes[n->freq].p;
        nodes[n->freq].p->n = n;
        nodes[n->freq].p = n;
        n->pa = &nodes[n->freq];
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        if(exist.prev == &nodes[0]){
            return string();
        }
        return exist.prev->n->key;
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        if(exist.next->next == &exist){
            return string();
        }
        return exist.next->next->n->key;
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */

int main(){
    freopen("0Text.txt", "r", stdin);
    int n;
    int comm;
    int l;
    AllOne allone = AllOne();
    cin >> n;
    string in;

    while(n--){
        cin >> comm;
        switch(comm){
            case 0: 
            cin >> in;
            allone.inc(in);
            break;
            case 1:
            cin >> in;
            allone.dec(in);
            break;
            case 2:
            cout << allone.getMaxKey() << endl;
            break;
            case 3:
            cout << allone.getMinKey() << endl;
            break;
        }
    }
    return 0;
}