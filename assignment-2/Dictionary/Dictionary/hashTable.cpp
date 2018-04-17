#include "hashTable.h"

hashTable::hashTable() {
	numberOfWords = 0;
	size = 50;
	hashMap = new List[size];
};

hashTable::~hashTable() {
	deleteMap();
};

void hashTable::deleteMap() {
	for (int i = 0; i < size; i++)
		hashMap[i].deleteList();
	delete [] hashMap;
};

int hashTable::getKey(string word) {
	return numberOfWords;
};

void hashTable::add(string word, string definition) {
	if (size * 0.8 < numberOfWords)
		rebuilding();
	int key = getKey(word);
	hashMap[key].push(word, definition);
	numberOfWords++;
};

void hashTable::rebuilding() {
	List *tempMap = new List[size];
	List::Node* temp = NULL;
	int counter = numberOfWords;
	cout << "================" << endl << "Rebuilding: " << size << endl;
	for (int i = 0; i < counter; i++) {
		temp = hashMap[i].listHead;
		for (int j = 0; j <  hashMap[i].listSize; j++) {
			tempMap[i].push(temp->word, temp->definition);
			temp = temp->next;
		}
	}
	deleteMap();
	size *= 2;
	hashMap = new List[size];
	numberOfWords = 0;

	for (int i = 0; i < counter; i++)
		add(tempMap[i].listHead->word, tempMap[i].listHead->definition);
	delete temp;
	for (int i = 0; i < counter; i++)
		tempMap[i].deleteList();
	delete [] tempMap;
	cout << "================" << endl << "Rebuilding end: " << size << endl;
}