#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
struct stkOfChar{
    int topOfStack;
    char* elem;
};
struct stkOfInt
{
    int topOfStack;
    int* elem;
};
typedef struct stkOfChar* charStack;
typedef struct stkOfInt* intStack;
charStack initialize_charStack(){
    charStack stack = malloc(sizeof(struct stkOfChar));
    stack->topOfStack = -1;
    stack->elem = (char*)malloc(100 * sizeof(char));
    return stack;
}
intStack initialize_intStack(){
    intStack stack = malloc(sizeof(struct stkOfInt));
    stack->topOfStack = -1;
    stack->elem = (int*)malloc(100 * sizeof(int));
    return stack;
}
bool emptyCharStack(charStack s){
    return s->topOfStack == -1;
}
bool emptyIntStack(intStack s){
    return s->topOfStack == -1;
}
void pushCharStack(charStack s, char ch){
    s->elem[++s->topOfStack] = ch;
}
void pushIntStack(intStack s, int num){
    s->elem[++s->topOfStack] = num;
}
char topCharStack(charStack s){
    return s->elem[s->topOfStack];
}
int topIntStack(intStack s){
    return s->elem[s->topOfStack];
}
void popCharStack(charStack s){
    s->topOfStack--;
}
void popIntStack(intStack s){
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
int postfixToNum(char* postfix){
    int num = 0;
    bool flag;
    int numA, numB, centerNum;
    intStack numbers = initialize_intStack();
    for (int i = 0; postfix[i] != 0; i++){
        char ch = postfix[i];
        if (isdigit(ch)){
            flag = true;
            num = num * 10 + ch - 48;
        }
        else{
            if (flag){
                pushIntStack(numbers, num);
                flag = false;
                num = 0;
            }
            if (ch == '+'){
                numA = topIntStack(numbers);
                popIntStack(numbers);
                numB = topIntStack(numbers);
                popIntStack(numbers);
                centerNum = numB + numA;
                pushIntStack(numbers, centerNum);
            }else if (ch == '-'){
                numA = topIntStack(numbers);
                popIntStack(numbers);
                numB = topIntStack(numbers);
                popIntStack(numbers);
                centerNum = numB - numA;
                pushIntStack(numbers, centerNum);
            }else if (ch == '*'){
                numA = topIntStack(numbers);
                popIntStack(numbers);
                numB = topIntStack(numbers);
                popIntStack(numbers);
                centerNum = numB * numA;
                pushIntStack(numbers, centerNum);
            }else if (ch == '/'){
                numA = topIntStack(numbers);
                popIntStack(numbers);
                numB = topIntStack(numbers);
                popIntStack(numbers);
                centerNum = numB / numA;
                pushIntStack(numbers, centerNum);
            }
        }
    }
    if (emptyIntStack(numbers)) return num;
    centerNum = topIntStack(numbers);
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
    int ans = postfixToNum(postfix);
    printf("%d", ans);
    return 0;
}