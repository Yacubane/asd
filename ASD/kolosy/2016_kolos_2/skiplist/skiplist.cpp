/*
Dane są struktury danych opisujące SkipListę:
struct SLNode {
int value; // wartość przechowywana w węźle
int level; // poziom węzła
SLNode** next; // level-elementowa tablica wskaźników na następniki
};
struct SkipList {
SLNode* first; // wartownik przedni (pole value ma wartość -∞)
SLNode* last; // wartownik tylny (pole value ma wartość +∞)
};
const int MAX LEVEL = ... ; // maksymalny poziom węzłów
Proszę zaimplementować funkcję SkipList merge( SkipList A, SkipList B ), która scala
dwie otrzymane SkipListy (w efekcie powstaje nowa SkipLista składająca się z dokładnie tych
samych węzłów co poprzednie; nie należy zmieniać poziomów węzłów). Węzły wartowników mają
poziom MAX LEVEL. Funkcja powinna działać możliwie jak najszybciej. Proszę oszacować
złożoność czasową.
 */
#include <iostream>
#include <time.h>

const int MAX_LEVEL = 5;
struct SLNode {
    int value; // wartość przechowywana w węźle
    int level; // poziom węzła
    SLNode** next; // level-elementowa tablica wskaźników na następniki
};
struct SkipList {
    SLNode* first; // wartownik przedni (pole value ma wartość -∞)
    SLNode* last; // wartownik tylny (pole value ma wartość +∞)
    int height;
};
/**
 * Creates skiplist with selected height
 * @param height - height for new skiplist
 * @return new skiplist
 */
SkipList createSkiplist(int height){
    SkipList skipList;
    skipList.height=height;
    skipList.first=new SLNode;
    skipList.first->value=INT32_MIN;
    skipList.first->next=new SLNode*[height];
    skipList.last=new SLNode;
    skipList.last->value=INT32_MAX;
    skipList.last->next=new SLNode*[height];
    for(int i = 0; i < height; i++){
        skipList.first->next[i]=skipList.last;
        skipList.last->next[i]=NULL;
    }
    return skipList;
}
/**
 * Returns random height less than maximum height
 * @param maxHeight
 * @return random integer
 */
int getRandomHeight(int maxHeight){
    int h = 1;
    float p = 0.8;
    while (h < maxHeight && rand() / (RAND_MAX + 1.) < p) h++;
    return h;
}
/**
 * Creates node for skiplist
 * @param val - integer value
 * @param height - height of node
 * @return SLNode*
 */
SLNode* createNode(int val, int height){
    SLNode* node = new SLNode;
    node->value=val;
    node->level=height;
    node->next = new SLNode*[height];
    for(int i = 0; i < height; i++)
        node->next[i]=NULL;
    return node;
}
/**
 * Creates and inserts node to skiplist
 * @param skipList
 * @param val - integer value
 */
void insert(SkipList &skipList, int val){
    SLNode* toAdd = createNode(val, getRandomHeight(MAX_LEVEL));
    SLNode* pointers[toAdd->level];
    for(int i = 0; i < skipList.height; i++)
        pointers[i]=NULL;
    int level = skipList.height-1;
    SLNode* node = skipList.first;
    while(level>=0){
        if(node->next[level]->value > val){
            if(toAdd->level >= level)
                pointers[level]=node;
            level--;
        }
        else node=node->next[level];
    }
    for(int i = 0; i < toAdd->level; i++){
        toAdd->next[i]=pointers[i]->next[i];
        pointers[i]->next[i]=toAdd;
    }
}
/**
 * Searches for element in skiplist
 * @param skipList
 * @param val - value that you want to find
 * @return SLNode* or NULL
 */
SLNode* search(SkipList &skipList, int val){
    int level = skipList.height-1;
    SLNode* node = skipList.first;
    while(level>=0){
        if(node->next[level]->value >= val){
            level--;
        }
        else node=node->next[level];
    }
    if(node->next[0]->value==val) return node->next[0];
    return NULL;
}
/**
 * Prints every element of skiplist. In [] brackets prints height of every node
 * @param list - skiplist
 */
void printSkiplist(SkipList list) {
    SLNode* node = list.first;
    node=node->next[0];
    while(node!=list.last){
        std::cout << node->value << "[" << node->level << "]" <<",";
        node=node->next[0];
    }
    std::cout << std::endl;
}
/**
 * Merges two skiplists
 * @param A - skiplist 1
 * @param B - skiplist 2
 * @return merged SkipList
 */
SkipList merge(SkipList A, SkipList B){
    SkipList merged = createSkiplist(MAX_LEVEL);
    SLNode* pointers[MAX_LEVEL];
    for(int i = 0; i < MAX_LEVEL; i++)
        pointers[i]=merged.first;
    SLNode* list1 = A.first->next[0];
    SLNode* list2 = B.first->next[0];
    while(!(list1->value == INT32_MAX && list2->value == INT32_MAX)){
        SLNode* node;
        if(list1->value < list2->value){
            node = list1;
            list1=list1->next[0];
        }
        else {
            node = list2;
            list2=list2->next[0];
        }
        for(int i = 0; i < node->level; i++){
            node->next[i]=pointers[i]->next[i];
            pointers[i]->next[i]=node;
            pointers[i]=node;
        }
    }
    return merged;
}
int main() {
    srand(time(NULL));
    SkipList skiplist = createSkiplist(MAX_LEVEL);
    insert(skiplist,3);
    insert(skiplist,6);
    insert(skiplist,1);
    insert(skiplist,4);
    insert(skiplist,9);

    SkipList skiplist2 = createSkiplist(MAX_LEVEL);
    insert(skiplist2,0);
    insert(skiplist2,2);
    insert(skiplist2,8);
    insert(skiplist2,5);
    insert(skiplist2,7);

    printSkiplist(skiplist);
    printSkiplist(skiplist2);

    SkipList merged = merge(skiplist,skiplist2);
    printSkiplist(merged);

    for(int i = 0; i < 11; i++)
        std::cout << "FOUND " << i << "? " <<  (search(merged,i)!=NULL ? "YES" : "NO")  << std::endl;
    return 0;
}

