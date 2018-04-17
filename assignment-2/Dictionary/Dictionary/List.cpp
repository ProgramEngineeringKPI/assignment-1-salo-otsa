#include "List.h"

List::List() {
	listSize = 0;
	listHead = NULL;
	listTail = NULL;
};

List::~List() {
	List::deleteList();
	listHead = listTail;
	delete listHead;
};

void List::deleteList() {
	while (listHead != listTail) shift();
};

void List::push(string word, string definition) {
	listSize++;
	Node* node = new Node(word, definition);
	if (listTail) listTail->next = node;
	if (!listHead) listHead = node;
	listTail = node;
};

void List::shift() {
	if (listHead) {
		listSize--;
		Node* newHead = listHead->next;
		delete listHead;
		listHead = newHead;
	}
};

void List::findWord(string word) {
	Node* temp = listHead;
	while(temp && temp->word != word)
		temp = temp->next;

	if (temp->word == word)
		cout << temp->word << ": " << temp->definition << endl;
	else
		cout << "No such word" << endl;

	delete temp;
};
