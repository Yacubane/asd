/*
 Proszę opisać (bez implementacji) algorytm, który otrzymuje na wejściu pewne drzewo BST T
i tworzy nowe drzewo BST T, które spełnia następujące warunki: (a) T zawiera dokładnie te
same wartości co T, oraz (b) drzewo T jest drzewem czerwono-czarnym (w związku z tym
powinno zawierać kolory węzłów).
 */
#include <iostream>
enum Color{
    BLACK,
    RED,
    NONE
};
struct Node{
    int val;
    Node* left;
    Node* right;
    Color color;
};
void printInorder(Node* node){
    if(node==NULL) return;
    printInorder(node->left);
    std::cout << node->val << ((node->color!=NONE) ? (node->color==BLACK ? "BLACK" : "RED") : " ") << std::endl;
    printInorder(node->right);
}
Node* createNode(int val){
    Node* newNode = new Node;
    newNode->color=NONE;
    newNode->val=val;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
Node* insert(Node* tree, Node* newNode){
    if(tree==NULL) return newNode;
    if(newNode->val > tree->val) {
        tree->right=insert(tree->right,newNode);
        return tree;
    }
    else {
        tree->left=insert(tree->left,newNode);
        return tree;
    }
}
void getTreeSize(Node* node, int &size){
    if(node==NULL) return;
    getTreeSize(node->left, size);
    size++;
    getTreeSize(node->right, size);
}
int getTreeMaxHeight(Node* node){
    if(node==NULL) return 0;
    int h1 = getTreeMaxHeight(node->left);
    int h2 = getTreeMaxHeight(node->right);
    return (h1 > h2 ? h1 : h2)+1;
}
void colorizeHeight(Node* node, int currentDepth, int colorizeDepth){
    if(node==NULL) return;
    currentDepth++;
    if(currentDepth==colorizeDepth)
        node->color=RED;
    else
        node->color=BLACK;
    colorizeHeight(node->left,currentDepth,colorizeDepth);
    colorizeHeight(node->right,currentDepth,colorizeDepth);
}
void treeToArray(Node* node, int arr[], int &i){
    if(node==NULL) return;
    treeToArray(node->left, arr,i);
    arr[i++]=node->val;
    treeToArray(node->right, arr,i);
}
Node* arrayToTree(int arr[], int l, int p){
    if(l<=p){
        int m = (l+p)/2;
        Node* node = createNode(arr[m]);
        node->left=arrayToTree(arr,l,m-1);
        node->right=arrayToTree(arr,m+1,p);
        return node;
    }
    return NULL;
}
Node* copyTree(Node* tree){
    int size = 0;
    getTreeSize(tree,size);
    int arr[size];
    int i = 0;
    treeToArray(tree,arr,i);
    Node* newTree = arrayToTree(arr,0,size-1);
    return newTree;
}
void colorizeBalancedTree(Node* tree){
    int maxHeight = getTreeMaxHeight(tree);
    colorizeHeight(tree,0,maxHeight);
}
int main() {
    Node* root = new Node;
    root->val=5;
    root->left=NULL;
    root->right=NULL;
    insert(root,createNode(3));
    insert(root,createNode(7));
    insert(root,createNode(2));
    insert(root,createNode(4));
    insert(root,createNode(6));
    insert(root,createNode(8));

    Node* copiedTree = copyTree(root);

    printInorder(copiedTree);
    colorizeBalancedTree(copiedTree);
    printInorder(copiedTree);

    std::cout << getTreeMaxHeight(copiedTree) << std::endl;
    return 0;
}