class Solution:
    def findLexSmallestString(self, s, a,b):
        visit = set([s])
        dq = deque()
        dq.append(s)
        while dq:
            now = dq.popleft()
            nxt = now[-b:] + now[:-b]
            if nxt not in visit:
                visit.add(nxt)
                dq.append(nxt)
            nxt = list(now)
            for i in range(1, len(s),2):
                c = now[i]
                nxt[i] = chr((int(c) + a)%10 + ord('0'))
            nxt = ''.join(nxt)
            if nxt not in visit:
                visit.add(nxt)
                dq.append(nxt)

        return min(list(visit))