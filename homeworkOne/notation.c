#include <stdio.h>
#include <ctype.h>
int main(){
    char num[105];
    char ans[105];
    int exponent;
    int i;
    int j = 0;
    fgets(num, 105, stdin);
    if (num[0] == '0'){
        exponent = 1;
        for (i = 2; num[i] == '0'; i++, exponent++);
        if (isspace(num[i + 1])){
            ans[j++] = num[i];
            ans[j++] = 'e';
            ans[j++] = '-';
            if (exponent > 9){
                ans[j++] = exponent / 10 + '0';
                ans[j++] = exponent % 10 + '0';
            }else ans[j++] = exponent + '0';
            ans[j] = 0;
        }else{
            ans[j++] = num[i++];
            ans[j++] = '.';
            for (; !isspace(num[i]); i++){
                ans[j++] = num[i];
            }
            ans[j++] = 'e';
            ans[j++] = '-';
            if (exponent > 9){
                ans[j++] = exponent / 10 + '0';
                ans[j++] = exponent % 10 + '0';
            }else ans[j++] = exponent + '0';
            ans[j] = 0;
        }
    }
    else{
        ans[j++] = num[0];
        ans[j++] = '.';
        exponent = 0;
        for (i = 1; num[i] != '.'; i++, j++, exponent++){
            ans[j] = num[i];
        }
        for (i++; !isspace(num[i]); i++){
            ans[j++] = num[i];
        }
        ans[j++] = 'e';
        if (exponent > 9){
            ans[j++] = exponent / 10 + '0';
            ans[j++] = exponent % 10 + '0';
        }else ans[j++] = exponent + '0';
        ans[j] = 0;
    }
    printf("%s", ans);
}