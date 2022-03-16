#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int  main(int argc, char* argv[]) {
	string input;
	int key;
	string inputFile = argv[4];
	string outputFile = "output.txt";

	ifstream inputF;
	inputF.open(inputFile);
	if (inputF.fail()) {
		cout << "Read File Fail\n"; exit(1);
	}
	string line = "";
	while (getline(inputF, line)) {
		stringstream file(line);
		file >> input;
	}
	//getline(cin, input);
	//cin >> key;
	key = atoi(argv[6]);
	int inputLen = input.length();
	char** rail = new char* [key];
	for (int i = 0; i < key; i++)rail[i] = new char[inputLen];
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < inputLen; j++) {
			rail[i][j] = '\n';
		}
	}
	int row = 0, col = 0, k = -1;
	for (int i = 0; i < input.length(); i++) {
		rail[row][col++] = '*';
		//col++;
		if (row == 0 || row == key - 1)k *= (-1);
		row += k;
	}
	int count = 0;
	for (int i = 0; i < key; i++) {
		for (int j = 0; j < input.length(); j++) {
			if (rail[i][j] == '*')rail[i][j] = input[count++];
		}
	}
	row = 0;
	col = 0;
	k = -1;
	ofstream output;
	output.open(outputFile);
	for (int i = 0; i < input.length(); i++) {
		rail[row][col] = toupper(rail[row][col]);
		output << rail[row][col++];
		if (row == 0 || row == key - 1)k *= (-1);
		row += k;
	}
	output.close();
	return 0;
}