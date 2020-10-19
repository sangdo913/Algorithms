from collections import deque
from collections import defaultdict

def getlen(res, adj, n, tree):
    Q = deque([tree[0]])
    visit = 1<<tree[0]
    last = 0
    while Q:
        last = Q.popleft()
        for nxt in [nxt for nxt in adj[last] if nxt in tree]:
            if visit & 1<<nxt:
                continue
            visit |= 1<<nxt 
            Q.append(nxt)
    Q.append(last)
    res = 0
    visit = 1<<last 
    while Q:
        cnt = len(Q)
        while cnt:
            now = Q.popleft()
            for nxt in [nxt for nxt in adj[now] if not visit & 1 << nxt and nxt in tree]:
                visit |= 1<<nxt
                Q.append(nxt)
            cnt-=1
        res+=1
    return res -1
    
class Solution:
    def countSubgraphsForEachDiameter(self, n: int, edges):
        adj = defaultdict(list)
        for a,b in edges:
            adj[a-1].append(b-1)
            adj[b-1].append(a-1)
        
        Q = deque([1<<i for i in range(n)])
        visit = set([1<< i for i in range(n)])
        res =[0]*(n-1)
        while Q:
            cnt = len(Q)
            while cnt:
                now = Q.popleft()
                tree = [i for i in range(n) if now & (1 << i)]
                for nxt in sum([adj[i] for i in tree], []):
                    nvisit = now | (1<<nxt)
                    if nvisit not in visit:
                        ret = getlen(res, adj, n, list(set(tree + [nxt])))
                        res[ret-1]+=1
                        visit.add(nvisit)
                        Q.append(nvisit)
                cnt-=1

        return res