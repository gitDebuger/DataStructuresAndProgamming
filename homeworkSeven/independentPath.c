#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct ListNode{
    int edgeRank;
    int adjaVertex;
    struct ListNode* next;
};
typedef struct ListNode* List;
typedef struct ListNode* Node;
void addEdge(List* adjacentList, int left, int right, int rank){
    Node newCell = malloc(sizeof(struct ListNode));
    newCell->adjaVertex = right;
    newCell->edgeRank = rank;
    if (adjacentList[left] == NULL){
        adjacentList[left] = newCell;
        newCell->next = NULL;
        return;
    }
    if (rank < adjacentList[left]->edgeRank){
        newCell->next = adjacentList[left];
        adjacentList[left] = newCell;
        return;
    }
    Node temp = adjacentList[left];
    while (temp->next && rank > temp->next->edgeRank){
        temp = temp->next;
    }
    newCell->next = temp->next;
    temp->next = newCell;
}
void dfs(List* adjacentList, int* path, int pos, int curPoint, int numVertex, bool* flag){
    if (curPoint == numVertex - 1){
        for (int i = 0; i < pos; i++){
            printf("%d ", path[i]);
        }
        putchar('\n');
        return;
    }
    Node temp = adjacentList[curPoint];
    while (temp){
        if (!flag[temp->adjaVertex]){
            flag[temp->adjaVertex] = true;
            path[pos] = temp->edgeRank;
            dfs(adjacentList, path, pos + 1, temp->adjaVertex, numVertex, flag);
            flag[temp->adjaVertex] = false;
        }
        temp = temp->next;
    }
}
void findPath(List* adjacentList, int numVertex, int numEdge){
    int* path = malloc(numEdge * sizeof(int));
    bool* flag = calloc(numVertex, sizeof(bool));
    flag[0] = true;
    dfs(adjacentList, path, 0, 0, numVertex, flag);
    free(path);
    free(flag);
}
int main(){
    int numVertex, numEdge;
    scanf("%d%d", &numVertex, &numEdge);
    List* adjacentList = calloc(numVertex, sizeof(List));
    int edge;
    int v, w;
    for (int i = 0; i < numEdge; i++){
        scanf("%d%d%d", &edge, &v, &w);
        addEdge(adjacentList, v, w, edge);
        addEdge(adjacentList, w, v, edge);
    }
    findPath(adjacentList, numVertex, numEdge);
    return 0;
}