#include <iostream>
struct Node{
    int intervalMin;
    int intervalMax;
    int heightWholeInterval;
    int maxHeightInside;
    Node* left;
    Node* right;
    Node* parent;
};
/**
 * Creates interval tree with n intervals
 * @param n - number of intervals
 * @return root of tree
 */
int getSmallestHigherPowerOf2(int n){
    int power = 1;
    while(power<n){
        power*=2;
    }
    return power;
}

Node* createIntervalTree(int n){
    int size = getSmallestHigherPowerOf2(n);
    Node** arr = new Node*[size*2];
    for(int i = 0; i < size*2; i++){
        arr[i]=NULL;
    }
    int intervalSize=1;
    while(size>0){
        for(int i = 0; i < size; i++) {
            Node* node =new Node;
            node->heightWholeInterval=0;
            node->maxHeightInside=0;
            node->parent=NULL;
            node->left=arr[i*2];
            node->right=arr[(i*2)+1];
            if(node->left!=NULL)
                node->left->parent=node;
            if(node->right!=NULL)
                node->right->parent=node;
            node->intervalMin=i*intervalSize;
            node->intervalMax=(i+1)*intervalSize - 1;
            arr[i]=node;
        }
        size/=2;
        intervalSize*=2;
    }
    Node* root = arr[0];
    delete arr;
    return root;

}
void inorder(Node* root){
    if(root==NULL) return;
    inorder(root->left);
    std::cout << "IO: " << root->intervalMin << " " << root->intervalMax << std::endl;
    inorder(root->right);
}
void getIntervals(Node* root, int min, int max, Node** array, int &i, int&max_height){
    if(root->heightWholeInterval>max_height)
        max_height=root->heightWholeInterval;

    if(root->intervalMin==min && root->intervalMax==max){
        if(root->maxHeightInside>max_height)
            max_height=root->maxHeightInside;
        array[i++]=root;
        return;
    }
    int leftCenter = (root->intervalMin+root->intervalMax)/2;
    int rightCenter = leftCenter+1;
    if(min > leftCenter){
        getIntervals(root->right, min, max,array,i,max_height);
    }
    else if(max < rightCenter){
        getIntervals(root->left, min, max,array,i,max_height);
    }
    else {
        getIntervals(root->left,min,leftCenter,array,i,max_height);
        getIntervals(root->right,rightCenter,max,array,i,max_height);
    }
}

void pushBlock(Node* tree, Node** tmpArr, int min, int max){
    int elements = 0;
    int maxHeight = 0;
    getIntervals(tree,min,max,tmpArr,elements,maxHeight);
    for(int i = 0; i < elements; i++){
        Node* node = tmpArr[i];
        node->heightWholeInterval=maxHeight+1;
        node=node->parent;
        while(node!=NULL){
            if(node->maxHeightInside < (maxHeight+1))
                node->maxHeightInside=maxHeight+1;
            node=node->parent;
        }
    }
}
int main() {
    int n = 10;
    Node* tree = createIntervalTree(n);
    //inorder(tree);
    Node** array = new Node*[n];
    pushBlock(tree,array,1,3);
    pushBlock(tree,array,2,5);
    pushBlock(tree,array,0,3);
    pushBlock(tree,array,8,9);
    pushBlock(tree,array,4,6);

    std::cout << tree->maxHeightInside << std::endl;
    return 0;
}