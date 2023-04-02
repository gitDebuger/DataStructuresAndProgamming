#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct funcNode{
    char name[20];
    struct funcNode* next;
};
struct ListNode{
    char funcName[20];
    struct funcNode* funcList;
    struct ListNode* next;
};
typedef struct ListNode* list;
list insert(list funcs, const char* str){
    if (funcs == NULL){
        funcs = malloc(sizeof(struct ListNode));
        funcs->funcList = NULL;
        strcpy(funcs->funcName, str);
        funcs->next = NULL;
        return funcs;
    }
    list node = funcs;
    while (node->next){
        if (strcmp(node->funcName, str) != 0){
            node = node->next;
        }
        else return funcs;
    }
    if (strcmp(node->funcName, str) != 0){
        node->next = malloc(sizeof(struct ListNode));
        node = node->next;
        node->funcList = NULL;
        node->next = NULL;
        strcpy(node->funcName, str);
    }
    return funcs;
}
void addFunc(list funcs, const char* caller, const char* callee){
    struct funcNode* curNode;
    while (funcs){
        if (strcmp(funcs->funcName, caller) == 0){
            if (funcs->funcList == NULL){
                funcs->funcList = malloc(sizeof(struct funcNode));
                curNode = funcs->funcList;
                strcpy(curNode->name, callee);
                curNode->next = NULL;
                return;
            }
            else{
                curNode = funcs->funcList;
                while (curNode->next){
                    if (strcmp(curNode->name, callee) != 0){
                        curNode = curNode->next;
                    }
                    else return;
                }
                if (strcmp(curNode->name, callee) != 0){
                    curNode->next = malloc(sizeof(struct funcNode));
                    curNode = curNode->next;
                    strcpy(curNode->name, callee);
                    curNode->next = NULL;
                    return;
                }
                else return;
            }
        }
        funcs = funcs->next;
    }
}
int main(){
    char funcStack[50][20];
    int topOfStack = -1;
    char curFunc[20];
    list allFuncs = NULL;
    int op;
    topOfStack++;
    scanf("%d %s", &op, curFunc);
    strcpy(funcStack[topOfStack], curFunc);
    allFuncs = insert(allFuncs, curFunc);
    while (topOfStack > -1){
        scanf("%d", &op);
        if (op == 8){
            scanf("%s", curFunc);
            topOfStack++;
            strcpy(funcStack[topOfStack], curFunc);
            allFuncs = insert(allFuncs, curFunc);
            if (topOfStack > 0){
                addFunc(allFuncs, funcStack[topOfStack - 1], curFunc);
            }
        }
        else if (op == 0){
            topOfStack--;
        }
    }
    struct ListNode* mainFunc = allFuncs;
    struct funcNode* moduleFunc;
    while (mainFunc){
        if (mainFunc->funcList == NULL){
            mainFunc = mainFunc->next;
            continue;
        }
        moduleFunc = mainFunc->funcList;
        printf("%s:", mainFunc->funcName);
        while (moduleFunc){
            printf("%s", moduleFunc->name);
            if (moduleFunc->next) printf(",");
            else printf("\n");
            moduleFunc = moduleFunc->next;
        }
        mainFunc = mainFunc->next;
    }
    return 0;
}