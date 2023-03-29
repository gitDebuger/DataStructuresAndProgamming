#include <stdio.h>
#include <stdlib.h>
struct STACK{
    int maxNum;
    int topOfStack;
    int* elements;
};
typedef struct STACK stack;
int main(){
    int opreator;
    int num;
    stack numbers;
    numbers.maxNum = 100;
    numbers.topOfStack = -1;
    numbers.elements = malloc(100 * sizeof(int));
    for (;;){
        scanf("%d", &opreator);
        if (opreator == -1) break;
        else if (opreator == 1){
            scanf("%d", &num);
            if (numbers.topOfStack == numbers.maxNum - 1){
                printf("error ");
            }
            else{
                numbers.elements[++numbers.topOfStack] = num;
            }
        }
        else if (opreator == 0){
            if (numbers.topOfStack == -1){
                printf("error ");
            }
            else{
                printf("%d ", numbers.elements[numbers.topOfStack--]);
            }
        }
    }
    return 0;
}