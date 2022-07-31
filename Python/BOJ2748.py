# 1. DFS방식 - 시간 초과
def fibonacci(n):
    if n == 0: return 0
    elif n == 1: return 1
    return fibonacci(n-1) + fibonacci(n-2)

# 2. 메모이제이션
cache = [-1]*91

def fibonacci_memoization(n):
    if cache[n] != -1: return cache[n]
    if n == 0: return 0
    if n == 1: return 1
    cache[n] = fibonacci_memoization(n-1) + fibonacci_memoization(n-2)
    return cache[n] 

print(fibonacci_memoization(int(input())))
