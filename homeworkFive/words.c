#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct TreeNode{
    char word[50];
    int times;
    struct TreeNode* left;
    struct TreeNode* right;
};
typedef struct TreeNode* Tree;
typedef struct TreeNode* Node;
Tree insert(Tree root, const char* word){
    if (root == NULL){
        root = malloc(sizeof(struct TreeNode));
        strcpy(root->word, word);
        root->times = 1;
        root->left = root->right = NULL;
        return root;
    }
    int cmp = strcmp(word, root->word);
    if (cmp == 0){
        root->times++;
    }
    else if (cmp < 0){
        root->left = insert(root->left, word);
    }
    else{
        root->right = insert(root->right, word);
    }
    return root;
}
void printAll(Tree words){
    if (words == NULL) return;
    printAll(words->left);
    printf("%s %d\n", words->word, words->times);
    printAll(words->right);
}
int main(){
    FILE* fr = fopen("article.txt", "r");
    Tree wordsTree = NULL;
    char word[50];
    int length = 0;
    char ch;
    while ((ch = fgetc(fr)) != EOF){
        if (isalpha(ch)){
            word[length++] = tolower(ch);
        }
        else if (length){
            word[length] = 0;
            wordsTree = insert(wordsTree, word);
            length = 0;
        }
    }
    Node node = wordsTree;
    int num = 0;
    while (node && num < 3){
        printf("%s ", node->word);
        num++;
        node = node->right;
    }
    putchar('\n');
    printAll(wordsTree);
}