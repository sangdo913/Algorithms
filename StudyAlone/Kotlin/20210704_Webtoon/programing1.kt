class Solution {
    fun solution(sizes: Array<IntArray>): Int {
        var answer: Int = 0
        var row = 0
        var col = 0
        for((a, b) in sizes){
            var a = a
            var b = b
            if(a > b) {
                var t = a
                a = b
                b = t
            }
            row = Math.max(row, a)
            col = Math.max(col,b)
        }
        
        return row*col
    }
}