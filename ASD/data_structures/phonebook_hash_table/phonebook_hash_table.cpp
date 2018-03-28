#include <iostream>
#include <string.h>
using namespace std;
const uint32_t KEY_SIZE = 32; //key size in bits
const uint32_t ARR_SIZE = 65536; //array size

/**
	Represents one entry of phonebook
*/
struct Entry{
	string* first_name;
	string* last_name;
	string* telephone;
};
/**
	Represents one node of phonebook. Every node must contain entry and (optional) pointer to next node.
*/
struct Node{
	Entry* entry;
	Node* next;
};
/**
	Just phonebook. With array of pointers of nodes.
*/
struct Phonebook{
	Node** nodes;
};

/**
	Generates 32-bit key from string. It uses XOR operation on wrapped string
	@param last_name - string to be numerized
*/
uint32_t generate_32bit_key(string last_name){
	uint32_t result = 0;
	int size = 32/8; //size in BYTES
	for(int i = 0; i < size; i++){
		char partial_result = last_name[i]; //in this char, XOR value of one column will be calculated
		int j = i+size;
		while(last_name.length() > j){
			partial_result ^= last_name[j];
			j+=size;
		}
		result |= partial_result; //this line adds partial_result bits to result
		if(i < (size-1)) //don't do in in last iteration!
			result <<=8; //move result by 8 bits in left to make space for another partial_result
	}
	return result;
}
/**
	Generates 32-bit array index from key, using modulo operation
	@param key - key
*/
uint32_t hash_function(uint32_t key){
	return key % ARR_SIZE;
}
/**
	Initalizes phonebook
	@param *phonebook - pointer to phonebook
*/
void init_phonebook(Phonebook *phonebook){
	phonebook->nodes = new Node*[ARR_SIZE]; //array of pointers
	for(int i = 0; i < ARR_SIZE; i++) phonebook->nodes[i]=NULL;
}
/**
	Finds node associated with last name. Can be useful if you can check collisions with this last name.
	@param *phonebook - pointer to phonebook
	@param last_name - last_name
	
	@return node or NULL if there is no last name associated with any node
*/
Node* find_node(Phonebook* phonebook, string last_name){
	uint32_t key = hash_function(generate_32bit_key(last_name));
	if(phonebook->nodes[key]==NULL) return NULL;
	return phonebook->nodes[key];
}
/**
	Adds new entry to phonebook.
	@param *phonebook - pointer to phonebook
	@param name - name
	@param last_name - last name
	@param telephone - telephone number
*/
void add_entry(Phonebook* phonebook, string name, string last_name, string telephone){
	Entry* entry = new Entry;
	entry->first_name=new string(name);
	entry->last_name=new string(last_name);
	entry->telephone=new string(telephone);
	
	uint32_t key = hash_function(generate_32bit_key(last_name));
		
	Node* node = new Node;
	node->entry=entry;
	node->next=phonebook->nodes[key];
	phonebook->nodes[key]=node;
}
/**
	Searches for FIRST entry in phonebook by last name.
	@param *phonebook - pointer to phonebook
	@param last_name - last name
	
	@return Entry* or NULL if there is no last name associated with any entry.
*/
Entry* find_entry(Phonebook* phonebook, string last_name){
	uint32_t key = hash_function(generate_32bit_key(last_name));
	if(phonebook->nodes[key]==NULL) return NULL;

	Node* node = phonebook->nodes[key];
	if(phonebook->nodes[key]->next==NULL && *node->entry->last_name == last_name) //this is a case if there is only one node associated to key
		return node->entry;
		
	while(node!=NULL){
		if(*node->entry->last_name == last_name) return node->entry;
		node=node->next;
	}
	return NULL;
}
/**
	Searches for FIRST entry in phonebook by last and first name.
	@param *phonebook - pointer to phonebook
	@param first_name - first name
	@param last_name - last name

	@return Entry* or NULL if there is no last and first name associated with any entry.
*/
Entry* find_entry(Phonebook* phonebook, string first_name, string last_name){
	uint32_t key = hash_function(generate_32bit_key(last_name));
	if(phonebook->nodes[key]==NULL) return NULL;

	Node* node = phonebook->nodes[key];
	if(phonebook->nodes[key]->next==NULL && *node->entry->first_name == first_name && *node->entry->last_name == last_name) //this is a case if there is only one node associated to key
		return node->entry;
		
	while(node!=NULL){
		if(*node->entry->last_name == last_name && *node->entry->first_name == first_name) return node->entry;
		node=node->next;
	}
	return NULL;
}
/**
	Prints all names and telephone numbers associated with last name.
	@param *phonebook - pointer to phonebook
	@param last_name - last name
*/
void print_telephone(Phonebook* phonebook, string last_name){
	uint32_t key = hash_function(generate_32bit_key(last_name));
	if(phonebook->nodes[key]==NULL) return;
	Node* node = phonebook->nodes[key];
	while(node!=NULL){
		if(*node->entry->last_name == last_name){
			cout << *node->entry->first_name << " " << *node->entry->last_name << " " << *node->entry->telephone << endl;
		}
		node=node->next;
	}
}
/**
	Makes sure that there is everything ok with your memory <3
	@param node* - node to be deleted
*/
void delete_node(Node* node){
	delete node->entry->first_name;
	delete node->entry->last_name;
	delete node->entry->telephone;
	delete node->entry;
	delete node;
}
/**
	Removes entry from phonebook. You can get entry by calling #find_entry() function.
	@param *phonebook - pointer to phonebook
	@param entry* - entry to be deleted
	
	@return true if entry existed and was deleted
*/
bool remove_entry(Phonebook* phonebook, Entry* entry){
	uint32_t key = hash_function(generate_32bit_key(*entry->last_name));
	if(phonebook->nodes[key]==NULL) return false;
	Node* node = phonebook->nodes[key];
	if(node->entry == entry){ //special case if first node is desired node
		phonebook->nodes[key] = node->next;
		delete_node(node);
		return true;
	}
	while(node->next!=NULL){
		if(node->next->entry == entry){
			Node* to_delete = node->next;
			node->next=to_delete->next;
			delete_node(to_delete);
			return true;
		}
		node = node->next;
	}
	return false;

}
int main() {
	Phonebook* phonebook = new Phonebook;
	init_phonebook(phonebook);
	add_entry(phonebook, "Jakub","Dybczak","123123123");
	add_entry(phonebook, "Jakub","Plotnikowski","321321321");
	add_entry(phonebook, "Mateusz","Kubicki","111222333");
	add_entry(phonebook, "Jacek","Kusnierz","696969696");
	add_entry(phonebook, "Jan","Kowalski","10101010");
	add_entry(phonebook, "Justyna","Kowilska","20202020");
	add_entry(phonebook, "Antoni","Kowalski","30303030");

	Entry* e1 = find_entry(phonebook,"Kowalski");
	Entry* e2 = find_entry(phonebook,"Kowilska");
	
	cout<<"Key for Dybczak is " << generate_32bit_key("Dybczak") << endl;
	cout<<"Key for Kowalski is " << generate_32bit_key("Kowalski") << endl;
	cout<<"Key for Kowilska is " << generate_32bit_key("Kowilska") << endl;

	cout<<endl;

	cout<<"Telephone of Dybczak is " << *find_entry(phonebook,"Dybczak")->telephone << endl;
	cout<<"Telephone of Kusnierz is " << *find_entry(phonebook,"Kusnierz")->telephone << endl;
	
	cout<<endl;

	cout<<"Are there more than one nodes associated with Dybczak key? " 
	<< (find_node(phonebook,"Dybczak")->next == NULL ? "No" : "Yes") << endl;

	cout<<"Are there more than one nodes associated with Kowalski key? " 
	<< (find_node(phonebook,"Kowalski")->next == NULL ? "No" : "Yes") << endl;
	
	cout<<"Are there more than one nodes associated with Kowilska key? " 
	<< (find_node(phonebook,"Kowilska")->next == NULL ? "No" : "Yes") << endl;
	
	cout<<endl;

	cout<<"Telephone of Kowalski is " << *find_entry(phonebook,"Kowalski")->telephone << " and his name: " << *find_entry(phonebook,"Kowalski")->first_name << endl;
	cout<<"Uhh, we missed Janek :( (it's because find_entry() returns last added entry to same node, and we have two Kowalski in one node)" << endl;
	
	cout<<endl;
	
	cout<<"Printing all numbers associated with Kowalski" << endl;
	print_telephone(phonebook,"Kowalski");
	
	cout<<endl;
	cout<<"Let's kill Janek!" << endl;
	remove_entry(phonebook,find_entry(phonebook,"Jan","Kowalski"));
	cout<<"Printing all numbers associated with Kowalski again:" << endl;
	print_telephone(phonebook,"Kowalski");
	return 0;
}
