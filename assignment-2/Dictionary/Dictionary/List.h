#ifndef ListH
#define ListH
#include <iostream>
#include <string>

using namespace std;

class List {
public:
	List();

	~List();

	void deleteList();

	void push(string word, string definition);

	void shift();

	bool findElementInList(string word);

	struct Node {
		Node(string newWord, string newDefinition) {
			word = newWord;
			definition = newDefinition;
			next = NULL;
		};

		string definition;
		string word;
		Node *next;
	};

	Node *listHead;
	Node *listTail;

	int listSize;
};
#endif