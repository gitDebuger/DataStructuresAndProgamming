#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
bool expandStr(char front, char back){
    if (islower(front) && islower(back) && front < back) return true;
    else if (isupper(front) && isupper(back) && front < back) return true;
    else if (isdigit(front) && isdigit(back) && front < back) return true;
    return false; 
}
int main()
{
    char ans[100];
    char basic[100];
    char ch;
    int j = 0;
    fgets(basic, 100, stdin);
    ans[j++] = basic[0];
    for (int i = 1; basic[i] != 0; i++){
        ch = basic[i];
        if (ch == '-' && expandStr(basic[i - 1], basic[i + 1])){
            for (char c = basic[i - 1] + 1; c < basic[i + 1]; c++){
                ans[j++] = c;
            }
        }else ans[j++] = ch;
    }ans[j] = 0;
    printf("%s", ans);
}