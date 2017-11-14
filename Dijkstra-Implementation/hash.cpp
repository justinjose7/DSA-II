#include "hash.h"
#include <iostream>

// prime numbers used in hash function 
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define prime_0 37 /* also prime */

using namespace std;

hashTable::hashTable(int size){
	capacity = getPrime(size);
	data.resize(capacity);
	
	for(int i = 0; i < capacity; i++){
		data[i].key = "";
		data[i].isOccupied == 0;
		data[i].isDeleted == 0;
		data[i].pv = NULL;
	}
}

int hashTable::insert(const std::string &key, void *pv){
	int index = hash(key);

	if (contains(key)){
		return 1;
	}

	while (data[index].isOccupied){
		index++;

	}
	if (!(data[index].isOccupied) || data[index].isDeleted){
		data[index].key = key;
		data[index].isOccupied = 1;
		data[index].isDeleted = 0;
		data[index].pv = pv;
		filled++;
	}
	
	if (filled >= capacity/2) {
			
		if(!rehash()){ //rehash and check if memory allocation fails
			return 2;
		}
	}

	return 0;
}

bool hashTable::contains(const std::string &key){
	if (findPos(key) != -1){
		return true;
	}
	return false;
}

void *hashTable::getPointer(const string &key, bool *b){
	int index = findPos(key);
	
	if(index == -1){
		*b = false;
		return NULL;
	}
	else{
		*b = true;
		return data[index].pv;
	}
}

int hashTable::setPointer(const string &key, void *pv){
	int index = findPos(key);
	
	if(index == -1)
		return 1;
	else
		data[index].pv = pv;
	return 0;
}

int hashTable::findPos(const string &key){
	int index = hash(key);
		
	while(data[index].isOccupied == true){
		
		if((data[index].key == key) && (data[index].isDeleted == false))
			return index;

		index++;
	}
	
	return -1;
}

bool hashTable::remove(const string &key){
	int index = findPos(key);

	if(index == -1)
		return false;
	else
		data[index].isDeleted = true;
	
	return true;
}

int hashTable::hash(const std::string &key) //hash function found on google
{
   unsigned h = prime_0;
   int i = 0;

   for (int i = 0; i < key.size(); i++) {
     h = (h * A) ^ (key[i] * B);
   }

   return h % (data.size()-1); 
}

bool hashTable::rehash(){
	try{
		vector<hashItem> temp = data;
		capacity = getPrime(capacity * 2);

		filled = 0;
		data.clear();
		data.resize(capacity);

		for(int i = 0; i < temp.size(); i++){
			
			if(temp[i].isOccupied && !(temp[i].isDeleted)){
				insert(temp[i].key, temp[i].pv);
			}
				
		}
		return true;
	}
	catch(exception& e){
		return false;
	}
}

bool isPrime(int size){
	for (int i = 2; i <= size/2; i++){
        
        if (size % i == 0)     //checks if has a factor that isn't 1 or size
           return false;
    }
    return true;
}

unsigned int hashTable::getPrime(int size){
    bool found = false;
    while (!found)
    {
        size++;
        
        if (isPrime(size))
            found = true;
    }

    return size;

}


