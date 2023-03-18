#include <stdio.h>
#include <stdbool.h>
struct FLAG
{
    bool leftDown;
    bool down;
    bool rightDown;
    bool right;
};
bool judgeLeftDown(int (*chesses)[19], int i, int j, struct FLAG (*flag)[19]){
    int chessman = chesses[i][j];
    int count;
    for (count = 1; count <= 3; count++){
        if (chesses[i+count][j-count] != chessman){
            break;
        }flag[i+count][j-count].leftDown = true;
    }if (count == 4){
        if (i <= 14 && j >= 4 && chesses[i+4][j-4] == 0){
            return true;
        }
        if (i >= 1 && j <= 17 && chesses[i-1][j+1] == 0){
            return true;
        }
    }
    return false;
}
bool judgeDown(int (*chesses)[19], int i, int j, struct FLAG (*flag)[19]){
    int chessman = chesses[i][j];
    int count;
    for (count = 1; count <= 3; count++){
        if (chesses[i+count][j] != chessman){
            break;
        }flag[i+count][j].down = true;
    }if (count == 4){
        if (i <= 14 && chesses[i+4][j] == 0){
            return true;
        }
        if (i >= 1 && chesses[i-1][j] == 0){
            return true;
        }
    }
    return false;
}
bool judgeRightDown(int (*chesses)[19], int i, int j, struct FLAG (*flag)[19]){
    int chessman = chesses[i][j];
    int count;
    if (i <= 15 && j <= 15 && !flag[i][j].rightDown){
        for (count = 1; count <= 3; count++){
            if (chesses[i+count][j+count] != chessman){
                break;
            }flag[i+count][j+count].rightDown = true;
        }if (count == 4){
            if (i <= 14 && j <= 14 && chesses[i+4][j+4] == 0){
                return true;
            }
            if (i >= 1 && j >= 1 && chesses[i-1][j-1] == 0){
                return true;
            }
        }
    }
    return false;
}
bool judgeRight(int (*chesses)[19], int i, int j, struct FLAG (*flag)[19]){
    int chessman = chesses[i][j];
    int count;
    if (j <= 15 && !flag[i][j].right){
        for (count = 1; count <= 3; count++){
            if (chesses[i][j+count] != chessman){
                break;
            }flag[i][j+count].right = true;
        }if (count == 4){
            if (j <= 14 && chesses[i][j+4] == 0){
                return true;
            }
            if (j >= 1 && chesses[i][j-1] == 0){
                return true;
            }
        }
    }
    return false;
}
bool judge(int (*chesses)[19], int i, int j, struct FLAG (*flag)[19]){
    bool res = false;
    if (i <= 15 && j >= 3 && !flag[i][j].leftDown){
        res = judgeLeftDown(chesses, i, j, flag);
        if (res) return true;
    }
    if (i <= 15 && !flag[i][j].down){
        res = judgeDown(chesses, i, j, flag);
        if (res) return true;
    }
    if (i <= 15 && j <= 15 && !flag[i][j].rightDown){
        res = judgeRightDown(chesses, i, j, flag);
        if (res) return true;
    }
    if (j <= 15 && !flag[i][j].right){
        res = judgeRight(chesses, i, j, flag);
        if (res) return true;
    }
    return false;
}
int main(){
    int chesses[19][19];
    struct FLAG flag[19][19] = {0};
    int i, j;
    for (i = 0; i < 19; i++){
        for (j = 0; j < 19; j++){
            scanf("%d", &chesses[i][j]);
        }
    }
    for (i = 0; i < 19; i++){
        for (j = 0; j < 19; j++){
            if (chesses[i][j] != 0 && judge(chesses, i, j, flag)){
                printf("%d:%d,%d\n", chesses[i][j], i+1, j+1);
                return 0;
            }
        }
    }
    printf("No\n");
    return 0;
}