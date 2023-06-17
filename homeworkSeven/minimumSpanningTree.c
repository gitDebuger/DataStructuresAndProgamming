#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INT_MAX 2147483647
struct ListNode{
    int edgeID;
    int weight;
    int adjaVertex;
    struct ListNode* next;
};
struct Point{
    bool flag;
    int dv;
};
typedef struct ListNode* List;
typedef struct ListNode* Node;
int MIN(int a, int b){
    if (a > b) return b;
    return a;
}
void addEdge(List* adjacentList, int left, int right, int id, int cost){
    Node newCell = malloc(sizeof(struct ListNode));
    newCell->adjaVertex = right;
    newCell->edgeID = id;
    newCell->weight = cost;
    if (adjacentList[left] == NULL){
        adjacentList[left] = newCell;
        newCell->next = NULL;
        return;
    }
    if (right < adjacentList[left]->adjaVertex){
        newCell->next = adjacentList[left];
        adjacentList[left] = newCell;
        return;
    }
    Node temp = adjacentList[left];
    while (temp->next && right > temp->next->adjaVertex){
        temp = temp->next;
    }
    newCell->next = temp->next;
    temp->next = newCell;
}
int cmp(const void* _a, const void* _b){
    return *((int*)_a) - *((int*)_b);
}
void Prim(List* adjacentList, int numVertex){
    struct Point* vertexes = malloc(numVertex * sizeof(struct Point));
    for (int i = 0; i < numVertex; i++){
        vertexes[i].flag = false;
        vertexes[i].dv = INT_MAX;
    }
    int* edges = malloc((numVertex - 1) * sizeof(int));
    int pos = 0;
    Node minimum;
    Node temp;

    vertexes[0].flag = true;
    vertexes[0].dv = 0;
    temp = adjacentList[0];
    while (temp){
        vertexes[temp->adjaVertex].dv = temp->weight;
        temp = temp->next;
    }
    
    int minLen;
    for (int i = 1; i < numVertex; i++){
        minLen = INT_MAX;
        for (int j = 0; j < numVertex; j++){
            if (vertexes[j].flag == false) continue;
            temp = adjacentList[j];
            while (temp){
                if (vertexes[temp->adjaVertex].flag == false && temp->weight < minLen){
                    minimum = temp;
                    minLen = temp->weight;
                }
                temp = temp->next;
            }
        }
        edges[pos++] = minimum->edgeID;
        vertexes[minimum->adjaVertex].flag = true;
        temp = adjacentList[minimum->adjaVertex];
        while (temp){
            if (vertexes[temp->adjaVertex].flag == false){
                vertexes[temp->adjaVertex].dv = MIN(vertexes[temp->adjaVertex].dv, temp->weight);
            }
            temp = temp->next;
        }
    }
    int totalCost = 0;
    for (int i = 0; i < numVertex; i++){
        totalCost += vertexes[i].dv;
    }
    printf("%d\n", totalCost);
    qsort(edges, numVertex - 1, sizeof(int), cmp);
    for (int i = 0; i < numVertex - 1; i++){
        printf("%d ", edges[i]);
    }
    free(vertexes);
    free(edges);
}
int main(){
    int numVertex, numEdge;
    scanf("%d%d", &numVertex, &numEdge);
    List* adjacentList = calloc(numVertex, sizeof(List));
    int v, w;
    int cost;
    int id;
    for (int i = 0; i < numEdge; i++){
        scanf("%d%d%d%d", &id, &v, &w, &cost);
        addEdge(adjacentList, v, w, id, cost);
        addEdge(adjacentList, w, v, id, cost);
    }
    Prim(adjacentList, numVertex);
    return 0;
}