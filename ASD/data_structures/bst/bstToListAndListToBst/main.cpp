#include <iostream>
struct Node{
    int val;
    Node* left;
    Node* right;
};
void printInorder(Node* node){
    if(node==NULL) return;
    printInorder(node->left);
    std::cout << node->val << std::endl;
    printInorder(node->right);
}
Node* createNode(int val){
    Node* newNode = new Node;
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

void treeToDoubleLinkedList(Node* tree, Node*& lastNode){
    if(tree==NULL) return;
    treeToDoubleLinkedList(tree->left, lastNode);
    tree->left=lastNode;
    if(lastNode!=NULL) lastNode->right=tree;
    lastNode=tree;
    treeToDoubleLinkedList(tree->right, lastNode);
}
Node* doubleLinkedListToTree(Node*& node, int l, int p){
    if(l<=p){
        int m = (l+p)/2;
        Node* left=doubleLinkedListToTree(node,l,m-1);
        node->left=left;
        Node* tmp = node;
        node=node->right;
        tmp->right=doubleLinkedListToTree(node,m+1,p);
        return tmp;
    }
    return NULL;
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

    Node* node = NULL;
    treeToDoubleLinkedList(root,node);
    //now node is last element of list, let's make it first
    while(node->left!=NULL){
        node=node->left;
    }
    Node* root2 = doubleLinkedListToTree(node,0,6);
    printInorder(root2);
    return 0;
}