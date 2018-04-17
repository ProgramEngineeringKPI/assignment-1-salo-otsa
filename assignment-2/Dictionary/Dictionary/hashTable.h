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


private:
	void deleteMap();

	int getKey(string word);

	void rebuilding();

	List *hashMap;
	int size;
	int numberOfWords;
};
#endif