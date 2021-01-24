from collections import deque
def check_cycle(i, j):
    cnt = 100
    s = i+j
    if s%2 : return False
    while(cnt):
        if i == j: return True
        if i < j: i = i*2; j = s-i
        else: j = j*2; i = s-j
        cnt-=1
    return False

# def detect_inf_loop(a, b):
    # number_sum = a + b
    # if number_sum % 2:
    #     return True
    # number_sum /= 2
    # lower_number = a if a < b else b

    # if not number_sum % lower_number:
    #     number_sum /= lower_number
    #     count = 1
    #     while count < number_sum:
    #         count <<= 1
    #     if count == number_sum:
    #         return False
    # return True

def biparate_matching(chk,sel, adj, con, i):
    if sel[i] == -1: return True
    chk[i] = 1
    b = sel[i]
    while con[b] < len(adj[b]):
        if not chk[adj[b][con[b]]] and biparate_matching(chk, sel, adj, con, adj[b][con[b]]):
            sel[b] = adj[b][con[b]]
            sel[adj[b][con[b]]] = b
            return True
        con[b]+=1
    return False
tc = 0

def lca(par, chk,mat, root, u,v):
    global tc
    tc+=1
    chk[root] = tc
    while root != u:
        chk[u] = tc 
        u = par[mat[u]]
    while chk[v] != tc:
        v = par[mat[v]]

    return v

def blossom(mat, par, grp, vis, p, u, v):
    while p != u:
        nv = mat[u]
        nu = par[nv]
        par[u] = v
        grp[u] = grp[nv] = p
        vis[nv] = 1
        u = nu
        v = nv
        
def flip_pos(col, mat, par,root, u):
    while root != par[u]:
        v = par[u]; w = mat[v] 
        mat[w] = 0
        mat[u],mat[v] = v,u
        u = par[u]
    mat[root] = u
    mat[u] = root

def flip_find(chk, adj,par, col,mat,vis,r):
    Q= deque([r])
    grp = [i for i in range(len(chk))]
    vis[r] = 1
    col[r] = 0
    while Q:
        now = Q.popleft()

        for nxt in adj[now]:
            par[nxt] = now
            if col[nxt] == -1:
                col[nxt] = 1
                if not mat[nxt]:
                    flip_pos(col,mat,par,now,nxt)
                    return 2
                col[mat[nxt]] = 0
                Q.append(mat[nxt])
            elif col[nxt] == 0 and grp[nxt] != grp[now]:
                p = lca(par,chk,mat,r,now, nxt)
                blossom(mat,par,grp, vis,p,now,nxt)
                blossom(mat, par, grp, vis,p,nxt,now)
                for i in range(len(vis)):
                    if vis[i] and col[i]:
                        col[i] = 0
                        Q.append(i)
                        
    return 0
                
def solution(banana_list):
    #Your code here
    adj = [[] for _ in range(len(banana_list)+1)]
    # print(adj)
    for i,j in [(i,j) for i in range(len(banana_list)) for j in range(len(banana_list))]:
        if i == j :continue
        if not check_cycle(banana_list[i], banana_list[j]):
            adj[i+1].append(j+1)
    ret = 0
    mat = [0]*len(adj)
    for i in range(1, len(banana_list)):
        if mat[i]: continue
        chk = [0]*len(adj)
        col = [-1]*len(adj)
        par = [0]*len(adj)
        vis = [0]*len(adj)
        ret += flip_find(chk,adj,par,col,mat,vis,i) 
    # print(adj)
    # print(ret)
    # for r in enumerate(adj):
    #     print(banana_list[r[0]], list(map(lambda x: banana_list[x],r[1])))
    # print()

    # for r in adj:
    #     print(r)
    # print()
    # for i in range(10):
    #     lca(0,0,0,0,0)
    return len(banana_list) - ret 
        

li = [1, 7, 3, 21, 13, 19]
# li = [1,1]
print(solution(li))