#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "hashTable.h"

int main() {
	hashTable *test = new hashTable;

	ifstream fromFile("../dict_processed.txt");

	if (fromFile.is_open()) {
		string cell, line, word, definition;
		
		while (!fromFile.eof()) {

			getline(fromFile, line);
			stringstream lineString(line);

			getline(lineString, cell, ';');
			word = cell;

			getline(lineString, cell);
			definition = cell;

			test->add(word, definition);
		}

		fromFile.close();
	}
	else {
		cout << "No such file." << endl;
	}

	delete test;

	system("pause");
    return 0;
}
