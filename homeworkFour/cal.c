#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
struct stkOfChar{
    int topOfStack;
    char* elem;
};
struct stkOfDouble
{
    int topOfStack;
    double* elem;
};
typedef struct stkOfChar* charStack;
typedef struct stkOfDouble* doubleStack;
charStack initialize_charStack(){
    charStack stack = malloc(sizeof(struct stkOfChar));
    stack->topOfStack = -1;
    stack->elem = (char*)malloc(100 * sizeof(char));
    return stack;
}
doubleStack initialize_doubleStack(){
    doubleStack stack = malloc(sizeof(struct stkOfDouble));
    stack->topOfStack = -1;
    stack->elem = (double*)malloc(100 * sizeof(double));
    return stack;
}
bool emptyCharStack(charStack s){
    return s->topOfStack == -1;
}
bool emptyDoubleStack(doubleStack s){
    return s->topOfStack == -1;
}
void pushCharStack(charStack s, char ch){
    s->elem[++s->topOfStack] = ch;
}
void pushDoubleStack(doubleStack s, double num){
    s->elem[++s->topOfStack] = num;
}
char topCharStack(charStack s){
    return s->elem[s->topOfStack];
}
double topDoubleStack(doubleStack s){
    return s->elem[s->topOfStack];
}
void popCharStack(charStack s){
    s->topOfStack--;
}
void popDoubleStack(doubleStack s){
    s->topOfStack--;
}
int precedence(const char ch){
    if (ch == '+' || ch == '-') return 1;
    return 2;
}
char* infixToPostfix(char* infix){
    char* postfix = malloc(100 * sizeof(char));
    int j = 0;
    charStack ops = initialize_charStack();
    for (int i = 0; infix[i] != 0; i++){
        char ch = infix[i];
        if (ch == ' ') continue;
        if (isdigit(ch)){
            postfix[j++] = ch;
        }
        else{
            postfix[j++] = ' ';
            if (emptyCharStack(ops)) pushCharStack(ops, ch);
            else if (ch == '(') pushCharStack(ops, ch);
            else if (ch == ')'){
                while (topCharStack(ops) != '('){
                    postfix[j++] = topCharStack(ops);
                    popCharStack(ops);
                    postfix[j++] = ' ';
                }popCharStack(ops);
            }
            else if (precedence(ch) == 1){
                while (!emptyCharStack(ops) && topCharStack(ops) != '('){
                    postfix[j++] = topCharStack(ops);
                    popCharStack(ops);
                    postfix[j++] = ' ';
                }pushCharStack(ops, ch);
            }
            else if (precedence(ch) == 2){
                while (!emptyCharStack(ops) && precedence(topCharStack(ops)) != 1 && topCharStack(ops) != '('){
                    postfix[j++] = topCharStack(ops);
                    popCharStack(ops);
                    postfix[j++] = ' ';
                }pushCharStack(ops, ch);
            }
        }
    }
    while (!emptyCharStack(ops)){
        postfix[j++] = topCharStack(ops);
        popCharStack(ops);
        postfix[j++] = ' ';
    }
    postfix[j] = 0;
    free(ops->elem);
    free(ops);
    return postfix;
}
double postfixToNum(char* postfix){
    int num = 0;
    bool flag;
    double numA, numB, centerNum;
    doubleStack numbers = initialize_doubleStack();
    for (int i = 0; postfix[i] != 0; i++){
        char ch = postfix[i];
        if (isdigit(ch)){
            flag = true;
            num = num * 10 + ch - 48;
        }
        else{
            if (flag){
                pushDoubleStack(numbers, num);
                flag = false;
                num = 0;
            }
            if (ch == '+'){
                numA = topDoubleStack(numbers);
                popDoubleStack(numbers);
                numB = topDoubleStack(numbers);
                popDoubleStack(numbers);
                centerNum = numB + numA;
                pushDoubleStack(numbers, centerNum);
            }else if (ch == '-'){
                numA = topDoubleStack(numbers);
                popDoubleStack(numbers);
                numB = topDoubleStack(numbers);
                popDoubleStack(numbers);
                centerNum = numB - numA;
                pushDoubleStack(numbers, centerNum);
            }else if (ch == '*'){
                numA = topDoubleStack(numbers);
                popDoubleStack(numbers);
                numB = topDoubleStack(numbers);
                popDoubleStack(numbers);
                centerNum = numB * numA;
                pushDoubleStack(numbers, centerNum);
            }else if (ch == '/'){
                numA = topDoubleStack(numbers);
                popDoubleStack(numbers);
                numB = topDoubleStack(numbers);
                popDoubleStack(numbers);
                centerNum = numB / numA;
                pushDoubleStack(numbers, centerNum);
            }
        }
    }
    if (emptyDoubleStack(numbers)) return num;
    centerNum = topDoubleStack(numbers);
    free(numbers->elem);
    free(numbers);
    return centerNum;
}
int main(){
    char* infix = malloc(100 * sizeof(char));
    char c;
    int i = 0;
    while ((c = getchar()) != '=') infix[i++] = c;
    infix[i] = 0;
    char* postfix = infixToPostfix(infix);
    double ans = postfixToNum(postfix);
    printf("%.2lf", ans);
    return 0;
}