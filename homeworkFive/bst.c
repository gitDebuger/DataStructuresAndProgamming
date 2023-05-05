#include <stdio.h>
#include <stdlib.h>
struct treeNode{
    int val;
    int height;
    struct treeNode* left;
    struct treeNode* right;
};
struct treeNode* insert(struct treeNode* root, int val, int curHeight){
    if (root == NULL){
        root = malloc(sizeof(struct treeNode));
        root->height = curHeight + 1;
        root->left = root->right = NULL;
        root->val = val;
        return root;
    }
    if (val >= root->val){
        root->right = insert(root->right, val, root->height);
    }
    else{
        root->left = insert(root->left, val, root->height);
    }
    return root;
}
void printLeaves(struct treeNode* root){
    if (root == NULL) return;
    if (root->left == NULL && root->right == NULL){
        printf("%d %d\n", root->val, root->height);
    }
    printLeaves(root->left);
    printLeaves(root->right);
}
void ldr(struct treeNode* root){
    if (root == NULL) return;
    ldr(root->left);
    printf("%d ", root->val);
    ldr(root->right);
}
int main(){
    int num;
    int cur;
    struct treeNode* tree = NULL;
    scanf("%d", &num);
    for (int i = 0; i < num; i++){
        scanf("%d", &cur);
        tree = insert(tree, cur, 0);
    }
    printLeaves(tree);
}