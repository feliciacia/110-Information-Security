#include<iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

//for playfair
void createMatrix(string key, int keyLength, char matrix[5][5])
{
	int k = 0, count[26] = { 0 };
	char keyArr[200] = { 0 };
	string keys;
	for (int i = 0; i < key.length(); i++)
	{
		count[key[i] - 'a']++; //count key char
	}
	for (int i = 0, j = 'a'; i <= 25 && j <= 'z'; i++, j++) // add char that aren't in the key 
	{
		if (j == 'j')
		{
			continue;
		}
		if (count[i] <= 0)
		{
			key.push_back(j);
			count[i]++;
		}
		else
		{
			continue;
		}

	}
	for (int i = 0; i < 25; i++)
	{
		keyArr[i] = key[i]; // changing string to char array
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			matrix[i][j] = keyArr[k]; // adding char to 2d matrix
			k++;
		}
	}
}

string removeSpace(string str) //function used to remove space betwwen word (ex: Play Fair become PlayFair)
{
	string res;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 32)
		{
			continue;
		}
		res.push_back(str[i]);
	}
	return res;
}

void getPosition(char ch, int& row, int& col) {
	if (ch < 'J') {
		row = (ch - 65) / 5;
		col = (ch - 65) % 5;
	}
	else if (ch > 'J') {
		row = (ch - 66) / 5;
		col = (ch - 66) % 5;
	}
}

string removeDuplicate(string str)
{
	string res;
	char Arr[200];
	int count[200] = { 0 };
	for (int i = 0; i < str.length(); i++)
	{
		Arr[i] = str[i];
		if (count[Arr[i]] < 1)
		{
			res.push_back(Arr[i]);
			count[Arr[i]]++;
		}
	}
	return res;
}

//for row
char arr[100][100], tempArr[100][100];
char temp[100], temp2[100], keys[100], answer[100];

int findMin() {
	int min = temp[0];
	int idx = 0;
	int i = 0;
	for (i = 0; temp[i] != NULL; i++) {
		if (temp[i] < min) {
			min = temp[i];
			idx = i;
		}
	}
	temp[idx] = 123;
	return(idx);
}

void makeArr(int col, int row) {
	for (int i = 0; i < row; i++) {
		tempArr[i][col] = temp2[i];
	}
}

