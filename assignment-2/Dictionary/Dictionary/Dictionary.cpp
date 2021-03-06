#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "hashTable.h"

hashTable *parseCSV(string fileName);

int main() {
	hashTable *dictionary = parseCSV("../dict_processed.txt");
	string word, flag;
	while (true) {
		cout << "q to exit" << endl;
		cout << "Type word:" << endl;
		getline(cin, word);
		if ("q" == word) break;
		dictionary->findWord(word);
	}
	delete dictionary;

	system("pause");
    return 0;
}

hashTable *parseCSV(string fileName) {
	ifstream fromFile(fileName);

	if (fromFile.is_open()) {
		hashTable *dictionary = new hashTable;
		string cell, line, word, definition;

		while (!fromFile.eof()) {

			getline(fromFile, line);
			stringstream lineString(line);

			getline(lineString, cell, ';');
			word = cell;

			getline(lineString, cell);
			definition = cell;

			dictionary->add(word, definition);
		}

		fromFile.close();
		return dictionary;
	}
	else {
		cout << "No such file." << endl;
		return NULL;
	}
};
