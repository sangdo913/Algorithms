from fractions import Fraction
from collections import defaultdict

def getdet(m):
    if(len(m) == 2): return m[0][0]* m[1][1] - m[0][1]*m[1][0]
    res = 0
    mi = 1
    mm = m[1:]
    for j in range(len(m)):
        sij = [row[:j] + row[j+1:] for row in mm]
        res += mi * m[0][j]* getdet(sij)
        mi = -mi
    return res

def getdet_ij(m,i,j):
    sij = m[:i]+m[i+1:]
    for row in range(len(sij)):
        sij[row] = sij[row][:j] + sij[row][j+1:]
    return getdet(sij)

def getinv(m):
    det = Fraction(getdet(m),1)
    if(len(m) == 2) :
        m[0][0],m[1][1] = m[1][1]/det, m[0][0]/det
        m[0][1],m[1][0] = -m[0][1]/det, -m[1][0]/det
        return m
        
    mm = [[0]*len(m) for _ in range(len(m))]

    for i,j in [(i,j) for i in range(len(m)) for j in range(len(m))]:
        mm[i][j] = (-1 if (i+j)%2 else 1) *getdet_ij(m,i,j)

    for i,j in [(i,j) for i in range(len(m)) for j in range(i+1,len(m))]:
        mm[i][j],mm[j][i] = mm[j][i], mm[i][j]

    for i in range(len(mm)):
       mm[i] = list(map(lambda x : x/det, mm[i])) 
    return mm

def multimatrix(a,b):
    ret = [[0]*len(b[0]) for _ in range(len(a))]
    for i,j in [(i,j) for i in range(len(a)) for j in range(len(b[0]))]:
        for k in range(len(a[i])):
            ret[i][j] += a[i][k] * b[k][j]

    return ret

def gcd(a,b):
    if a < b: b,a = a,b
    r = a%b
    while r: a,b,r = b,r, b%r
    return b

def solution(m):
    n = len(m)
    if n == 1:
        return [1,1]
    nt, t = [],[]

    for i in range(len(m)):
        total = sum(m[i])
        if total:
            m[i] = list(map(lambda x: x/Fraction(total,1),m[i]))
            nt.append(i)
        else:
            m[i][i] = 1
            t.append(i)

    li = t + nt
    dic = defaultdict(int)
    for i, v in enumerate(li):
        dic[v] = i

    P = []
    # print(dic)
    for row in t:
        P.append(m[row])
    for row in nt:
        P.append(m[row])
    for r in range(len(P)):
        li = [0]*len(P)
        for i in range(len(P)):
            li[dic[i]] = P[r][i]
        P[r] = li

    I = [[1 if j == i else 0 for j in  range(len(nt))] for i in range(len(nt))]
    Q = [[0]* len(nt) for _ in range(len(nt))]
    for i in range( len(nt)):
        for j in range(len(nt)):
            Q[i][j] = P[len(t) + i][len(t) + j]

    I_Q = []
    for i in range(len(I)):
        I_Q.append( [I[i][j] - Q[i][j] for j in range(len(I))])

    temp = []
    for r in I_Q:
        li = []
        for c in r:
            li.append(c)
        temp.append(li)

    inv_I_Q = getinv(I_Q)
    
    R = []
    for i in range(len(nt)):
        li = []
        for j in range(len(t)):
            li.append(P[len(t) + i][j])
        R.append(li)

    # print('RR')
    # for r in R:
    #     # print(r)
    # print('FF')
    # for r in inv_I_Q:
    #     print(r)
    # print(len(inv_I_Q), len(inv_I_Q[0]))
    rq = multimatrix(inv_I_Q, R)
    li = rq[dic[0]-len(t)]

    lcm = 1
    for i in li: 
        g = gcd(lcm, i.denominator)
        lcm = lcm*i.denominator//g
    res = []
    for i in li:
        res.append(i.numerator*lcm//i.denominator)
    res.append(lcm)
    return res
            
    # li =[[1,2,3],[0,1,4],[5,6,0]]
    # li2 =[[1,2,3],[0,1,4],[5,6,0]]
    # print(nt,t)
    # for i in li:
    #     print(i)
    # print('mul')

    # print(li)

    # for r in li:
    #     print(r)

    # inv = getinv(li)
    # print('inv')
    # for r in inv:
    #     print(r)

    # print()
    # print('li * inv')
    # m = multimatrix(li2,inv)
    # for r in m:
    #     print(r)

print(solution([[0, 1, 0, 0, 0, 1], [4, 0, 0, 3, 2, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0], [0, 0, 0, 0, 0, 0]]))
    