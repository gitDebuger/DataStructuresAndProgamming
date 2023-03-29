#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct BRACKET{
    char brac;
    int position;
};
typedef struct BRACKET bracket;
struct myStack{
    bracket* elements;
    int topOfStack;
};
typedef struct myStack stack;
int main(){
    FILE* fr = fopen("example.c", "r");
    char ans[250];
    int ptr = 0;
    char currentLine[205];
    int numbersOfLine = 0;
    stack bracs;
    bracs.elements = malloc(100 * sizeof(bracket));
    bracs.topOfStack = -1;

    int i;
    bool flag = false;
    while (fgets(currentLine, 205, fr) != NULL){
        numbersOfLine++;
        for (i = 0; currentLine[i]; i++){
            flag = false;
            if (currentLine[i] == '('){
                bracs.elements[++bracs.topOfStack].brac = '(';
                bracs.elements[bracs.topOfStack].position = numbersOfLine;
                ans[ptr++] = '(';
            }
            else if (currentLine[i] == ')'){
                if (bracs.elements[bracs.topOfStack].brac == '('){
                    ans[ptr++] = ')';
                    bracs.topOfStack--;
                }
                else{
                    printf("without maching ')' at line %d", numbersOfLine);
                    return 0;
                }
            }
            else if (currentLine[i] == '{'){
                if (bracs.elements[bracs.topOfStack].brac == '('){
                    printf("without maching '(' at line %d", 
                    bracs.elements[bracs.topOfStack].position);
                    return 0;
                }
                else{
                    ans[ptr++] = '{';
                    bracs.elements[++bracs.topOfStack].brac = '{';
                    bracs.elements[bracs.topOfStack].position = numbersOfLine;
                }
            }
            else if (currentLine[i] == '}'){
                if (bracs.elements[bracs.topOfStack].brac == '{'){
                    ans[ptr++] = '}';
                    bracs.topOfStack--;
                }
                else{
                    printf("without maching '}' at line %d", numbersOfLine);
                    return 0;
                }
            }
            /* '/'不会单独存在于程序代码内 */
            else if (currentLine[i] == '/'){
                /* 遇到单行注释，直接跳过本行，也就是跳出本层循环，进入下一行的处理阶段 */
                if (currentLine[i + 1] == '/'){
                    break;
                }
                /* 多行注释只有遇到右边界才会截断，期间遇到左边界不会更新左边界信息 */
                /* 多行注释内的引号内的信息不会被视作字符串而被忽略 */
                else if (currentLine[i + 1] == '*'){
                    for (i += 2; currentLine[i]; i++){
                        if (currentLine[i] == '*' && currentLine[i + 1] == '/'){
                            flag = true;
                            break;
                        }
                    }
                    while (!flag){
                        fgets(currentLine, 205, fr);
                        numbersOfLine++;
                        for (i = 0; currentLine[i]; i++){
                            if (currentLine[i] == '*' && currentLine[i + 1] == '/'){
                                flag = true;
                                i++;
                                break;
                            }
                        }
                    }
                }
            }
            /* 需要注意的是字符串的双引号遵循最近匹配原则 */
            /* 字符串仅能存在于单行内，即不能将字符串分行书写 */
            /* 所以遇到双引号，将指针向前推进，直到遇到与该引号匹配的右引号 */
            else if (currentLine[i] == '\"'){
                while (currentLine[++i] != '\"');
            }
            /* 遇到单引号包裹的字符常量，直接跳过这一部分 */
            else if (currentLine[i] == '\''){
                while (currentLine[++i] != '\'');
            }
        }
    }
    if (bracs.topOfStack == -1){
        for (i = 0; i < ptr; i++){
            printf("%c", ans[i]);
        }
    }
    else{
        printf("without maching '%c' at line %d", bracs.elements[0].brac, bracs.elements[0].position);
    }
    return 0;
}
