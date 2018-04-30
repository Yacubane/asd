/*
Student chce wypuœciæ n ró¿nych pok´emonów (numerowanych od 0 do n - 1) z klatek
(pok´eball’i). Wypuszczony Pok´emon natychmiast atakuje swojego wybawiciela, chyba ¿e (a) jest
spokojny, lub (b) w okolicy znajduj¹ siê co najmniej dwa uwolnione pok´emony, na które ten
pok´emon poluje. Proszê zaimplementowaæ funkcjê:
int* releaseThemAll( HuntingList* list, int n ),
gdzie list to lista z informacj¹, które pok´emony poluj¹ na które (lista nie zawiera powtórzeñ):
struct HuntingList {
HuntingList* next; // nastêpny element listy
int predator; // numer pokemona, który poluje
int prey; } // numer pokemona, na którego poluje
Funkcja powinna zwróciæ n elementow¹ tablicê z numerami pok´emonów w kolejnoœci
wypuszczania (tak, ¿eby wypuszczaj¹cy nie zosta³ zaatakowany) lub NULL jeœli taka kolejnoœæ nie
istnieje. Ka¿dy wypuszczony pok´emon zostaje ”w okolicy”. Jeœli pok´emon nie wystêpuje na liœcie
jako predator to znaczy, ¿e jest spokojny. Zaimplementowana funkcja powinna byæ mo¿liwie jak
najszybsza. Proszê krótko oszacowaæ jej z³o¿onoœæ.
*/
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
/**
 * Inserts predator to the list of predators of prey
 * @param prey
 * @param predator
 */
void insertPredator(Pokemon* prey, Pokemon* predator){
    PokemonNode* node = new PokemonNode;
    node->next=prey->predators;
    node->pokemon=predator;
    prey->predators=node;
}
/**
 * Unleashes pokemon, decrements remaingingPreys counter
 * in every predator of pokemon and if remaingingPreys<=0
 * recursively unleashes this predator.
 * What's more, it adds id of pokemon to queue
 * @param pokemon
 * @param queue
 */
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
    //Make array of pokemons
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
    //now insert predators to every pokemon
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
        //if pokemon is safe and isn't outside already, then unleash him
        if(pokemons[i]->predatorCounter==0 &&
                !pokemons[i]->outside){
            unleashPokemon(pokemons[i],queue);
        }

    }
    //if queue counter isn't n then don't return (not all pokemons are outside)
    //queue counter is incremented in unleashPokemon function
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
