#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

const char playfair[5][5] = {{'A','B','C','D','E'},
							{'F','G','H','I','K'},
							{'L','M','N','O','P'},
							{'Q','R','S','T','U'},
							{'V','W','X','Y','Z'} };

void getPosition(char ch, int &row, int &col) {
	if (ch < 'J') {
		row = (ch - 65) / 5;
		col = (ch - 65) % 5;
	}
	else if (ch > 'J') {
		row = (ch - 66) / 5;
		col = (ch - 66) % 5;
	}
}

int main(int argc, char* argv[]) {
	string input, answer;

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
	//cout << "Enter text: ";
	//getline(cin, input);
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
	}
	for (int i = 0; i < input.length(); i++) {
		int row1, row2, col1, col2;
		getPosition(input[i], row1, col1); //first word
		i++;
		getPosition(input[i], row2, col2); //second word

		if (row1 == row2) {
			answer.push_back(playfair[row1][(col1 + 4) % 5]);
			answer.push_back(playfair[row1][(col2 + 4) % 5]);
		}
		else if (col1 == col2) {
			answer.push_back(playfair[(row1 + 4) % 5][col1]);
			answer.push_back(playfair[(row2 + 4) % 5][col1]);
		}
		else {
			answer.push_back(playfair[row1][col2]);
			answer.push_back(playfair[row2][col1]);
		}
	}
	cout << "Decrypt text: ";
	ofstream output;
	output.open(outputFile);
	for (int i = 0; i < answer.length(); i++) {
		if (answer[i] != 'X') {
			output << answer[i];
		}
		else continue;
	}
	output.close();
	return 0;
}