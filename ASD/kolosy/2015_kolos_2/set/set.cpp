/*
Pewna firma przechowuje dużo iczb pierwszych w postaci binarnej jako stringi ”10101...”.
Zaimplementuj strukturę danych Set do przechowywania tych danych. Napisz funkcje:
Set createSet( string A[], int n ), która tworzy Set z n-elementowej tablicy stringów
oraz bool contains( Set a, string s ), która sprawdza czy dana liczba jest w Secie.
Oszacuj złożoność czasową i pamięciową powyższych funkcji.
 */
#include <iostream>
using namespace std;
struct Set{
    string** numbers;
    int size;
};
uint32_t getHash(Set &set, string* s){
    uint32_t result = 0;
    for(int i = 0; i < s->length(); i+=32){
        uint32_t oneInteger = 0;
        uint32_t powerOf2 = 1;
        for(int j = 0; j < 32; j++){
            int index = i+j;
            if(index < s->length() && (*s)[index]=='1')
                oneInteger+=powerOf2;
            powerOf2*=2;
        }
        result^=oneInteger;

    }
    return result%set.size;
}
uint32_t nextHash(Set &set, uint32_t hash){
    return (hash+1)%set.size;
}
void insert(Set &set, string* s){
    int hash = getHash(set,s);
    while(set.numbers[hash]!=NULL){
        hash=nextHash(set,hash);
    }
    set.numbers[hash]=s;
}

Set createSet(string A[], int n){
    Set set;
    set.size=2*n;
    set.numbers=new string*[set.size];
    for(int i = 0; i < set.size; i++)
        set.numbers[i]=NULL;
    for(int i = 0; i < n; i++)
        insert(set, &A[i]);
    return set;
}
bool contains(Set a, string s){
    int hash = getHash(a,&s);
    while(a.numbers[hash]!=NULL){
        if(*a.numbers[hash]==s)
            return true;
        hash=nextHash(a,hash);
    }
    return false;
}
int main() {
    int n = 10;
    string strings[n];
    strings[0]="1001010100010010101";
    strings[1]="101111011111111111101010101";
    strings[2]="1000000000011111111111111";
    strings[3]="100111001000101010001001110";
    strings[4]="11001111001001010110011001001110101";

    Set set = createSet(strings,n);

    std::cout << "Zawiera? " << contains(set,"1001010100010010101") << std::endl;
    std::cout << "Zawiera? " << contains(set,"101111011111111111101010101") << std::endl;
    std::cout << "Zawiera? " << contains(set,"1000000000011111111111111") << std::endl;
    std::cout << "Zawiera? " << contains(set,"100111001000101010001001110") << std::endl;
    std::cout << "Zawiera? " << contains(set,"11001111001001010110011001001110101") << std::endl;
    std::cout << "Zawiera? " << contains(set,"1100111100100101010001100100111010") << std::endl;

    return 0;
}