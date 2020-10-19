class Solution:
    def maximalNetworkRank(self, n, roads):
        dic = {i:[] for i in range(n)}
        se = set(map(tuple, roads))
        for a,b in roads:
            dic[a].append(b)
            dic[b].append(a)
        return max([len(dic[i]) + len(dic[j]) - int((i,j) in se or (j,i) in se) for i in range(n) for j in range(i+1,n)])