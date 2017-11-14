#include "heap.h"
#include "hash.h"
#include <iostream>

using namespace std;

heap::heap(int size){
	currentSize = 0;
	capacity = size;
	data.resize(capacity + 1);
	mapping = new hashTable(capacity*200);;

}

int heap::insert(const std::string &id, int key, void *pv){
	if (currentSize == capacity){
		return 1;
	}
	if (mapping->contains(id)){
		return 2;
	}

	currentSize++;

	data[currentSize].id = id;
	data[currentSize].key = key;
	data[currentSize].pData = pv;

	mapping->insert(id, &data[currentSize]);

	percolateUp(currentSize);

	return 0;
}

int heap::setKey(const string &id, int key){
	bool b;

	node *pn = static_cast<node *> (mapping->getPointer(id, &b));

	if(b == false)
		return 1;

	int updatedPos = getPos(pn);

	data[updatedPos].key = key;
	
	if(updatedPos > 1){
		
		if(data[updatedPos].key < data[updatedPos/2].key)
			percolateUp(updatedPos);

	}
	
	if(currentSize >= 2*updatedPos){
		
		if((data[updatedPos].key > data[updatedPos*2].key) || (data[updatedPos].key > data[(updatedPos*2) +1].key))
			percolateDown(updatedPos);
	
	}
	

	return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
	if (currentSize == 0)
		return 1;

	if (pId != NULL)
		*pId = data[1].id;

	if (pKey != NULL)
		*pKey = data[1].key;

	if (ppData != NULL)
		*(static_cast<void **> (ppData)) = data[1].pData;
	

	swap(data[1], data[currentSize]);

	mapping->setPointer(data[1].id, &data[1]);
	mapping->remove(data[currentSize].id);

	currentSize--;
	
	percolateDown(1);
	return 0;

}

int heap::remove(const std::string &id, int *pKey, void *ppData){
	bool b;
	
	node *pn = static_cast<node *> (mapping->getPointer(id, &b));

	if(b == false)
		return 1;

	int updatedPos = getPos(pn);

	if (pKey != NULL)
		*pKey = data[updatedPos].key;

	if (ppData != NULL)
		ppData = data[updatedPos].pData;

	swap(data[currentSize], data[updatedPos]);
	mapping->setPointer(data[updatedPos].id, &data[updatedPos]);
	
	mapping->remove(data[currentSize].id);
	
	currentSize--;

	if (currentSize >= 2*updatedPos){
		if(data[updatedPos].key > data[updatedPos*2].key || data[updatedPos].key > data[(updatedPos*2) +1].key){
			percolateDown(updatedPos);

		}
	}

	if(updatedPos > 1){
		if(data[updatedPos].key < data[updatedPos/2].key){
			percolateUp(updatedPos);

		}
	}
	
	return 0;

}


void heap::percolateUp(int posCur){
	int tempPos = posCur;
	
	while (tempPos > 1 && data[tempPos].key < data[tempPos/2].key){
		swap(data[tempPos], data[tempPos/2]);
		mapping->setPointer(data[tempPos].id, &data[tempPos]);
		mapping->setPointer(data[tempPos/2].id, &data[tempPos/2]);
		tempPos = tempPos/2;
	}
	
}

void heap::percolateDown(int posCur){
	int tempPos = posCur;
	int child;

	while(currentSize	>= tempPos*2){
		child = tempPos * 2;

		if(child != currentSize && data[child+1].key < data[child].key)
			++child;

		if(data[child].key < data[tempPos].key){
			swap(data[tempPos],data[child]);
			mapping->setPointer(data[tempPos].id, &data[tempPos]);
			mapping->setPointer(data[child].id, &data[child]);
			tempPos = child;
		}
		else
			break;

	}

}
	
int heap::getPos(node *pn){
	int pos = pn - &data[0];
	return pos;
}

