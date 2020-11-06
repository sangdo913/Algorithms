class FIRE:
    def __init__(self, li):
        self.r = li[0]-1; self.c = li[1]-1; self.m = li[2]
        self.s = li[3]; self.d = li[4]; self.num = 1; self.nd = 0

def mysum(f):
    return f.m

n, m, k = map(int ,input().split())

fire = [[],[]]
dr = (-1,-1,0,1,1,1,0,-1)
dc = (0,1,1,1,0,-1,-1,-1)
turn = 0

fire[0] = [(FIRE(list(map(int, input().split())))) for _ in range(m)]
mymap = [[FIRE([0,0,0,0,0])]*n for _ in range(n)]
chk = [[0]*n for _ in range(n)]

nexts = []
for i in range(k,0,-1):
    nexts = []
    for f in fire[turn]:
        f.r, f.c = (f.r + dr[f.d]*f.s)%n, (f.c+dc[f.d]*f.s)%n
        if chk[f.r][f.c] != i:
            chk[f.r][f.c] = i
            mymap[f.r][f.c] = f
            f.nd = 1<<(f.d%2)
            nexts.append(f)
        else:
            mymap[f.r][f.c].m+= f.m; mymap[f.r][f.c].s += f.s
            mymap[f.r][f.c].nd |= 1<<(f.d%2)
            mymap[f.r][f.c].num += 1
    turn ^= 1
    fire[turn] = []
    for f in nexts:
        fire[turn] += [FIRE([f.r+1, f.c+1, f.m//5, f.s//f.num, d + int(f.nd==3)]) for d in range(0,7,2) if f.m>=5] if f.num > 1 else [f]  
print(sum(map(mysum, fire[turn])))