//main program
int main(int argc, char** argv) {
	//char* input = argv[4];
	string method = argv[2];

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-m") == 0) {
			method = argv[i + 1];
		}
	}
	if (method == "caesar") {
		char* input = argv[4];
		char* key = argv[6];
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-i") == 0) {
				input = argv[i + 1];
			}
			if (strcmp(argv[i], "-k") == 0) {
				key = argv[i + 1];
			}
		}
		int shift = 0;
		for (int i = 0; i < strlen(key); i++)
		{
			shift = shift * 10;
			shift = shift + key[i] - '0';
		}
		for (int i = 0; i < strlen(input); i++) {
			input[i] = toupper(input[i]);
			if (input[i] >= 'A' && input[i] <= 'Z') {
				char temp = input[i];
				temp = temp - shift;
				if (temp < 'A')temp = temp + 'Z' - 'A' + 1;
				input[i] = temp;
			}
			else continue;
		}
		std::cout << input;
	}
	else if (method == "playfair") {
		char* input = argv[4];
		string answer;
		char* key = argv[6];
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-i") == 0) {
				input = argv[i + 1];
			}
			if (strcmp(argv[i], "-k") == 0) {
				key = argv[i + 1];
			}
		}
		string tempKey, tempStr;
		int keyLength = 0;
		char matrix[5][5];

		tempKey = removeSpace(key);
		for (int i = 0; i < tempKey.length(); i++) // change 'j' to 'i'
		{
			if (tempKey[i] == 'j')
			{
				tempKey[i] = 'i';
			}
		}
		tempKey = removeDuplicate(tempKey); // remove duplicate character
		keyLength = tempKey.length();

		createMatrix(tempKey, keyLength, matrix); //create matrix table

		tempStr = removeSpace(input);
		int strLength = strlen(input);
		for (int i = 0; i < strlen(input); i++)
		{
			int j = i + 1;
			if (input[i] == input[j])
			{
				for (int k = j; k <= j; k++)input[k] += 'x';
				//input.insert(j, 1, 'x'); //insert x if the char is the same (ex: LL become LX)
			}
		}
		if (strlen(input) % 2 != 0)
		{
			input += 'x'; // Add X at the end of the word if the length is odd
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				matrix[i][j] = toupper(matrix[i][j]);
			}
		}
		for (int i = 0; i < strlen(input); i++) {
			input[i] = toupper(input[i]);
		}

		for (int i = 0; i < strlen(input); i++) {
			int row1, row2, col1, col2;

			getPosition(input[i], row1, col1); //first word
			i++;
			getPosition(input[i], row2, col2); //second word

			if (row1 == row2) {
				answer.push_back(matrix[row1][(col1 - 1) % 5]);
				answer.push_back(matrix[row1][(col2 - 1) % 5]);
			}
			else if (col1 == col2) {
				answer.push_back(matrix[(row1 - 1) % 5][col1]);
				answer.push_back(matrix[(row2 - 1) % 5][col1]);
			}
			else {
				answer.push_back(matrix[row1][col2]);
				answer.push_back(matrix[row2][col1]);
			}
		}
		//cout << "Decrypt text: ";
		//ofstream output;
		//output.open(outputFile);
		for (int i = 0; i < answer.length(); i++) {
			if (answer[i] != 'X') {
				std::cout << answer[i];
			}
			else continue;
		}
	}
	else if (method == "vernam") {
		char* input = argv[4];
		char* key = argv[6];
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-i") == 0) {
				input = argv[i + 1];
			}
			if (strcmp(argv[i], "-k") == 0) {
				key = argv[i + 1];
			}
		}
		int j = 0;
		int mod = strlen(key);
		for (int i = strlen(key); i < strlen(input); i++) {
			key += key[j % mod]; j++;
		}
		string answer;
		for (int i = 0; i < strlen(input); i++) {
			answer += (input[i] - key[i] + 26) % 26 + 'A';
		}
		std::cout << answer;
	}
	else if (method == "railfence") {
		char* input = argv[4];
		char* keys = argv[6];
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-i") == 0) {
				input = argv[i + 1];
			}
			if (strcmp(argv[i], "-k") == 0) {
				keys = argv[i + 1];
			}
		}
		int key = 0;
		for (int i = 0; i < strlen(keys); i++)
		{
			key = key * 10;
			key = key + keys[i] - '0';
		}
		int inputLen = strlen(input);
		char** rail = new char* [key];
		for (int i = 0; i < key; i++)rail[i] = new char[inputLen];
		for (int i = 0; i < key; i++) {
			for (int j = 0; j < strlen(input); j++) {
				rail[i][j] = '\n';
			}
		}
		int row = 0, col = 0, k = -1;
		for (int i = 0; i < strlen(input); i++) {
			rail[row][col++] = '*';
			col++;
			if (row == 0 || row == key - 1)k *= (-1);
			row += k;
		}
		int count = 0;
		for (int i = 0; i < key; i++) {
			for (int j = 0; j < strlen(input); j++) {
				if (rail[i][j] == '*')rail[i][j] = input[count++];
			}
		}
		row = 0;
		col = 0;
		k = -1;

		for (int i = 0; i < strlen(input); i++) {
			rail[row][col] = toupper(rail[row][col]);
			std::cout << rail[row][col++];
			if (row == 0 || row == key - 1)k *= (-1);
			row += k;
		}
	}
	else if (method == "row") {
		char* input = argv[4];
		char* key = argv[6];
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-i") == 0) {
				input = argv[i + 1];
			}
			if (strcmp(argv[i], "-k") == 0) {
				key = argv[i + 1];
			}
		}
		for (int i = 0; i < strlen(key); i++)keys[i] = key[i];
		//strcpy(temp, keys);
		int i = 0;
		for (i = 0; keys[i] != '\0'; i++) {
			temp[i] = keys[i];
		}
		temp[i] = '\0';
		int flag = 0;
		int k = 0;
		int rows = 0, cols = 0;
		int j = 0;
		i = 0;
		for (i = 0;; i++) {
			if (flag)break;
			for (j = 0; key[j] != NULL; j++) {
				if (input[k] == NULL) {
					flag = 1;
					arr[i][j] = '-';
				}
				else {
					arr[i][j] = input[k];
					k++;
				}
			}
		}
		rows = i;
		cols = j;

		int idx;
		k = 0;
		int key_len = strlen(keys);
		int row = strlen(input) / key_len;
		j = 0;
		for (int i = 0, k = 1; input[i] != NULL; i++, k++) {
			temp2[j] = input[i];
			j++;
			if ((k % row) == 0) {
				temp2[j] = '\0';
				idx = findMin();
				makeArr(idx, row);
				j = 0;
			}
		}
		k = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				answer[k++] = tempArr[i][j];
			}
		}
		answer[k] = '\0';
		for (int i = 0; answer[i] != NULL; i++) {
			answer[i] = toupper(answer[i]);
			std::cout << answer[i];
		}
	}
	std::cout << std::endl;
	return 0;
}
