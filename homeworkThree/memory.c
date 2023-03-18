#include <stdio.h>
#include <stdlib.h>
struct MemoryBlock{
    int address;
    int space;
    struct MemoryBlock* next;
};
typedef struct MemoryBlock* memoryList;
typedef struct MemoryBlock* block;
int main(){
    memoryList list = NULL;
    block curPos = NULL;
    int blockCounts;
    scanf("%d", &blockCounts);
    list = malloc(sizeof(struct MemoryBlock));
    scanf("%d %d", &list->address, &list->space);
    curPos = list;
    for (int i = 1; i < blockCounts; i++){
        curPos->next = malloc(sizeof(struct MemoryBlock));
        curPos = curPos->next;
        scanf("%d %d", &curPos->address, &curPos->space);
    }
    curPos->next = list;

    int spaceAlloc;
    block preCurPos = curPos;
    curPos = curPos->next;
    block tempBlock;
    block mostSuitablePreCurPos;
    while (scanf("%d", &spaceAlloc)){
        if (spaceAlloc == -1){
            break;
        }
        if (curPos == NULL){
            continue;
        }
        if (preCurPos == curPos){
            if (curPos->space == spaceAlloc){
                free(curPos);
                preCurPos = curPos = NULL;
            }else if (curPos->space > spaceAlloc){
                curPos->space -= spaceAlloc;
            }
        }
        else{
            for (tempBlock = preCurPos;
            tempBlock->next != preCurPos && tempBlock->next->space < spaceAlloc;
            tempBlock = tempBlock->next);

            if (tempBlock->next == preCurPos){
                if (preCurPos->space == spaceAlloc){
                    free(preCurPos);
                    tempBlock->next = curPos;
                    preCurPos = tempBlock;
                }else if (preCurPos->space > spaceAlloc){
                    preCurPos->space -= spaceAlloc;
                    curPos = preCurPos;
                    preCurPos = tempBlock;
                }
            }
            else{
                mostSuitablePreCurPos = tempBlock;
                tempBlock = tempBlock->next;
                while (tempBlock != preCurPos){
                    if (tempBlock->next->space >= spaceAlloc && 
                    tempBlock->next->space < mostSuitablePreCurPos->next->space){
                        mostSuitablePreCurPos = tempBlock;
                    }
                    tempBlock = tempBlock->next;
                }
                if (mostSuitablePreCurPos->next->space == spaceAlloc){
                    tempBlock = mostSuitablePreCurPos->next;
                    mostSuitablePreCurPos->next = tempBlock->next;
                    free(tempBlock);
                    curPos = mostSuitablePreCurPos->next;
                    preCurPos = mostSuitablePreCurPos;
                }else{
                    mostSuitablePreCurPos->next->space -= spaceAlloc;
                    curPos = mostSuitablePreCurPos->next;
                    preCurPos = mostSuitablePreCurPos;
                }
            }
        }
    }
    if (curPos == NULL) return 0;
    for (tempBlock = curPos; tempBlock->next != curPos; tempBlock = tempBlock->next){
        printf("%d %d\n", tempBlock->address, tempBlock->space);
    }printf("%d %d", tempBlock->address, tempBlock->space);
    return 0;
}