#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

struct Team {
	string name;
	int **matches;
	bool validation;
	int result;
};

struct Team *parseCSV(string fileName);
void writeToFile(struct Team *data);
void teamsResult(struct Team *data);
bool isNumber(string value);

int teamsNumber  = 0, matchesNumber = 0;

int main() {

	Team *data = parseCSV("../premier_league.csv");
	teamsResult(data);

	for (int i = 0; i < teamsNumber; i++) {
		cout << "Name: " << (data + i)->name << ": ";
		if (!(data + i)->validation) {
			cout << " error validation" << endl;
			continue;
		};
		for (int j = 0; j < matchesNumber; j++) {
			cout << "|" << (data + i)->matches[j][0] << ":" << (data + i)->matches[j][1] << "| ";
		}
		cout << "result: " << (data + i)->result << endl;
	}

	writeToFile(data);

	delete[] data;
	system("pause");
	return 0;
}

struct Team *parseCSV(string fileName) {
	ifstream fromFile(fileName);

	if (fromFile.is_open()) {
		string cell, line;
		int home, guest, matchesNumberCurr;

		getline(fromFile, line);
		stringstream lineString(line);

		lineString >> teamsNumber;
		matchesNumber = teamsNumber / 2;

		Team *data = new Team[teamsNumber];
		for (int i = 0; i < teamsNumber; i++) {
			matchesNumberCurr = 0;
			(data + i)->matches = new int*[matchesNumber];

			getline(fromFile, line);
			stringstream lineString(line);

			getline(lineString, cell, ',');
			(data + i)->name = cell;

			(data + i)->validation = true;

			for (int j = 0; !lineString.eof(); j++, matchesNumberCurr++) {
				if (matchesNumberCurr == matchesNumber) {
					(data + i)->validation = false;
					break;
				}
				(data + i)->matches[j] = new int[2];

				getline(lineString, cell, ':');
				if (!isNumber(cell)) {
					(data + i)->validation = false;
					break;
				}

				(data + i)->matches[j][0] = atoi(cell.c_str());

				getline(lineString, cell, ',');
				if (!isNumber(cell)) {
					(data + i)->validation = false;
					break;
				}

				(data + i)->matches[j][1] = atoi(cell.c_str());
			}

			if (matchesNumberCurr < matchesNumber) (data + i)->validation = false;
		}

		fromFile.close();
		return data;
	} else {
		cout << "No such file." << endl;
		return NULL;
	}
};

void writeToFile(struct Team *data) {
	ofstream intoFile("../result.csv");
	for (int i = 0; i < teamsNumber; i++)
		if((data + i)->validation)
			intoFile << (data + i)->name << " " << (data + i)->result << endl;
		else
			intoFile << (data + i)->name << " error validation." << endl;
	intoFile.close();
};

bool isNumber(string value) {
	for (int i = 0; i < value.length(); i++) {
		if (!isdigit(value[i])) return false;
	};
	return true;
};

void teamsResult(struct Team *data) {
	int result;
	for (int i = 0; i < teamsNumber; i++) {
		result = 0;
		if (!(data + i)->validation) continue;
		for (int j = 0; j < matchesNumber; j++) {
			if((data + i)->matches[j][0] >= (data + i)->matches[j][1]) {
				if ((data + i)->matches[j][0] > (data + i)->matches[j][1]) result += 2;
				++result;
			}
		}
		(data + i)->result = result;
	}
};
