#ifndef hashTableH
#define hashTableH
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

class hashTable {
public:
	hashTable();

	~hashTable();

	void add(string word, string definition);

	void findWord(string word);

private:
	void deleteMap();

	int hash(string word);

	void rebuilding();

	List *hashMap;
	int size;
	int numberOfWords;
};
#endif