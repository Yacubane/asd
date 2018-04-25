#include <iostream>
using namespace std;
/**
 * Structure used in heap and tree
 */
struct Node{
    char letter;
    int value; //used to save frequency of character
    Node* left;
    Node* right;
};
void swap(Node* arr[], int i, int j){
    Node* tmp = arr[i];
    arr[i]=arr[j];
    arr[j]=tmp;
}
int leftChild(int index){
    return index*2;
}
int rightChild(int index){
    return index*2 + 1;
}
/**
 * Heapifies min-heap
 * @param arr - heap array
 * @param index - index which needs to be repaired
 */
void heapify(Node* arr[], int index){
    int size = arr[0]->value;
    int smallest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    if(left <= size && arr[left]->value < arr[smallest]->value) smallest=left;
    if(right <= size && arr[right]->value < arr[smallest]->value) smallest=right;
    if(smallest != index){
        swap(arr, smallest, index);
        heapify(arr,smallest);
    }
}
/**
 * Builds heap from array
 * @param arr - array
 */
void buildHeap(Node* arr[]){
    int n = arr[0]->value;
    for(int i = (n)/2; i>=1; i--){
        heapify(arr,i);
    }
}
/**
 * Creates heap structure from characters and frequencies. First element has value of size.
 * @return array used for heap
 */
Node** createNodeArray(char letters[], int freq[], int n){
    int size = n+1; //size of heap = size of letters + one node with size
    Node** arr = new Node*[size];
    arr[0]=new Node;
    arr[0]->value=size-1;
    for(int i = 1; i < size; i++){
        arr[i]=new Node;
        arr[i]->left=NULL;
        arr[i]->right=NULL;
        arr[i]->letter=letters[i-1];
        arr[i]->value=freq[i-1];
    }
    return arr;
}
/**
 * Builds huffman tree
 * @param arr - heap array
 * @return - root node of Huffman tree
 */
Node* buildHuffmanTree(Node* arr[]){
    while(arr[0]->value>1){
        Node* node1 = arr[1];
        swap(arr,1,arr[0]->value); //replace first and last element of array
        arr[0]->value--; //heap size changed
        heapify(arr,1);
        Node* node2 = arr[1];
        Node* combined = new Node;
        combined->value=node1->value+node2->value;
        combined->letter=' '; //this is huffman blank node
        arr[1]=combined; //place huffman blank node on heap and heapify it
        heapify(arr,1);
        combined->left=node1;
        combined->right=node2;
    }
    return arr[1];
}
/**
 * Prints huffman tree codings recursively
 * @param root - Huffman tree root
 * @param code - pass "" value at start
 */
void printHuffmanTree(Node* root, string code){
    if(root->left == NULL && root->right==NULL){
        cout << root->letter << " - " << code << endl;
    }
    else {
        printHuffmanTree(root->left,code+"0");
        printHuffmanTree(root->right,code+"1");
    }
}
/**
 * Decodes text compressed with Huffman algorithm
 * @param huffmanTree - root of Huffman Tree
 * @param text - text with zeros and ones to be decoded
 * @return string with decoded text
 */
string decodeText(Node* huffmanTree, string text){
    string finalText;
    Node* traverse = huffmanTree;
    int textIterator = 0;
    while(textIterator < text.length()){
        if(text[textIterator] == '0') traverse = traverse->left;
        if(text[textIterator] == '1') traverse = traverse->right;
        if(traverse->left == NULL && traverse->right==NULL){
            finalText+=traverse->letter;
            traverse=huffmanTree;
        }
        textIterator++;
    }
    return finalText;
}
int main() {
    //example letters and frequencies
    char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] =     { 5, 9, 12, 13, 16, 45 };
    Node** arr = createNodeArray(letters,freq,6);
    buildHeap(arr);
    Node* huffmanTree = buildHuffmanTree(arr);
    printHuffmanTree(huffmanTree,"");
    //"111 0 100 101 1100 1101" is efcdab
    cout << decodeText(huffmanTree,"111010010111001101") << endl;
    return 0;
}