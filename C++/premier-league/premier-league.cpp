#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

struct Team {
	std::string name;
	int **matches;
	int result;
};

struct Team *parseCSV(std::string fileName);
void writeToFile(struct Team *data);
void teamsResult(struct Team *data);

int teamsNumber  = 0, matchesNumber = 0;

int main() {

	Team *data = parseCSV("../premier_league.csv");
	teamsResult(data);

	for (int i = 0; i < teamsNumber; i++) {
		std::cout << "Name: " << (data + i)->name << ": ";
		for (int j = 0; j < matchesNumber; j++) {
			std::cout << "|" << (data + i)->matches[j][0] << ":" << (data + i)->matches[j][1] << "| ";
		}
		std::cout << "result: " << (data + i)->result << std::endl;
	}

	writeToFile(data);

	delete[] data;
	system("pause");
	return 0;
}

struct Team *parseCSV(std::string fileName) {
	std::ifstream fromFile(fileName);

	if (fromFile.is_open()) {
		std::string cell, line;

		std::getline(fromFile, line);
		std::stringstream lineString(line);

		lineString >> teamsNumber;
		matchesNumber = teamsNumber / 2;

		Team *data = new Team[teamsNumber];
		for (int i = 0; i < teamsNumber; i++) {
			(data + i)->matches = new int*[matchesNumber];

			std::getline(fromFile, line);
			std::stringstream lineString(line);

			std::getline(lineString, cell, ',');
			(data + i)->name = cell;

			for (int j = 0; j < matchesNumber; j++) {
				(data + i)->matches[j] = new int[2];

				std::getline(lineString, cell, ':');
				(data + i)->matches[j][0] = atoi(cell.c_str());

				std::getline(lineString, cell, ',');
				(data + i)->matches[j][1] = atoi(cell.c_str());
			}
		}

		fromFile.close();
		return data;
	} else {
		std::cout << "No such file." << std::endl;
		return NULL;
	}
};

void writeToFile(struct Team *data) {
	std::ofstream intoFile("../result.csv");
	for (int i = 0; i < teamsNumber; i++)
		intoFile << (data + i)->name << " " << (data + i)->result << std::endl;
	intoFile.close();
};

void teamsResult(struct Team *data) {
	int result;
	for (int i = 0; i < teamsNumber; i++) {
		result = 0;
		for (int j = 0; j < matchesNumber; j++) {
			if((data + i)->matches[j][0] >= (data + i)->matches[j][1]) {
				if ((data + i)->matches[j][0] > (data + i)->matches[j][1]) result += 2;
				++result;
			}
		}
		(data + i)->result = result;
	}
};
