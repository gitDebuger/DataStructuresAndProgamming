#include <stdio.h>
#include <stdlib.h>
struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* medium;
    struct TreeNode* right;
};
typedef struct TreeNode* Tree;
typedef struct TreeNode* Node;
struct DOOR{
    int rank;
    int numOfPerson;
};
typedef struct DOOR Gate;
Tree initialize(){
    Tree root = malloc(sizeof(struct TreeNode));
    root->left = root->medium = root->right = NULL;
    root->val = 100;
    return root;
}
Node find(Tree root, int num){
    if (root == NULL) return root;
    if (root->val == num) return root;
    Node ans;
    ans = find(root->left, num);
    if (ans) return ans;
    ans = find(root->medium, num);
    if (ans) return ans;
    ans = find(root->right, num);
    return ans;
}
void insert(Tree root, int branch, int numA, int numB, int numC){
    Node fatherNode = find(root, branch);
    Node currentNode;
    fatherNode->left = malloc(sizeof(struct TreeNode));
    currentNode = fatherNode->left;
    currentNode->left = currentNode->medium = currentNode->right = NULL;
    currentNode->val = numA;
    if (numB){
        fatherNode->medium = malloc(sizeof(struct TreeNode));
        currentNode = fatherNode->medium;
        currentNode->left = currentNode->medium = currentNode->right = NULL;
        currentNode->val = numB;
    }
    if (numC){
        fatherNode->right = malloc(sizeof(struct TreeNode));
        currentNode = fatherNode->right;
        currentNode->left = currentNode->medium = currentNode->right = NULL;
        currentNode->val = numC;
    }
}
int cmp(const void* _a, const void* _b){
    Gate* gateA = (Gate*)_a;
    Gate* gateB = (Gate*)_b;
    if (gateA->numOfPerson == gateB->numOfPerson){
        return gateA->rank - gateB->rank;
    }
    return gateB->numOfPerson - gateA->numOfPerson;
}
int main(){
    int parent;
    int nums[3];
    int length;
    int number;
    Tree terminal = initialize();
    for (;;){
        scanf("%d", &parent);
        if (parent == -1) break;
        length = 0;
        for (;;){
            scanf("%d", &number);
            if (number == -1) break;
            nums[length++] = number;
        }
        if (length == 1) insert(terminal, parent, nums[0], 0, 0);
        else if (length == 2) insert(terminal, parent, nums[0], nums[1], 0);
        else insert(terminal, parent, nums[0], nums[1], nums[2]);
    }
    int front = 0;
    int rare = 0;
    int numOfGates = 0;
    int gates[100];
    Node queue[200];
    Node cur;
    Gate newRank[100];
    queue[rare++] = terminal;
    while (rare > front){
        cur = queue[front++];
        if (cur->val < 100){
            gates[numOfGates++] = cur->val;
        }
        if (cur->left) queue[rare++] = cur->left;
        if (cur->medium) queue[rare++] = cur->medium;
        if (cur->right) queue[rare++] = cur->right;
    }
    for (int i = 0; i < numOfGates; i++){
        scanf("%d %d", &newRank[i].rank, &newRank[i].numOfPerson);
    }
    qsort(newRank, numOfGates, sizeof(Gate), cmp);
    for (int i = 0; i < numOfGates; i++){
        printf("%d->%d\n", newRank[i].rank, gates[i]);
    }
    return 0;
}