#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct OPERATION{
    int op;
    int pos;
    char* str;
};
typedef struct OPERATION operation; 
struct STACK{
    int topOfStack;
    operation* ops;
};
typedef struct STACK stack;
void insert(char* text, int posi, char* str, stack* s){
    int lengthText = strlen(text);
    int lengthStr = strlen(str);
    s->topOfStack++;
    s->ops[s->topOfStack].op = 1;
    s->ops[s->topOfStack].pos = posi;
    s->ops[s->topOfStack].str = malloc((lengthStr + 1) * sizeof(char));
    strcpy(s->ops[s->topOfStack].str, str);
    
    if (posi == lengthText){
        strcat(text, str);
    }
    else{
        for (int i = lengthText; i >= posi; i--){
            text[i + lengthStr] = text[i]; 
        }
        for (int i = 0; str[i]; i++){
            text[posi + i] = str[i];
        }
    }
}
void delete(char* text, int posi, int num, stack* s){
    int lengthText = strlen(text);
    s->topOfStack++;
    s->ops[s->topOfStack].op = 2;
    s->ops[s->topOfStack].pos = posi;
    if (lengthText - posi <= num){
        s->ops[s->topOfStack].str = malloc((lengthText - posi + 1) * sizeof(char));
        strcpy(s->ops[s->topOfStack].str, text + posi);
        text[posi] = 0;
    }
    else{
        s->ops[s->topOfStack].str = malloc((num + 1) * sizeof(char));
        for (int i = 0; i < num; i++){
            s->ops[s->topOfStack].str[i] = text[posi + i];
        }
        s->ops[s->topOfStack].str[num] = 0;
        for (int i = posi + num; i <= lengthText; i++){
            text[i - num] = text[i];
        }
    }
}
void undo(char* text, stack* s){
    if (s->topOfStack == -1) return;
    int textLength = strlen(text);
    int strLength = strlen(s->ops[s->topOfStack].str);
    int posi = s->ops[s->topOfStack].pos;
    char* str = s->ops[s->topOfStack].str;
    if (s->ops[s->topOfStack].op == 1){
        for (int i = s->ops[s->topOfStack].pos; i + strLength <= textLength; i++){
            text[i] = text[i + strLength];
        }
    }
    else{
        for (int i = textLength; i >= posi; i--){
            text[i + strLength] = text[i];
        }
        for (int i = 0; str[i]; i++){
            text[posi + i] = str[i];
        }
    }
    free(str);
    s->topOfStack--;
}
int main(){
    char text[550];
    stack s;
    s.topOfStack = -1;
    s.ops = malloc(50 * sizeof(operation));
    int n;
    gets(text);
    int op;
    int position;
    char obj[550];
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d %d %s", &op, &position, obj);
        s.topOfStack++;
        s.ops[s.topOfStack].op = op;
        s.ops[s.topOfStack].pos = position;
        s.ops[s.topOfStack].str = malloc((strlen(obj) + 1) * sizeof(char));
        strcpy(s.ops[s.topOfStack].str, obj);
    }
    
    int numOfChar;
    for (;;){
        scanf("%d", &op);
        if (op == 1){
            scanf("%d %s", &position, obj);
            insert(text, position, obj, &s);
        }
        else if (op == 2){
            scanf("%d %d", &position, &numOfChar);
            delete(text, position, numOfChar, &s);
        }
        else if (op == 3){
            undo(text, &s);
        }
        else if (op == -1){
            break;
        }
    }
    printf("%s", text);
    return 0;
}