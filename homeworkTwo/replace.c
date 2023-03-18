#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
bool equal(const char _a, const char _b){
    if (isupper(_a) && islower(_b) && _a + 32 == _b) return true;
    if (isupper(_b) && islower(_a) && _b + 32 == _a) return true;
    if (_a == _b) return true;
    return false;
}
int main(){
    FILE* fr = fopen("filein.txt", "r");
    FILE* fw = fopen("fileout.txt", "w");
    char line[100];
    char oldstr[50];
    char newstr[50];
    int i, j;
    int oldstrLength, lineLength, deltaLength;
    scanf("%s%s", oldstr, newstr);
    oldstrLength = strlen(oldstr);
    while (fgets(line, 100, fr) != NULL){
        lineLength = strlen(line);
        deltaLength = lineLength - oldstrLength;
        for (i = 0; i <= deltaLength; i++){
            for (j = 0; j < oldstrLength; j++){
                if (!equal(line[i + j], oldstr[j])){
                    fputc(line[i], fw);
                    break;
                }
            }
            if (j == oldstrLength){
                fputs(newstr, fw);
                i += oldstrLength - 1;
            }
        }
        fputs(line + i, fw);
    }
    fclose(fr);
    fclose(fw);
    return 0;
}