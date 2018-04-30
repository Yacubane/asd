#include <iostream>
struct HuntingList {
    HuntingList* next;
    int predator;
    int prey;
} ;

struct PokemonNode;
struct Pokemon{
    bool outside; //did pokemon leave?
    PokemonNode* predators; //list of predators hunting this pokemon
    int predatorCounter; //on how many pokemons this pokemon hunt
    int remainingPreys; //how many preys there is needed to release pokemon
    int id;
};
struct PokemonNode{
    Pokemon* pokemon;
    PokemonNode* next;
};

struct Queue{
    int *arr;
    int counter;
};

void insertPredator(Pokemon* prey, Pokemon* predator){
    PokemonNode* node = new PokemonNode;
    node->next=prey->predators;
    node->pokemon=predator;
    prey->predators=node;
}

void unleashPokemon(Pokemon* pokemon, Queue* queue){
    pokemon->outside=true;
    queue->arr[queue->counter++]=pokemon->id;
    PokemonNode* predator = pokemon->predators;
    while(predator!=NULL){
        if(!predator->pokemon->outside){
            predator->pokemon->remainingPreys--;
            if(predator->pokemon->remainingPreys<=0)
                unleashPokemon(predator->pokemon,queue);
        }
        predator=predator->next;
    }
}
int* releaseThemAll(HuntingList* list, int n){
    Pokemon** pokemons = new Pokemon*[n];
    for(int i = 0; i < n; i++){
        Pokemon* pokemon = new Pokemon;
        pokemon->predatorCounter=0;
        pokemon->outside=false;
        pokemon->remainingPreys=2;
        pokemon->predators=NULL;
        pokemon->id=i;
        pokemons[i]=pokemon;
    }
    HuntingList* node=list;
    while(node!=NULL){
        Pokemon* predator = pokemons[node->predator];
        Pokemon* prey = pokemons[node->prey];
        predator->predatorCounter++;
        insertPredator(prey,predator);
        node = node->next;
    }
    Queue* queue = new Queue;
    queue->arr=new int[n];
    queue->counter=0;
    for(int i = 0; i < n; i++){
        if(pokemons[i]->predatorCounter==0 &&
                !pokemons[i]->outside){
            unleashPokemon(pokemons[i],queue);
        }

    }
    if(queue->counter==n)return queue->arr;
    return NULL;
}
void addToHuntingList(HuntingList*& list, int predator, int prey){
    HuntingList* node = new HuntingList;
    node->prey=prey;
    node->predator=predator;
    node->next=list;
    list=node;
}
int main() {
    int n = 4;
    HuntingList* huntingList = NULL;
    addToHuntingList(huntingList,0,1);
    addToHuntingList(huntingList,0,2);
    addToHuntingList(huntingList,2,1);
    addToHuntingList(huntingList,2,3);

    int* queue = releaseThemAll(huntingList,n);
    if(queue==NULL){
        std::cout << "Nie da sie wypuscic pokemonow ;(" << std::endl;
    }
    else {
        std::cout << "Kolejnosc: " << std::endl;
        for(int i = 0; i < n; i++){
            std::cout <<  queue[i] <<",";
        }
    }
    return 0;
}