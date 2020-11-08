green = [[0]*4 for _ in range(6)]
blue = [[0]*4 for _ in range(6)]

def down(arr, r):
    for i in range(r,0, -1):
        arr[i][:] = arr[i-1][:]
    arr[0][:] = [0]*4

chkp = ([(0,0)],[(0,0),(0,1)], [(0,0),(1,0)])
convt = (0, 2,1)

def findr(arr, bj, bt):
    chk = chkp[bt]
    bi = 0

    while bi !=6:
        invalid = False
        for r,c in ((bi + ni,bj + nj) for (ni, nj) in chk):                
            if r == 6 or arr[r][c]: invalid = True; break
        if invalid: break
        bi+=1
    bi-=1
    for r,c in ((bi + ni, bj + nj) for (ni,nj) in chk):
        arr[r][c] = 1

def checkscore(arr):
    ret = 0
    for i,l in enumerate(arr[::-1]):
        while sum(l) == 4:
            ret+=1
            down(arr,5-i)
    return ret

def remove(arr):
    for _ in range(sum(int(any(l)) for l in arr[0:2])):
        down(arr,5)

n = int(input())
query = [tuple(map(int,input().split())) for _ in range(n)]

score = 0
for b, x, y in query:
    b-=1
    findr(green, y, b)
    score += checkscore(green)
    remove(green)

    findr(blue, 3-x - int(convt[b] == 1), convt[b])
    score += checkscore(blue)
    remove(blue)

print(score)
print(sum(sum(green,[])) + sum(sum(blue,[])))