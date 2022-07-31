n, m = map(int, input().split())

def combination(data, res, index):
    # base case: 
    # 1. m개의 데이터 선택
    # 2. index가 마지막에 도달
    if len(res) == m:
        for i in res:
            print(i, end=' ')
        print()
        return
    if index == len(data):
        return
    
    # general case
    # 1. index번 데이터 선택
    res.append(data[index])
    combination(data, res, index + 1)
    res.pop()

    # 2. index번 데이터 선택하지 않음
    combination(data, res, index + 1 )
        
data = [i+1 for i in range(n)]
combination(data, [], 0)