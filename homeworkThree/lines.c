#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct LINE{
    int leftx;
    int lefty;
    int rightx;
    int righty;
    bool flag;
};
typedef struct LINE line;

int cmp(const void* _a, const void* _b){
    line* a = (line*)_a;
    line* b = (line*)_b;
    return a->leftx - b->leftx;
}
int main(){
    line lines[100];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d %d %d %d", &lines[i].leftx, &lines[i].lefty, &lines[i].rightx, &lines[i].righty);
        lines[i].flag = false;
    }
    qsort(lines, n, sizeof(line), cmp);
    
    int max = 0;
    int cnt = 0;
    int i, j;
    int x, y;
    int pointx, pointy;
    for (i = 0; i < n; i++){
        if (!lines[i].flag){
            cnt = 1;
            lines[i].flag = true;
            x = lines[i].rightx;
            y = lines[i].righty;
            j = 0;
            while (j < n){
                if (!lines[j].flag && lines[j].leftx == x && lines[j].lefty == y){
                    lines[j].flag = true;
                    cnt++;
                    x = lines[j].rightx;
                    y = lines[j].righty;
                    j = 0;
                }else j++;
            }
            if (cnt > max){
                max = cnt;
                pointx = lines[i].leftx;
                pointy = lines[i].lefty;
            }
        }
    }
    printf("%d %d %d", max, pointx, pointy);
    return 0;
}