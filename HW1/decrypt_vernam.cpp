#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

int main(int argc, char* argv[]) {
	string input, key;
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
	//cout << "Enter key: ";
	//cin >> key;
	key = argv[6];
	int j = 0;
	int mod = key.size();
	for (int i = key.size(); i < input.size(); i++) {
		key += key[j % mod]; j++;
	}
	string answer;
	for (int i = 0; i < input.size(); i++) {
		answer += (input[i] - key[i] + 26) % 26 + 'A';
	}
	cout << "Decrypt text: ";
	ofstream output;
	output.open(outputFile);
	output << answer;
	output.close();
	return 0;
}