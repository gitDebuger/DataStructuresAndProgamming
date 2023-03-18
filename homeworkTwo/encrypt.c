#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
int main(){
    bool alpha[26] = {false};
    char password[26];
    char ch;
    int i = 0;
    while ((ch = getchar()) != EOF && !isspace(ch)){
        if (!alpha[ch - 'a']){
            alpha[ch - 'a'] = true;
            password[i++] = ch;
        }
    }
    for (ch = 'z'; ch >= 'a'; ch--){
        if (!alpha[ch - 'a']){
            alpha[ch - 'a'] = true;
            password[i++] = ch;
        }
    }
    FILE* fr = fopen("encrypt.txt", "r");
    FILE* fw = fopen("output.txt", "w");
    while ((ch = fgetc(fr)) != EOF){
        if (islower(ch))
            fputc(password[ch - 'a'], fw);
        else fputc(ch, fw);
    }
    fclose(fr);
    fclose(fw);
    return 0;
}