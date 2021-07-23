import java.util.*
class Solution {
    fun solution(m: IntArray): Int {
        var dp = IntArray(m.size){0x3f3f3f3f}
        var chk = IntArray(m.size){-1}
        var nxt = IntArray(m.size)
        for(i in m.indices){
            var now = i
            var c = i
            while(m[now] != 0 && chk[now] != c){
                chk[now] = c
                now = when{
                    now+m[now] < 0 -> 0
                    m.lastIndex < now+m[now] -> m.lastIndex
                    else -> now+m[now]
                } 
            }
            nxt[i] = if(chk[now] == c) -1 else now
        }
        var Q: Queue<Int> = LinkedList()
        Q.add(0)
        dp[0] = 0
        
        while(Q.isNotEmpty()){
        	var now = Q.poll()    
            for(d in 1 .. 6){
                var next = nxt[when {
                    now + d < 0 -> 0
                    now + d > m.lastIndex -> m.lastIndex
                    else -> now+d
                }]
                if(next == -1) continue
                if(dp[now] +1 < dp[next]){
                    dp[next] = dp[now]+1
                    Q.add(next)
                }
            }
        }
        
        return dp[m.lastIndex]
    }
}