class Solution:
    def maxDepth(self, s):
        conv = {'(':1, ')':-1}
        res = 0
        mmax = 0
        for c in s:
            if c == '(' or c ==')':
                res += conv[c]
                mmax = max(mmax, res)
        return mmax