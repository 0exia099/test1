#pragma warning(disable: 4778)//printf("%");�ϸ� ������ ���(c4778:printf:���Ĺ��ڿ� '%'��(��) ���ᵵ�� �ʾҽ��ϴ�.)�� ���ֱ�����
#pragma warning(disable: 26812)//enum��� enum class�� ����϶�� ��� ���ֱ�����
#pragma warning(disable: 6385)//92�ٿ��� c6385��� �ߴ°��� ���ֱ�����

//@file : main.cpp
/*infix������ ������ �Է¹޾� expr�� �����ϰ�
postfix�� �����Ͽ� new_expr�� ������ ��
postfix�� ����Ͽ� ���� ����ϴ� �ڵ�
postfix�� ������ ���� postfix�� ����Ҷ���
����(token, stack, top, output)�� ����Ѵ�.
���� ^(power������), !(not������)�� �����ϸ�
�����ڸ��� ���ڿ� ������ �ν��Ѵ�. �����ڸ� ���ڿ� ������ '(',')'�� ����Ͽ� �����Ѵ�.
������ �Է��Ҷ� ���� ���鹮�ڴ� ���°����� ó���Ѵ�.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef enum {//(����)�ƹ� ������ ���µ� �ѹ��� �ٸ� �κ� ���� �߿� typedef�� ';'�� �ʿ��ϴٰ� ������ �߻��� ���� ����. ��ٸ��� ������
    lparen, rparen, plus, minus, times, divide, mod, power, not_, eos, operand
} precedence;

//������ �켱����
//           (  )  +  -  *  /  %  ^  ! eos ����
int isp[] = { 0,19,12,12,13,13,13,18,15,0 };//���ÿ� ����� �������� �켱����
int icp[] = { 20,19,12,12,13,13,13,18,15,0 };//�Է� �������� �켱����

void postfix(char* expr, char* new_expr);//iffix�� postfix�� �ٲٴ� �Լ�

precedence postfixStack[MAX_SIZE];//infix�� postfix�� �ٲٴµ� �����ڰ� �� ����
int postfixTop = -1;//postfixStack�� top
void postfixPush(precedence token);//postfixStack�� push
precedence postfixPop();//postfixStack�� pop

char precedenceToChar(precedence token);//precedence���� token�� char������ �ٲٴ� �Լ�
void prtPrecedence(precedence token);//precedence���� token�� ����ϴ� �Լ�
void prtPostfixStack();//postfixStack�� ����ϴ� �Լ�
void prtPostfix(char* new_expr, int n);//������ postfix�迭�� ����ϴ� �Լ�

int eval(char* new_expr);//postfix�� ����ϴ� �Լ�

int evalStack[MAX_SIZE];//postfix����� ���� ���ڰ� �� ����
int evalTop = -1;//evalStack�� top
void push(int num);//evalStack�� push
int pop();//evalStack�� pop
void prtEvalStack(int* n);//evalStack�� ����ϰ� �ش� �ڸ����� ������ n�迭�� �����ϴ� �Լ�

void return_token(char* new_expr, char* symbol, int* count);//��ĭ�� �ֱ� ������ count�� �ǵ����� �Լ�
precedence get_token(char* new_expr, char* symbol, int* count);//���� ���ڿ����� ���� ���ڰ� �������� ��ȯ�ϴ� �Լ�

int main() {
    char expr[MAX_SIZE];//infix�� �����ϴ� �迭
    char new_expr[MAX_SIZE];//postfix�� �����ϴ� �迭

    //infix�Է¹���
    printf("infix ���� : ");
    gets_s(expr);

    postfix(expr, new_expr);//infix->postfix��
    printf("eval() ��� : %d\n", eval(new_expr));//postfix���

    //��������(exe)����� �ٷ� ����ǹǷ� �Ͻ������߰� 
    system("pause");
    return 0;
}

void postfix(char* expr, char* new_expr) {
    char symbol;
    precedence token;
    int count = 0;//expr�迭�� ���°���� ��Ÿ���� ����
    int n = 0;//new_expr�迭�� ���°���� ��Ÿ���� ����
    int negative = 0;//token�� ')'�� �ƴ� �����ڸ� 1�� �ǰ� negative�� 1�϶� ���� token�� -�� ����  
    postfixTop = -1;

    printf("Token\tStack\t\t\tTop\tOutput\n");

    postfixPush(eos);//���ÿ� eos����
	for (token = get_token(expr, &symbol, &count); token != eos; token = get_token(expr, &symbol, &count)) {//expr�� �������� token�� expr�� �� ����

        if (token == operand) {//���ڶ��

            negative = 0;//�ǿ����� �̹Ƿ� negative = 0

            if ((token = get_token(expr, &symbol, &count)) == operand) {//���� ��ū�� ���ڶ�� �����ڸ� ����

                new_expr[n++] = '(';//�����ڸ� ���ڸ� ����ϸ� ���� ������ �ȵ����� �����ڸ� ���ڴ� '(',')'���� ����

                return_token(expr, &symbol, &count);//�����ڸ������� ó�� ���ںκ����� count����

                for (token = get_token(expr, &symbol, &count); token != eos && token == operand; token = get_token(expr, &symbol, &count)) {
                    //���� ��ū�� ���ڰ� �ƴҶ����� �ݺ��Ͽ� �����ڸ� ���� �ν�
                    new_expr[n++] = symbol;//new_expr�� ����
                    printf("%c", symbol);//token ���(�������)
                }
                count--;//for�� ���������� ���� �þ count�ϳ� ����(get_token���� ' '�� �Ÿ����� count--�Ѱ��� ��ĭ�̾ ��)
                new_expr[n++] = ')';//�����ڸ� ���ڸ� ����ϸ� ���� ������ �ȵ����� �����ڸ� ���ڴ� '(',')'���� ����
            }
            else {
                return_token(expr, &symbol, &count);//�����ڸ������� ó�� ���ںκ����� count����
                token = get_token(expr, &symbol, &count);
                new_expr[n++] = symbol;//new_expr�� ����
                printf("%c", symbol);//token ���(�������)
            }
        }
        else if (token == rparen) {//��ȣ �ݴ±�ȣ')' ���
            negative = 0;//')'�̹Ƿ� nagative = 0
            while (postfixStack[postfixTop] != lparen)//��ȣ ���±�ȣ'(' ������pop�ؼ� new_expr�� ����
                new_expr[n++] = precedenceToChar(postfixPop());
            postfixPop();// ��ȣ ���±�ȣ�� ����
            prtPrecedence(token);//token ���
        }
        else {
            if (token == minus && negative==1) {//negative�� 1�̰� token�� '-'�̸� ������ ��Ÿ����'-'�̹Ƿ� ���ڷ� ó��
                negative = 0;//�����̹Ƿ� negative = 0
                printf("%c", symbol);//token ���(�������)
                new_expr[n++] = '(';//�����ΰ��� ���� �ϱ����ؼ� ()���
                new_expr[n++] = '-';
				for (token = get_token(expr, &symbol, &count); token != eos && token == operand; token = get_token(expr, &symbol, &count)) {
					//���� ��ū�� ���ڰ� �ƴҶ����� �ݺ��Ͽ� �����ڸ� ���� �ν�
					new_expr[n++] = symbol;//new_expr�� ����
					printf("%c", symbol);//token ���(�������)
				}
				count--;//for�� ���������� ���� �þ count�ϳ� ����(get_token���� ' '�� �Ÿ����� count--�Ѱ��� ��ĭ�̾ ��)
				new_expr[n++] = ')';//���� ����
            }
            else {
                negative = 1;//������ �̹Ƿ� negative = 1
                while (isp[postfixStack[postfixTop]] >= icp[token])//�������� token�� �켱������ ������ top���ִ� �����ں��� �켱������ ���ų� ���ٸ�
                    new_expr[n++] = precedenceToChar(postfixPop());//������ top�� �켱������ token���� ������������ �켱������ ���� ������ pop�ؼ� new_expr�� ����
                postfixPush(token);//������ top�� �켱������ token�� �켱�������� ������ token�� ���ÿ� push
                prtPrecedence(token);//token ���
            }
        }
        //�������( stack top output)
        printf("\t");
        prtPostfixStack();//stack ���
        if (postfixTop >= 8)//top ĭ���߾� ���
            printf("\t%d\t", postfixTop);
        else if (postfixTop >= 4)
            printf("\t\t%d\t", postfixTop);
        else
            printf("\t\t\t%d\t", postfixTop);
        prtPostfix(new_expr, n - 1);//output���
        printf("\n");
	}
    while ((token = postfixPop()) != eos)//���� ������ ������
        new_expr[n++] = precedenceToChar(token);//pop�ؼ� new_expr�� ����
    new_expr[n] = '\0';//postfix�� ���� �˷��ֱ����� '\0'

    //�������
    prtPrecedence(token);//token ���
    printf("\t");
    prtPostfixStack();//stack ���
    if (postfixTop >= 8)//top ĭ���߾� ���
        printf("\t%d\t", postfixTop);
    else if (postfixTop >= 4)
        printf("\t\t%d\t", postfixTop);
    else
        printf("\t\t\t%d\t", postfixTop);
    prtPostfix(new_expr, n - 1);//output���
    printf("\n");

    //postfix ���� ���
    printf("\npostfix ���� : ");
    prtPostfix(new_expr, n);
    printf("\n");
}

void postfixPush(precedence token) {//postfixStack�� push
    if (postfixTop >= MAX_SIZE - 1) {
        printf("stack is full");
        exit(1);
    }
    else
        postfixStack[++postfixTop] = token;
}

precedence postfixPop() {//postfixStack�� pop
    if (postfixTop == -1) {
        printf("stack is empty");
        exit(1);
    }
    else
        return postfixStack[postfixTop--];
}

char precedenceToChar(precedence token) {//precedence���� char������ �ٲٴ� �Լ�
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
    default: return ' ';//���� �ƴϸ� ' '����(' '�� get_token���� ���ð����ϱ� ����)
    }
}

void prtPrecedence(precedence token) {//precedence���� token�� ����ϴ� �Լ�
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


void prtPostfixStack() {//postfixStack�� ����ϴ� �Լ�
    for (int i = 0; i <= postfixTop; i++) {
        prtPrecedence(postfixStack[i]);
        printf(" ");
    }
}

void prtPostfix(char* new_expr, int n) {//������ postfix�迭�� ����ϴ� �Լ�
    for (int i = 0; i <= n; i++) {
        printf("%c", new_expr[i]);
    }
}


int eval(char* new_expr) {//postfix�� ����ϴ� �Լ�
    precedence token;
    char symbol;
    int i;
    int op1, op2;
    int num = 1;//�����ڸ� ������ ���� ���������� ����
    int count = 0;//new_expr�� ������ġ�� ��Ÿ���� ����
    int n[6] = { 0 };//����� �ڸ��� ���߱����� evalStack�� �ڸ��� ��(����)�� �� ������ �����ϴ� ����
    int m;//����ڸ��� ���߱����� ����
    
    evalTop = -1;

    printf("Token\tStack\t\t\t\tTop\n");

    token = get_token(new_expr, &symbol, &count);//token�� new_expr�� ����

    while (token != eos) {
        if (token == operand) {//��ū�� �����ϰ��(1�ڸ� ����)
            push(symbol - '0');
            printf("%c", symbol);//token ���
        }
        else if (token == lparen) {//��ū�� '('�϶��� ������ �����ڸ� ���� �Ǵ� ����(���� ���� �����ڸ� �� �� ����)�� �ִٴ� ��
            if ((token = get_token(new_expr, &symbol, &count)) == minus) {//������ ���
                printf("%c", symbol);//token ���(�������)

                token = get_token(new_expr, &symbol, &count);//�����ڸ� ������ ó�� ���� ��ū����
                num = symbol - '0';//�����ڸ� ������ ���� ���� �ڸ� ����
                printf("%c", symbol);//token ���(�������)
                for (token = get_token(new_expr, &symbol, &count); token != rparen; token = get_token(new_expr, &symbol, &count)) {
                    //���� ��ū�� ')'�϶����� �ݺ��Ͽ� �����ڸ� ���� �ν�
                    num *= 10;//�ڸ��� ���� ���ϱ�10
                    num += (symbol - '0');//���ڿ��� ����� �����ڸ� ���ڸ� num�� �߰�
                    printf("%c", symbol);//token ���(�������)
                }
                push(-1 * num);//���� ���ÿ� ����
            }
            else {//������ �ƴϹǷ� ����� �����ڸ� ����
                count--;//if������ �þ count����
                token = get_token(new_expr, &symbol, &count);//�����ڸ� ������ ó�� ���� ��ū����
                num = symbol - '0';//�����ڸ� ������ ���� ���� �ڸ� ����
                printf("%c", symbol);//token ���(�������)
                for (token = get_token(new_expr, &symbol, &count); token != rparen; token = get_token(new_expr, &symbol, &count)) {
                    //���� ��ū�� ')'�϶����� �ݺ��Ͽ� �����ڸ� ���� �ν�
                    num *= 10;//�ڸ��� ���� ���ϱ�10
                    num += (symbol - '0');//���ڿ��� ����� �����ڸ� ���ڸ� num�� �߰�
                    printf("%c", symbol);//token ���(�������)
                }
                push(num);//���ÿ� ����
            }
        }
        else if (token == not_) {//nott(!)�� ���׿�����
            op1 = pop();
            push(!op1);
            printf("%c", symbol);//token ���(�������)
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
                for (i = 0; i < op2; i++) {//power(^)�� right associative����
                    num *= op1;
                }
                push(num);
                break;
            }
            printf("%c", symbol);//token ���(�������)
        }
        //�������(stack top)
        printf("\t");
        for (i = 0; i < 6; i++)//n�迭 �ʱ�ȭ
            n[i] = 0;
        m = 0;//m�ʱ�ȭ
        prtEvalStack(n);//stack ���
        //�ڸ�����ŭ ��°��� ���
        for (i = 0; i < 6; i++) {
            m += n[i] * (i + 2);
        }
        m += 2 * evalTop + 2;
        for (i = 0; i < 6; i++) {
            m -= n[i];
        }
        if (m > 23)//top ĭ���߾� ���
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
    return pop(); // ����� ���
}

void push(int num) {//evalStack�� push
    if (evalTop >= MAX_SIZE - 1) {
        printf("stack is full");
        exit(1);
    }
    else
        evalStack[++evalTop] = num;
}

int pop() {//evalStack�� pop
    if (evalTop == -1) {
        printf("stack is empty");
        exit(1);
    }
    else
        return evalStack[evalTop--];
}

void prtEvalStack(int* n) {//evalStack�� ����ϰ� �ش� �ڸ����� ������ n�迭�� �����ϴ� �Լ�
    for (int i = 0; i <= evalTop; i++) {
        printf("%d ", evalStack[i]);
        if (evalStack[i] >= 1000000 || evalStack[i] < -99999)//�ڸ����� ���� n�迭�� �� ����
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

void return_token(char* new_expr, char* symbol, int* count) {//��ĭ�� �ֱ� ������ count�� �ǵ����� �Լ�
    --(*count);//���� ������ count����
    for (*symbol = new_expr[--(*count)]; *symbol == ' '; *symbol = new_expr[--(*count)]) {
        ;//*symbol�� ' '�� �ƴҶ����� count�� �����.
    }
}

precedence get_token(char* new_expr, char* symbol, int* count) {//���� ���ڿ����� ���� ���ڰ� �������� ��ȯ�ϴ� �Լ�
    //*symbol�� ' '�̶�� ' '�� �ƴҶ����� *symbol = new_expr[(*count)++]�� �ݺ��Ͽ�
    //' '�� �ƴѰ��� ��ū���� ��ȯ
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
    case '\0': return eos;//gets_s�� ��������\0�̱� ����
    default: return operand; // �ǿ����� ����
    }
}