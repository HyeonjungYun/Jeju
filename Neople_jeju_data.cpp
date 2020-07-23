#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int Tree;
typedef struct _tagTNode {
    Tree data;    
    struct _tagTNode* left;
    struct _tagTNode* right;
}TREENODE;

TREENODE* makeTreeNode(void) {
    TREENODE* brch = (TREENODE*)malloc(sizeof(TREENODE));

    brch->left = NULL;
    brch->right = NULL;
    return brch;
}

Tree getData(TREENODE* brch) {
    return brch->data;
}

void setData(TREENODE* brch, Tree data) {
    brch->data = data;
}

TREENODE* getLeftTree(TREENODE* brch) {
    return brch->left;
}

TREENODE* getRightTree(TREENODE* brch) {
    return brch->right;
}

void makeLeftTree(TREENODE* main, TREENODE* data) {
    if (main->left != NULL) {
        free(main->left);
    }

    main->left = data;
}

void makeRightTree(TREENODE* main, TREENODE* data) {
    if (main->right != NULL) {
        free(main->right);
    }

    main->right = data;
}

TREENODE* makeTreeNode(void);
Tree getData(TREENODE* brch);
void setData(TREENODE* brch, Tree data);
TREENODE* getLeftTree(TREENODE* brch);
TREENODE* getRightTree(TREENODE* brch);
void makeLeftTree(TREENODE* main, TREENODE* data);
void makeRightTree(TREENODE* main, TREENODE* data);

int main() {

    TREENODE* brch1 = makeTreeNode(); TREENODE* brch2 = makeTreeNode();
    TREENODE* brch3 = makeTreeNode(); TREENODE* brch4 = makeTreeNode();
    TREENODE* brch5 = makeTreeNode(); TREENODE* brch6 = makeTreeNode();
    TREENODE* brch7 = makeTreeNode();

    setData(brch1, 1); setData(brch2, 2);
    setData(brch3, 3); setData(brch4, 4);
    setData(brch5, 5); setData(brch6, 6);
    setData(brch7, 7);

    makeLeftTree(brch1, brch2); makeRightTree(brch1, brch3);
    makeLeftTree(brch2, brch4); makeRightTree(brch2, brch5);
    makeLeftTree(brch3, brch6); makeRightTree(brch3, brch7);

    cout << getData(getLeftTree(brch1)) << "\n";
    cout << getData(getRightTree(brch1)) << "\n";
    cout << getData(getLeftTree(getLeftTree(brch1))) << "\n";
    cout << getData(getRightTree((getLeftTree(brch1)))) << "\n";
    cout << getData(getLeftTree((getRightTree(brch1)))) << "\n";
    cout << getData(getRightTree((getRightTree(brch1)))) << "\n";

    return 0;
}