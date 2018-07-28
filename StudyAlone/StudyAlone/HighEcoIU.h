int len(long long from, long long to){
    if((from*3  + 2) == to) return 1;
    if(from*3 + 2 > to) return 0;

    int ret = 0;
    ret += len(from*3, to - 2);
    ret += len(from*3 + 1, to - 1);
    ret += len(from*3 + 2, to);
    if((to-2)%3 == 0) ret += len(from, (to-2)/3);
    return ret;
}



// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n) {
    int answer = 0;
    long long a = n;
    return len(1, a);
}