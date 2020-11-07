class Solution:
    def maxLengthBetweenEqualCharacters(self, s):
        dic = {c : i for i,c in enumerate(s)}
        res = -1
        for i,c in enumerate(s):
            res = max(res, dic[c] - i-1)
        return res