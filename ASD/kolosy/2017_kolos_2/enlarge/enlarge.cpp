#include <iostream>
struct HT{
    int* table;
    int size;
};
int hash(int x){
    return x;
}
void enlarge(HT* ht){
    int newSize = ht->size*2;
    int* newTable = new int[ht->size*2];
    for(int i = 0; i < newSize; i++)
        newTable[i]=-1;
    //przepisywanie tylko doskonaych
    for(int i = 0; i < ht->size; i++){
        if(ht->table[i]!=-1){
            int hashVal = hash(ht->table[i]) % newSize;
            if(newTable[hashVal] == -1){
                newTable[hashVal]=ht->table[i];
                ht->table[i]=-1;
            }
        }
    }
    //przepisywanie reszty
    for(int i = 0; i < ht->size; i++) {
        if (ht->table[i] != -1) {
            int hashVal = hash(ht->table[i]) % newSize;
            while(newTable[hashVal] != -1){
                hashVal = (hashVal+1) % newSize;
            }
            newTable[hashVal]=ht->table[i];
            ht->table[i]=-1;
        }
    }
    delete ht->table;
    ht->table=newTable;
    ht->size=newSize;
}
void insert(HT* ht, int val){
    int hashVal = hash(val) % ht->size;
    while(ht->table[hashVal] != -1){
        hashVal = (hashVal+1) % ht->size;
    }
    ht->table[hashVal]=val;
}
HT* createHT(int size){
    HT* ht = new HT;
    ht->size=size;
    ht->table=new int[ht->size];
    for(int i = 0; i < ht->size; i++)
        ht->table[i]=-1;
    return ht;
}
int main() {
    HT* ht = createHT(10);
    insert(ht,5);
    insert(ht,15);
    insert(ht,3);
    insert(ht,9);

    for(int i = 0; i < ht->size; i++)
        std::cout << "RECORD " << i << " = " << ht->table[i] << std::endl;

    enlarge(ht);
    std::cout << "Enlarged" << std::endl;

    for(int i = 0; i < ht->size; i++)
        std::cout << "RECORD " << i << " = " << ht->table[i] << std::endl;

    return 0;
}