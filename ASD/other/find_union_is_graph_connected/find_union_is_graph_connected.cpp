#include <iostream>
struct Edge{
    int e1;
    int e2;
    Edge* next;
};
struct Node{
    Node* parent;
    int val;
    int rank;
};
Node* MakeSet(int x){
    Node* p = new Node;
    p->parent=p;
    p->rank=0;
    p->val=x;
    return p;
}
Node* Find(Node* p){
    if(p->parent!=p)
        return p->parent=Find(p->parent);
    return p;
}
void Union(Node* x, Node* y){
    x=Find(x);
    y=Find(y);
    if(x==y)return;
    if(x->rank > y->rank){
        y->parent=x;
    }
    else {
        x->parent=y;
        if(x->rank==y->rank)
            y->rank++;
    }
}
void addEdge(Edge*& edge, int e1, int e2){
    Edge* newEdge = new Edge;
    newEdge->e1=e1;
    newEdge->e2=e2;
    newEdge->next=edge;
    edge=newEdge;
}
int main() {
    int MAX_EDGES=5;
    Edge* edges = NULL;
    addEdge(edges,0,1);
    addEdge(edges,1,2);
    addEdge(edges,2,3);
    addEdge(edges,3,4);

    Node** verticles = new Node*[MAX_EDGES];
    for(int i = 0; i < MAX_EDGES; i++){
        verticles[i]=MakeSet(i);
    }
    Edge* runner = edges;
    while(runner!=NULL){
        Union(verticles[runner->e1], verticles[runner->e2]);
        runner=runner->next;
    }
    bool isConnected=true;
    Node* firstParent = Find(verticles[0]);
    for(int i = 0; i < MAX_EDGES; i++){
        if(Find(verticles[i])!= firstParent)
            isConnected=false;
    }

    std::cout << "Is graph connected"  << isConnected << std::endl;
    return 0;
}