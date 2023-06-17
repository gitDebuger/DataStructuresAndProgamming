#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct ListNode{
    int rank;
    struct ListNode* next;
};
typedef struct ListNode* Node;
typedef struct ListNode* List;
void addEdge(List* adjacentList, int v, int w){
    Node newCell = malloc(sizeof(struct ListNode));
    newCell->rank = w;
    if (adjacentList[v] == NULL){
        adjacentList[v] = newCell;
        newCell->next = NULL;
        return;
    }
    else if (newCell->rank < adjacentList[v]->rank){
        newCell->next = adjacentList[v];
        adjacentList[v] = newCell;
        return;
    }
    Node temp = adjacentList[v];
    while (temp->next && newCell->rank > temp->next->rank){
        temp = temp->next;
    }
    newCell->next = temp->next;
    temp->next = newCell;
}
void dfs(List* adjacentList, bool* flag, int* ans, int* pos, int curPoint){
    Node temp = adjacentList[curPoint];
    while (temp){
        if (!flag[temp->rank]){
            flag[temp->rank] = true;
            ans[(*pos)++] = temp->rank;
            dfs(adjacentList, flag, ans, pos, temp->rank);
        }
        temp = temp->next;
    }
}
void dfsCarry(List* adjacentList, int numVertex){
    bool flag[100] = {true};
    int ans[100] = {0};
    int position = 1;
    dfs(adjacentList, flag, ans, &position, 0);
    for (int i = 0; i < numVertex; i++){
        printf("%d ", ans[i]);
    }
    putchar('\n');
}
void bfs(List* adjacentList, int numVertex){
    bool flag[100] = {true};
    int ans[100] = {0};
    int queue[100];
    int pos = 1;
    int front = 0;
    int rare = 0;
    int curPoint;
    Node temp = adjacentList[0];
    while (temp){
        queue[rare++] = temp->rank;
        flag[temp->rank] = true;
        temp = temp->next;
    }
    while (front != rare){
        curPoint = queue[front++];
        ans[pos++] = curPoint;
        temp = adjacentList[curPoint];
        while (temp){
            if (!flag[temp->rank]){
                queue[rare++] = temp->rank;
                flag[temp->rank] = true;
            }
            temp = temp->next;
        }
    }
    for (int i = 0; i < numVertex; i++){
        printf("%d ", ans[i]);
    }
    putchar('\n');
}
void deletePoint(List* adjacentList, int point){
    Node temp = adjacentList[point];
    Node curNode;
    Node mid;
    while (temp){
        curNode = adjacentList[temp->rank];
        if (curNode->rank == point){
            adjacentList[temp->rank] = curNode->next;
            free(curNode);
            temp = temp->next;
            continue;
        }
        while (curNode->next){
            if (curNode->next->rank == point){
                mid = curNode->next;
                curNode->next = mid->next;
                free(mid);
                break;
            }
            curNode = curNode->next;
        }
        temp = temp->next;
    }
}
int main(){
    int edgeNum, vertexNum;
    scanf("%d%d", &vertexNum, &edgeNum);
    List* adjacentList = calloc(vertexNum, sizeof(List));
    int v, w;
    for (int i = 0; i < edgeNum; i++){
        scanf("%d%d", &v, &w);
        addEdge(adjacentList, v, w);
        addEdge(adjacentList, w, v);
    }
    int point;
    scanf("%d", &point);
    dfsCarry(adjacentList, vertexNum);
    bfs(adjacentList, vertexNum);
    deletePoint(adjacentList, point);
    dfsCarry(adjacentList, vertexNum - 1);
    bfs(adjacentList, vertexNum - 1);
    return 0;
}