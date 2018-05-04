#include "hashTable.h"

hashTable::hashTable() {
	numberOfWords = 0;
	size = 1000;
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

int hashTable::hash(string word) {
	int key = 0;
	for (int i = 0; i < word.length(); i++)
		key += word[i];
	key *= key;
	key = key % size;
	return key;
};

void hashTable::add(string word, string definition) {
	if (size * 0.8 < numberOfWords)
		rebuilding();
	int key = hash(word);
	hashMap[key].push(word, definition);
	numberOfWords++;
};

void hashTable::rebuilding() {
	List *tempMap = new List[size];
	List::Node* temp = NULL;
	int counter = numberOfWords;
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

	for (int i = 0; i < counter; i++) {
		temp = tempMap[i].listHead;
		for (int j = 0; j < tempMap[i].listSize; j++) {
			add(temp->word, temp->definition);
			temp = temp->next;
		}
	}
	delete temp;
	for (int i = 0; i < counter; i++)
		tempMap[i].deleteList();
	delete [] tempMap;
};

void hashTable::findWord(string word) {
	for (int i = 0; i < word.length(); i++)
		word[i] = toupper(word[i]);
	int key = hash(word);
	bool result = hashMap[key].findElementInList(word);
	if (!result) {
		string definition;
		cout << "Add definition to word:" << endl;
		getline(cin, definition);
		add(word, definition);
	}
};
