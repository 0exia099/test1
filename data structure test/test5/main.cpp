#pragma warning(disable: 4778)//printf("%");하면 나오는 경고(c4778:printf:서식문자열 '%'이(가) 종결도지 않았습니다.)를 없애기위함
#pragma warning(disable: 26812)//enum대신 enum class를 사용하라는 경고를 없애기위함
#pragma warning(disable: 6385)//92줄에서 c6385경고가 뜨는것을 없애기위함

//@file : main.cpp
/*infix형태의 수식을 입력받아 expr에 저장하고
postfix로 변경하여 new_expr에 저장한 후
postfix를 계산하여 답을 출력하는 코드
postfix로 변경할 때와 postfix를 계산할때의
과정(token, stack, top, output)을 출력한다.
또한 ^(power연산자), !(not연산자)도 동작하며
여러자리의 숫자와 음수도 인식한다. 여러자리 숫자와 음수는 '(',')'를 사용하여 구분한다.
수식을 입력할때 생긴 공백문자는 없는것으로 처리한다.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef enum {//(주의)아무 오류가 없는데 한번씩 다른 부분 수정 중에 typedef에 ';'가 필요하다고 오류가 발생할 때가 있음. 기다리면 없어짐
    lparen, rparen, plus, minus, times, divide, mod, power, not_, eos, operand
} precedence;

//연산자 우선순위
//           (  )  +  -  *  /  %  ^  ! eos 순서
int isp[] = { 0,19,12,12,13,13,13,18,15,0 };//스택에 저장된 연산자의 우선순위
int icp[] = { 20,19,12,12,13,13,13,18,15,0 };//입력 연산자의 우선순위

void postfix(char* expr, char* new_expr);//iffix를 postfix로 바꾸는 함수

precedence postfixStack[MAX_SIZE];//infix를 postfix로 바꾸는데 연산자가 들어갈 스택
int postfixTop = -1;//postfixStack의 top
void postfixPush(precedence token);//postfixStack의 push
precedence postfixPop();//postfixStack의 pop

char precedenceToChar(precedence token);//precedence형의 token을 char형으로 바꾸는 함수
void prtPrecedence(precedence token);//precedence형의 token을 출력하는 함수
void prtPostfixStack();//postfixStack을 출력하는 함수
void prtPostfix(char* new_expr, int n);//현재의 postfix배열을 출력하는 함수

int eval(char* new_expr);//postfix를 계산하는 함수

int evalStack[MAX_SIZE];//postfix계산을 위한 숫자가 들어갈 스택
int evalTop = -1;//evalStack의 top
void push(int num);//evalStack의 push
int pop();//evalStack의 pop
void prtEvalStack(int* n);//evalStack을 출력하고 해당 자릿수의 갯수를 n배열에 저장하는 함수

void return_token(char* new_expr, char* symbol, int* count);//빈칸이 있기 전까지 count를 되돌리는 함수
precedence get_token(char* new_expr, char* symbol, int* count);//수식 문자열에서 다음 문자가 무엇인지 반환하는 함수

int main() {
    char expr[MAX_SIZE];//infix식 저장하는 배열
    char new_expr[MAX_SIZE];//postfix식 저장하는 배열

    //infix입력받음
    printf("infix 수식 : ");
    gets_s(expr);

    postfix(expr, new_expr);//infix->postfix로
    printf("eval() 결과 : %d\n", eval(new_expr));//postfix계산

    //실행파일(exe)실행시 바로 종료되므로 일시정지추가 
    system("pause");
    return 0;
}

void postfix(char* expr, char* new_expr) {
    char symbol;
    precedence token;
    int count = 0;//expr배열의 몇번째인지 나타내는 변수
    int n = 0;//new_expr배열의 몇번째인지 나타내는 변수
    int negative = 0;//token이 ')'가 아닌 연산자면 1이 되고 negative가 1일때 다음 token이 -면 음수  
    postfixTop = -1;

    printf("Token\tStack\t\t\tTop\tOutput\n");

    postfixPush(eos);//스택에 eos저장
	for (token = get_token(expr, &symbol, &count); token != eos; token = get_token(expr, &symbol, &count)) {//expr이 빌때까지 token에 expr의 값 저장

        if (token == operand) {//숫자라면

            negative = 0;//피연산자 이므로 negative = 0

            if ((token = get_token(expr, &symbol, &count)) == operand) {//다음 토큰도 숫자라면 여러자리 숫자

                new_expr[n++] = '(';//여러자리 숫자를 사용하면 숫자 구분이 안됨으로 여러자리 숫자는 '(',')'으로 구분

                return_token(expr, &symbol, &count);//여러자리숫자의 처음 숫자부분으로 count변경

                for (token = get_token(expr, &symbol, &count); token != eos && token == operand; token = get_token(expr, &symbol, &count)) {
                    //다음 토큰이 숫자가 아닐때까지 반복하여 여러자리 숫자 인식
                    new_expr[n++] = symbol;//new_expr에 저장
                    printf("%c", symbol);//token 출력(상태출력)
                }
                count--;//for문 마지막으로 인해 늘어난 count하나 감소(get_token에서 ' '을 거름으로 count--한곳이 빈칸이어도 됨)
                new_expr[n++] = ')';//여러자리 숫자를 사용하면 숫자 구분이 안됨으로 여러자리 숫자는 '(',')'으로 구분
            }
            else {
                return_token(expr, &symbol, &count);//여러자리숫자의 처음 숫자부분으로 count변경
                token = get_token(expr, &symbol, &count);
                new_expr[n++] = symbol;//new_expr에 저장
                printf("%c", symbol);//token 출력(상태출력)
            }
        }
        else if (token == rparen) {//괄호 닫는기호')' 라면
            negative = 0;//')'이므로 nagative = 0
            while (postfixStack[postfixTop] != lparen)//괄호 여는기호'(' 전까지pop해서 new_expr에 저장
                new_expr[n++] = precedenceToChar(postfixPop());
            postfixPop();// 괄호 여는기호는 삭제
            prtPrecedence(token);//token 출력
        }
        else {
            if (token == minus && negative==1) {//negative가 1이고 token이 '-'이면 음수를 나타내는'-'이므로 숫자로 처리
                negative = 0;//숫자이므로 negative = 0
                printf("%c", symbol);//token 출력(상태출력)
                new_expr[n++] = '(';//음수인것을 구분 하기위해서 ()사용
                new_expr[n++] = '-';
				for (token = get_token(expr, &symbol, &count); token != eos && token == operand; token = get_token(expr, &symbol, &count)) {
					//다음 토큰이 숫자가 아닐때까지 반복하여 여러자리 숫자 인식
					new_expr[n++] = symbol;//new_expr에 저장
					printf("%c", symbol);//token 출력(상태출력)
				}
				count--;//for문 마지막으로 인해 늘어난 count하나 감소(get_token에서 ' '을 거름으로 count--한곳이 빈칸이어도 됨)
				new_expr[n++] = ')';//음수 구분
            }
            else {
                negative = 1;//연산자 이므로 negative = 1
                while (isp[postfixStack[postfixTop]] >= icp[token])//나머지는 token의 우선순위가 스택의 top에있는 연산자보다 우선순위가 낮거나 같다면
                    new_expr[n++] = precedenceToChar(postfixPop());//스택의 top의 우선순위가 token보다 낮아질때까지 우선순위가 높은 연산자 pop해서 new_expr에 저장
                postfixPush(token);//스택의 top의 우선순위가 token의 우선순위보다 낮으면 token을 스택에 push
                prtPrecedence(token);//token 출력
            }
        }
        //상태출력( stack top output)
        printf("\t");
        prtPostfixStack();//stack 출력
        if (postfixTop >= 8)//top 칸맞추어 출력
            printf("\t%d\t", postfixTop);
        else if (postfixTop >= 4)
            printf("\t\t%d\t", postfixTop);
        else
            printf("\t\t\t%d\t", postfixTop);
        prtPostfix(new_expr, n - 1);//output출력
        printf("\n");
	}
    while ((token = postfixPop()) != eos)//남은 스택의 연산자
        new_expr[n++] = precedenceToChar(token);//pop해서 new_expr에 저장
    new_expr[n] = '\0';//postfix의 끝을 알려주기위한 '\0'

    //상태출력
    prtPrecedence(token);//token 출력
    printf("\t");
    prtPostfixStack();//stack 출력
    if (postfixTop >= 8)//top 칸맞추어 출력
        printf("\t%d\t", postfixTop);
    else if (postfixTop >= 4)
        printf("\t\t%d\t", postfixTop);
    else
        printf("\t\t\t%d\t", postfixTop);
    prtPostfix(new_expr, n - 1);//output출력
    printf("\n");

    //postfix 수식 출력
    printf("\npostfix 수식 : ");
    prtPostfix(new_expr, n);
    printf("\n");
}

void postfixPush(precedence token) {//postfixStack의 push
    if (postfixTop >= MAX_SIZE - 1) {
        printf("stack is full");
        exit(1);
    }
    else
        postfixStack[++postfixTop] = token;
}

precedence postfixPop() {//postfixStack의 pop
    if (postfixTop == -1) {
        printf("stack is empty");
        exit(1);
    }
    else
        return postfixStack[postfixTop--];
}

char precedenceToChar(precedence token) {//precedence형을 char형으로 바꾸는 함수
    switch (token) {
    case lparen:
        return '(';
        break;
    case rparen:
        return ')';
        break;
    case plus:
        return '+';
        break;
    case minus:
        return '-';
        break;
    case times:
        return '*';
        break;
    case divide:
        return '/';
        break;
    case mod:
        return '%';
        break;
    case power:
        return '^';
        break;
    case not_:
        return '!';
        break;
    default: return ' ';//전부 아니면 ' '리턴(' '는 get_token에서 무시가능하기 때문)
    }
}

void prtPrecedence(precedence token) {//precedence형의 token을 출력하는 함수
    switch (token) {
    case lparen:
        printf("(");
        break;
    case rparen:
        printf(")");
        break;
    case plus:
        printf("+");
        break;
    case minus:
        printf("-");
        break;
    case times:
        printf("*");
        break;
    case divide:
        printf("/");
        break;
    case mod:
        printf("%");
        break;
    case power:
        printf("^");
        break;
    case not_:
        printf("!");
        break;
    default: return;
    }
}


void prtPostfixStack() {//postfixStack을 출력하는 함수
    for (int i = 0; i <= postfixTop; i++) {
        prtPrecedence(postfixStack[i]);
        printf(" ");
    }
}

void prtPostfix(char* new_expr, int n) {//현재의 postfix배열을 출력하는 함수
    for (int i = 0; i <= n; i++) {
        printf("%c", new_expr[i]);
    }
}


int eval(char* new_expr) {//postfix를 계산하는 함수
    precedence token;
    char symbol;
    int i;
    int op1, op2;
    int num = 1;//여러자리 숫자의 값을 가지고있을 변수
    int count = 0;//new_expr의 현재위치를 나타내는 변수
    int n[6] = { 0 };//출력의 자리를 맞추기위해 evalStack의 자리의 수(음수)가 몇 개인지 저장하는 변수
    int m;//출력자리를 맞추기위한 변수
    
    evalTop = -1;

    printf("Token\tStack\t\t\t\tTop\n");

    token = get_token(new_expr, &symbol, &count);//token에 new_expr값 저장

    while (token != eos) {
        if (token == operand) {//토큰이 숫자일경우(1자리 숫자)
            push(symbol - '0');
            printf("%c", symbol);//token 출력
        }
        else if (token == lparen) {//토큰이 '('일때는 다음에 여러자리 숫자 또는 음수(음수 또한 여러자리 일 수 있음)가 있다는 뜻
            if ((token = get_token(new_expr, &symbol, &count)) == minus) {//음수인 경우
                printf("%c", symbol);//token 출력(상태출력)

                token = get_token(new_expr, &symbol, &count);//여러자리 숫자의 처음 숫자 토큰으로
                num = symbol - '0';//여러자리 숫자의 가장 높은 자리 숫자
                printf("%c", symbol);//token 출력(상태출력)
                for (token = get_token(new_expr, &symbol, &count); token != rparen; token = get_token(new_expr, &symbol, &count)) {
                    //다음 토큰이 ')'일때까지 반복하여 여러자리 숫자 인식
                    num *= 10;//자릿수 마다 곱하기10
                    num += (symbol - '0');//문자열로 저장된 다음자리 숫자를 num에 추가
                    printf("%c", symbol);//token 출력(상태출력)
                }
                push(-1 * num);//음수 스택에 저장
            }
            else {//음수가 아니므로 양수인 여러자리 숫자
                count--;//if문에서 늘어난 count감소
                token = get_token(new_expr, &symbol, &count);//여러자리 숫자의 처음 숫자 토큰으로
                num = symbol - '0';//여러자리 숫자의 가장 높은 자리 숫자
                printf("%c", symbol);//token 출력(상태출력)
                for (token = get_token(new_expr, &symbol, &count); token != rparen; token = get_token(new_expr, &symbol, &count)) {
                    //다음 토큰이 ')'일때까지 반복하여 여러자리 숫자 인식
                    num *= 10;//자릿수 마다 곱하기10
                    num += (symbol - '0');//문자열로 저장된 다음자리 숫자를 num에 추가
                    printf("%c", symbol);//token 출력(상태출력)
                }
                push(num);//스택에 저장
            }
        }
        else if (token == not_) {//nott(!)은 단항연산자
            op1 = pop();
            push(!op1);
            printf("%c", symbol);//token 출력(상태출력)
        }
        else {
            op2 = pop();
            op1 = pop();

            switch (token) {
            case plus:
                push(op1 + op2);
                break;
            case minus:
                push(op1 - op2);
                break;
            case times:
                push(op1 * op2);
                break;
            case divide:
                push(op1 / op2);
                break;
            case mod:
                push(op1 % op2);
                break;
            case power:
                num = 1;
                for (i = 0; i < op2; i++) {//power(^)는 right associative연산
                    num *= op1;
                }
                push(num);
                break;
            }
            printf("%c", symbol);//token 출력(상태출력)
        }
        //상태출력(stack top)
        printf("\t");
        for (i = 0; i < 6; i++)//n배열 초기화
            n[i] = 0;
        m = 0;//m초기화
        prtEvalStack(n);//stack 출력
        //자릿수만큼 출력공간 계산
        for (i = 0; i < 6; i++) {
            m += n[i] * (i + 2);
        }
        m += 2 * evalTop + 2;
        for (i = 0; i < 6; i++) {
            m -= n[i];
        }
        if (m > 23)//top 칸맞추어 출력
            printf("\t%d\t", evalTop);
		else if (m > 15)
			printf("\t\t%d\t", evalTop);
		else if (m > 7)
			printf("\t\t\t%d\t", evalTop);
		else
			printf("\t\t\t\t%d\t", evalTop);
		printf("\n");

        token = get_token(new_expr, &symbol, &count);
    }
    return pop(); // 결과를 출력
}

void push(int num) {//evalStack의 push
    if (evalTop >= MAX_SIZE - 1) {
        printf("stack is full");
        exit(1);
    }
    else
        evalStack[++evalTop] = num;
}

int pop() {//evalStack의 pop
    if (evalTop == -1) {
        printf("stack is empty");
        exit(1);
    }
    else
        return evalStack[evalTop--];
}

void prtEvalStack(int* n) {//evalStack을 출력하고 해당 자릿수의 갯수를 n배열에 저장하는 함수
    for (int i = 0; i <= evalTop; i++) {
        printf("%d ", evalStack[i]);
        if (evalStack[i] >= 1000000 || evalStack[i] < -99999)//자릿수에 따라 n배열의 값 변경
            n[5]++;
        else if (evalStack[i] >= 100000 || evalStack[i] < -9999)
            n[4]++;
        else if (evalStack[i] >= 10000 || evalStack[i] < -999)
            n[3]++;
        else if (evalStack[i] >= 1000 || evalStack[i] < -99)
            n[2]++;
        else if (evalStack[i] >= 100 || evalStack[i] < -9)
            n[1]++;
        else if (evalStack[i] >= 10 || evalStack[i] < 0)
            n[0]++;
    }
}

void return_token(char* new_expr, char* symbol, int* count) {//빈칸이 있기 전까지 count를 되돌리는 함수
    --(*count);//현재 이전의 count부터
    for (*symbol = new_expr[--(*count)]; *symbol == ' '; *symbol = new_expr[--(*count)]) {
        ;//*symbol이 ' '이 아닐때까지 count를 낮춘다.
    }
}

precedence get_token(char* new_expr, char* symbol, int* count) {//수식 문자열에서 다음 문자가 무엇인지 반환하는 함수
    //*symbol이 ' '이라면 ' '이 아닐때까지 *symbol = new_expr[(*count)++]을 반복하여
    //' '이 아닌값을 토큰으로 반환
    for (*symbol = new_expr[(*count)++]; *symbol == ' '; *symbol = new_expr[(*count)++]) {
        ;
    }

    switch (*symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    case '%': return mod;
    case '^': return power;
    case '!': return not_;
    case '\0': return eos;//gets_s는 마지막에\0이기 때문
    default: return operand; // 피연산자 리턴
    }
}
