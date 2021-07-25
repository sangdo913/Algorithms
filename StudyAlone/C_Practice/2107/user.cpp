#include<iostream>

using namespace std;
void code(char func[10000]){
    char* f = (char*)"int func(int num){int r=0;int i=1;int t=0;while (true) {A:t=n%i;if (t!=0)goto C;r=r+2;C:t=i*i;if (t>=n)goto D;i=i+1;goto A;}D:t=i*i;t=t-n;if (t!=0)goto E;r=r+1;E:return r;}";
    while(*f){
        *func++ = *f++;
    }
}

/*C코드
int func(int num) {
    int r=0;
    int i=1;
    int t=0;
    while (true) {
        A:
        t=n%i;
        if (t!=0) goto C;
            r=r+2;
        C:
        t=i*i;
        if (t>=n) goto D;
            i=i+1;
        goto A;
    }
    D:
    t=i*i;
    t=t-n;
    if (t!=0) goto E;
        r=r+1;
    E:
    return r;
}
*/
int type_buffer[20];
int buffer_len = 0;
int funcNameBuffer[20];
int nameBuffer[20];
int nameLen;
int funcNameLen;
char buffer[20];
int blen;

int func_passing(char *code) {
    int len = 0;
    buffer_len = 0;
    funcNameLen = 0;
    char*f = (char*)"int func(int ";
    while(*f && code[len] == *f) {
        len++, f++;
    }
    while(code[len] != ' ' && code[len] != ')') len++;
    if(code[len] != ')') return -1;
    return len;
}
int reg[256];
int commandLine[10000];
int commandLen;
bool mystrcmp(const char*a, const char*b){
    while(*a && *b && *a == *b) ++a, ++b;
    return *a == *b;
}

int run(int n, char *code){
    /*
    1. 모든 변수는int이다. (타입 검사 필요 X)
    ===============================================
    2. 대문자는 LABEL이다. 소문자는 변수이다.
    3. 모든 변수는 한글자이다.(라벨, 상수값 포함) (레지스터를 reg[256]을 통해 관리 가능)
    ===============================================
    4. 띄어쓰기, 탭, 엔터는 최소화한다.(파싱 복잡) 
    5. while은 무조건 true 이다. 또한 중괄호를 무조건 써야한다. (while 분기 조건 작성 필요 X)
    6. if는 뒤에 goto만을 가진다.+ 중괄호를 지원하지 않는다. + if문 안의 조건은 딱 하나의 연산까지만 지원한다. (분기 조건 작성 필요 X)
    7. 변수 선언시에는 반드시 초기화를 해야한다.(변수 선언 분기 제거)
    8. 대입 연산자 뒤에는 딱 하나의 연산만 할 수 있다. (연산을 3글자로 고정)
    9. int, while, if문 등 뒤에는 띄어쓰기가 1개만 있어야한다.
    */
    reg['n'] = n;
    reg['0'] = 0;
    reg['1'] = 1;
    reg['2'] = 2;
    commandLen = 0;

    int cur = func_passing(code);
    if (cur == -1) return -1;
    cur+=2;
    int returnReg=-1;
    
    //코드의 명령어들을 분석한다.
    while(code[cur]) {
        int now = cur;
        blen = 0; 
        while(code[cur] != 0 && code[cur] != ';' && code[cur] != ' ' && code[cur] !=':' && code[cur] != '}' && code[cur] != '{') {
            buffer[blen++] = code[cur++];
        }
        if(code[cur] == ' '){
            commandLine[commandLen++] = now;
            if(code[now] != 'w'){
                //while은 무조건 트루
                while(code[cur] != ';') cur++;
            }
            else{
                while(code[cur] != '{') cur++;
            }
        }
        else if(code[cur] == ':'){
            //라벨의 점프하는 위치를 레지스터에 저장(대문자)
            reg[code[cur-1]] = commandLen-1;
        }
        else if(code[cur] == ';'){
            commandLine[commandLen++] = now;
        }

        if(code[cur] == 0) break;
        cur++;
    }
    int line= 0;
    //명령어의 마지막에 도달할때까지 루프
    while(line != commandLen){
        cur = commandLine[line];
        int ed = cur;
        blen = 0;
        while(code[ed] != ' ' && code[ed] != ';') buffer[blen++] = code[ed++];
        buffer[blen] = 0;
        if(mystrcmp(buffer, "int")){
            reg[code[cur+4]] = reg[code[cur+6]];
        }
        //while은 무조건 true
        else if(mystrcmp(buffer, "while")){ }
        else if(mystrcmp(buffer, "if")){
            int go = ed+1;
            while(code[go] != ' ') go++; 
            int label = reg[code[go+1]];
            if(code[ed + 3] == '!' && code[ed + 4] == '='){
                if(reg[code[ed+2]] != reg[code[ed+5]]) line = label;
            }
            else if(code[ed + 3] == '>' && code[ed+4] == '='){
                if(reg[code[ed+2]] >= reg[code[ed+5]]) line = label;
            }
        }
        else if(mystrcmp(buffer, "return")) {
            returnReg = reg[code[ed+1]];
            line = commandLen-1;
        }
        else if(mystrcmp(buffer, "goto")){
            line = reg[code[ed+1]];
        }
        else{
            //대입 연산자
            switch(code[cur+3]){
                case '*':
                    reg[code[cur]] = reg[code[cur+2]]*reg[code[cur+4]];
                break;
                case '-':
                    reg[code[cur]] = reg[code[cur+2]]-reg[code[cur+4]];
                break;
                case '+':
                    reg[code[cur]] = reg[code[cur+2]]+reg[code[cur+4]];
                break;
                case '%':
                    reg[code[cur]] = reg[code[cur+2]]%reg[code[cur+4]];
                break;
            }
        }
        line++;
    }
    return returnReg;
}