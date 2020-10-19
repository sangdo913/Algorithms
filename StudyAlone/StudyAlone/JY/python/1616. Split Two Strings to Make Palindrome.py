class Solution:
    def checkPalindromeFormation(self, a: str, b: str) -> bool:
        l = len(a)
        s = (a,b)
        
        for s in s:
            le,ri = s[:l//2][::-1], s[l-l//2:]
            size = len(le)
            same = 0
            
            for i in range(l//2):
                if le[i] != ri[i]:
                    break
                else: same+=1
        
            le = (a[:size - same], b[:size-same])
            ri = (b[-1:same-size-1:-1], a[-1:same-size-1:-1])
            
            for le,ri in zip(le,ri):
                if le==ri: return True
        return False