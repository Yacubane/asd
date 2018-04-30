/*
W ramach obchodów międzynarodowego święta cyklistów organizatorzy przewidzieli górską
wycieczkę rowerową. Będzie się ona odbywać po bardzo wąskiej ścieżce, na której rowery mogą
jechać tylko jeden za drugim. W ramach zapewnienia bezpieczeństwa każdy rowerzysta będzie
miał numer identyfikacyjny oraz małe urządzenie, przez które będzie mógł przekazać
identyfikator rowerzysty przed nim (lub -1 jeśli nie widzi przed sobą nikogo). Należy napisać
funkcję, która na wejściu otrzymuje informacje wysłane przez rowerzystów i oblicza rozmiar
najmniejszej grupy (organizatorzy obawiają się, że na małe grupy mogłyby napadać dzikie
zwierzęta). Dane są następujące struktury danych:
struct Cyclist {
int id, n id; // identyfikator rowerzysty oraz tego, którego widzi
};
Funkcja powinna mieć prototyp int smallestGroup( Cyclist cyclist[], int n ), gdzie
cyclist to tablica n rowerzystów. Funkcja powinna być możliwie jak najszybsza. Można założyć,
że identyfikatory rowerzystów to liczby z zakresu 0 do 108
(osiem cyfr napisanych w dwóch
rzędach na koszulce rowerzysty) i że pamięć nie jest ograniczona. Rowerzystów jest jednak dużo
mniej niż identyfikatorów (nie bez powodu boją się dzikich zwierząt). Należy zaimplementować
wszystkie potrzebne struktury danych.
 */
#include <iostream>

struct Cyclist {
    int id, n_id;
};
/**
 * Structure used in hash table, has one more field ^_^
 */
struct BetterCyclist {
    int id, n_id, p_id; //p_id = previous cyclist
};
/**
 * Structure of hash table
 */
struct HashTable{
    BetterCyclist** arr;
    int n; //size of hash table
};
/**
 * Creates hash from cyclist id
 * @param table - hash table
 * @param id - id of cyclist
 * @return hash
 */
int getHash(HashTable* table, int id){
    return (id)%table->n;
}
/**
 * Creates hash based on previous hash
 * @param table - hash table
 * @param hash - previous hash
 * @return hash
 */
int nextHash(HashTable* table, int hash){
    return (hash+1)%table->n;
}
/**
 * Inserts cyclist into hash table. Makes hash from cyclist.id
 * @param table - hashtable
 * @param cyclist - cyclist, which you want to be added
 */
void insert(HashTable* table, Cyclist cyclist){
    BetterCyclist* betterCyclist = new BetterCyclist;
    betterCyclist->id=cyclist.id;
    betterCyclist->n_id=cyclist.n_id;
    betterCyclist->p_id=-1; //-1 means there is no cyclist behind
    int hash = getHash(table,cyclist.id);
    while(table->arr[hash] != NULL){
        hash = nextHash(table,hash);
    }
    table->arr[hash]=betterCyclist;
}
/**
 * Searches for cyclist with given id
 * @param table - hashtable
 * @param id - id of cyclist
 * @return BetterCyclist or NULL if there is no cyclist with given id
 */
BetterCyclist* search(HashTable* table, int id){
    int hash = getHash(table,id);
    while(table->arr[hash] != NULL){
        if(table->arr[hash]->id==id) return table->arr[hash];
        hash = nextHash(table,hash);
    }
    return NULL;
}
int smallestGroup(Cyclist cyclist[], int n){
    HashTable* hashTable = new HashTable;
    hashTable->arr=new BetterCyclist*[2*n];
    hashTable->n=2*n;
    for(int i = 0; i < hashTable->n; i++){
        hashTable->arr[i]=NULL;
    }
    for(int i = 0; i < n; i++)
        insert(hashTable,cyclist[i]);
    for(int i = 0; i < n; i++)
        if(cyclist[i].n_id!=-1)
            //in this step we are going to search for next cyclist and
            //set him prevoious id as current iterating cyclist
            search(hashTable,cyclist[i].n_id)->p_id=cyclist[i].id;

    int minCounter=INT32_MAX;
    for(int i = 0; i < hashTable->n; i++)
        if(hashTable->arr[i]!=NULL && hashTable->arr[i]->p_id==-1){
            //we found cyclist which don't have any cyclist behind!
            //now let's count how many cyclist are in front of him
            int counter = 1;
            BetterCyclist* cyclist = hashTable->arr[i];
            while(cyclist->n_id!=-1){
                cyclist=search(hashTable,cyclist->n_id);
                counter++;
            }
            if(counter < minCounter) minCounter=counter;
        }
    return minCounter;
};
int main() {
    int n = 3;
    Cyclist cyclist[n];
    cyclist[0].id=0;
    cyclist[0].n_id=2137;
    cyclist[1].id=2137;
    cyclist[1].n_id=911;
    cyclist[2].id=911;
    cyclist[2].n_id=-1;
    cyclist[3].id=2;
    cyclist[3].n_id=-1;
    int result = smallestGroup(cyclist,n);
    std::cout << "Smallest group: " << result << std::endl;
    return 0;
}