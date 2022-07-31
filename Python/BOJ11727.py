n = int(input())

# 1. Top Down
cache = [-1]*(n+1)
def tile(n):
    if cache[n] != -1: return cache[n]
    if n == 0 or n == 1: return 1
    
    cache[n] = tile(n-1) + tile(n-2)*2
    return cache[n]
# 2. Bottom Up
tiles = [0]*(n+1)
tiles[0] = tiles[1] = 1

for i in range(2, n+1):
    tiles[i] = (tiles[i-1] + tiles[i-2]*2)%10007

print(tiles[n])