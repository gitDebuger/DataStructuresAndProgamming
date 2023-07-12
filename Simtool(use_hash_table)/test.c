#include <stdio.h>
int main(int argc, char** argv, char** envp){
    printf("%d\n", argc);
    for (int i = 0; i < argc; i++){
        printf("%s\n", argv[i]);
    }
    for (int i = 0; envp[i]; i++){
        printf("%s\n", envp[i]);
    }
    return 0;
}