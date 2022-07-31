fibonacci = [-1]*100
fibonacci[0] = 0
fibonacci[1] = 1

for i in range(2,10):
    fibonacci[i] = fibonacci[i-1] + fibonacci[i-2]

print(fibonacci)