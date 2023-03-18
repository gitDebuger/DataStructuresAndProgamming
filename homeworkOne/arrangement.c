#include <stdio.h>
#include <stdbool.h>
void dfs(int k, int* num, bool* flag, int cnt){
    if (cnt == k){
        for (int i = 0; i < k; i++){
            printf("%d ", num[i]);
        }printf("\n");
        return;
    }
    for (int i = 1; i <= k; i++){
        if (flag[i - 1] == false){
            num[cnt] = i;
            flag[i - 1] = true;
            dfs(k, num, flag, cnt + 1);
            flag[i - 1] = false;
        }
    }
}
int main(){
    bool flag[10] = {false};
    int num[10];
    int n;
    scanf("%d", &n);
    dfs(n, num, flag, 0);
    return 0;
}