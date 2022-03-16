#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int main(int argc, char* argv[]) {
	string input = "";

	string inputFile = argv[4];
	string outputFile = "output.txt";

	ifstream inputF;

	inputF.open(inputFile);
	if (inputF.fail()) {
		cout << "Read File Fail\n"; exit(1);
	}
	//cout << "Enter text: ";
	//cout << "Enter key: ";
	int key = stoi(argv[6]);
	string line = "";
	//cin >> key;
	while (getline(inputF, line)) {
		stringstream file(line);
		file >> input;
	}
	for (int i = 0; i < input.size(); i++) {
		//for lower case
		if (input[i] >= 'a' && input[i] <= 'z') {
			char temp = input[i];
			temp = temp - key;
			if (temp < 'a')temp = temp + 'z' - 'a' + 1;
			input[i] = temp;
		}
		else if (input[i] >= 'A' && input[i] <= 'Z') {
			char temp = input[i];
			temp = temp - key;
			if (temp < 'A')temp = temp + 'z' - 'a' + 1;
			input[i] = temp;
		}
		else continue;
	}
	//cout << "Decrypt text: " << input;
	ofstream output;
	output.open(outputFile);
	if (output.fail()) {
		cout << "Output File failed\n";
		exit(1);
	}
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);
		output << input[i];
	}
	//output << input;
	output.close();
	return 0;
}