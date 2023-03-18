#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define cnt 85
int strToNum(char* str, int* num){
    int i, j;
    int length = strlen(str);
    int realLength = 0;
    for (i = 0; str[i] == '0'; i++);
    if (i == length){
        num[0] = 0;
        realLength = 1;
    }else for (j = length - 1; j >= i; j--, realLength++) num[realLength] = str[j] - '0';
    return realLength;
}
int sub(int* numA, int* numB, int* ansNum, int lengthA, int lengthB){
    int ansLength;
    int flag = 0;
    for (ansLength = 0; ansLength < lengthB; ansLength++){
        if (numA[ansLength] - flag >= numB[ansLength]){
            ansNum[ansLength] = numA[ansLength] - flag - numB[ansLength];
            flag = 0;
        }else{
            ansNum[ansLength] = numA[ansLength] - flag + 10 - numB[ansLength];
            flag = 1;
        }
    }
    while (ansLength < lengthA){
        if (numA[ansLength] - flag >= 0){
            ansNum[ansLength] = numA[ansLength] - flag;
            ansLength++;
            flag = 0;
        }else{
            ansNum[ansLength] = numA[ansLength] - flag + 10;
            ansLength++;
            flag = 1;
        }
    }
    return ansLength;
}
int main(){
    char strA[cnt];
    char strB[cnt];
    int numA[cnt];
    int numB[cnt];
    int ansNum[cnt];
    int lengthA, lengthB, ansLength;
    int i;
    bool flag;
    fgets(strA, 85, stdin);
    fgets(strB, 85, stdin);
    lengthA = strToNum(strA, numA);
    lengthB = strToNum(strB, numB);
    if (lengthA > lengthB) ansLength = sub(numA, numB, ansNum, lengthA, lengthB), flag = true;
    else if (lengthA < lengthB) ansLength = sub(numB, numA, ansNum, lengthB, lengthA), flag = false;
    else{
        for (i = lengthA - 1; i >= 0; i--){
            if (numA[i] > numB[i]){
                ansLength = sub(numA, numB, ansNum, lengthA, lengthB);
                flag = true;
                break;
            }else if (numA[i] < numB[i]){
                ansLength = sub(numB, numA, ansNum, lengthB, lengthA);
                flag = false;
                break;
            }
        }
        if (i == -1){
            printf("0");
            return 0;
        }
    }
    if (!flag) printf("-");
    for (i = ansLength - 1; ansNum[i] == 0; i--);
    for (; i > 0; i--) printf("%d", ansNum[i]);
    return 0;
}