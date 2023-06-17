#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define INFINITY 2147483647
#define NAME_LENGTH 15
#define STATION_NUM 320
struct STATION{
    char name[NAME_LENGTH];
    bool category;
};
struct ListNode{
    int adjaPoint;
    int lineRank;
    struct ListNode* next;
};
struct POINT{
    int dist;
    int path;
    bool flag;
};
typedef struct ListNode* List;
typedef struct ListNode* Node;
typedef struct STATION Station;
typedef struct POINT Point;
void addEdge(List* adjacentList, int left, int right, int line){
    Node newCell = malloc(sizeof(struct ListNode));
    newCell->adjaPoint = right;
    newCell->lineRank = line;
    if (adjacentList[left] == NULL){
        adjacentList[left] = newCell;
        newCell->next = NULL;
    }
    else{
        newCell->next = adjacentList[left];
        adjacentList[left] = newCell;
    }
}
int findPosition(Station* stations, int numAll, char* curStation){
    int pos;
    for (pos = 0; pos < numAll; pos++){
        if (strcmp(stations[pos].name, curStation) == 0){
            return pos;
        }
    }
    return numAll;
}
void findShortestPath(List* adjacentList, int start, int arrive, Point* ans){
    int* queue = malloc(STATION_NUM * sizeof(int));
    int front = 0;
    int rare = 0;
    queue[rare++] = start;
    ans[start].dist = 0;
    int v, w;
    Node temp;
    while (front != rare){
        v = queue[front++];
        ans[v].flag = true;
        temp = adjacentList[v];
        while (temp){
            w = temp->adjaPoint;
            if (ans[w].dist == INFINITY){
                ans[w].dist = ans[v].dist + 1;
                ans[w].path = v;
                queue[rare++] = w;
                if (w == arrive){
                    free(queue);
                    return;
                }
            }
            temp = temp->next;
        }
    }
}
int main(){
    FILE* subways = fopen("bgstations.txt", "r");
    Station stations[STATION_NUM];
    List adjacentList[STATION_NUM] = {NULL};
    int lineNum;
    int curLine;
    int stationNum;
    int cate;
    char stationName[NAME_LENGTH];
    int lastPosition, curPosition;
    int allStations = 0;
    fscanf(subways, "%d", &lineNum);
    int i, j;
    for (i = 0; i < lineNum; i++){
        fscanf(subways, "%d%d", &curLine, &stationNum);
        fscanf(subways, "%s%d", stationName, &cate);
        if (cate){
            lastPosition = findPosition(stations, allStations, stationName);
            if (lastPosition == allStations){
                stations[lastPosition].category = cate;
                strcpy(stations[lastPosition].name, stationName);
                allStations++;
            }
        }
        else{
            lastPosition = allStations++;
            stations[lastPosition].category = cate;
            strcpy(stations[lastPosition].name, stationName);
        }
        for (j = 1; j < stationNum; j++){
            fscanf(subways, "%s%d", stationName, &cate);
            if (cate){
                curPosition = findPosition(stations, allStations, stationName);
                if (curPosition == allStations){
                    stations[curPosition].category = cate;
                    strcpy(stations[curPosition].name, stationName);
                    allStations++;
                }
            }
            else{
                curPosition = allStations++;
                stations[curPosition].category = cate;
                strcpy(stations[curPosition].name, stationName);
            }
            addEdge(adjacentList, curPosition, lastPosition, curLine);
            addEdge(adjacentList, lastPosition, curPosition, curLine);
            lastPosition = curPosition;
        }
    }
    fclose(subways);
    char start[NAME_LENGTH];
    char destination[NAME_LENGTH];
    scanf("%s", start);
    scanf("%s", destination);
    int firstRank = 0;
    int lastRank = 0;
    for (i = 0; i < allStations; i++){
        if (strcmp(stations[i].name, start) == 0){
            firstRank = i;
            break;
        }
    }
    for (i = 0; i < allStations; i++){
        if (strcmp(stations[i].name, destination) == 0){
            lastRank = i;
            break;
        }
    }
    Point* ansList = malloc(STATION_NUM * sizeof(Point));
    for (i = 0; i < allStations; i++){
        ansList[i].dist = INFINITY;
        ansList[i].flag = false;
        ansList[i].path = -1;
    }
    findShortestPath(adjacentList, firstRank, lastRank, ansList);
    int path[STATION_NUM];
    int length = 0;
    int ptr = lastRank;
    while (ptr != firstRank){
        path[length++] = ptr;
        ptr = ansList[ptr].path;
    }
    path[length] = ptr;
    int num = 0;
    Node temp = NULL;
    printf("%s", start);
    temp = adjacentList[path[length]];
    while (temp->adjaPoint != path[length - 1]){
        temp = temp->next;
    }
    curLine = temp->lineRank;
    num++;
    for (i = length - 1; i > 0; i--){
        temp = adjacentList[path[i]];
        while (temp->adjaPoint != path[i - 1]){
            temp = temp->next;
        }
        if (temp->lineRank != curLine){
            printf("-%d(%d)-%s", curLine, num, stations[path[i]].name);
            curLine = temp->lineRank;
            num = 1;
        }
        else{
            num++;
        }
    }
    printf("-%d(%d)-%s", curLine, num, destination);
    free(ansList);
    return 0;
}