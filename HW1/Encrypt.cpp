#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

char* CaesarEncrypt(char* input, char* key)
{
	int shift = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		shift = shift * 10;
		shift = shift + key[i] - '0';
	}
	char* Answer = input;
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] == ' ')
		{
			Answer[i] = ' ';
		}
		else
		{
			Answer[i] = (char)((input[i] - 'a' + shift) % 26 + 'A');
		}
	}
	return Answer;
}

char* PlayFairEncrypt(char* input, char* key)
{
	for (int i = 0; i < strlen(input); i++)
	{
		if (input[i] == 'j')
		{
			input[i] = 'i';
		}
	}
	for (int i = 0; i < strlen(key); i++)
	{
		if (key[i] == 'j')
		{
			key[i] = 'i';
		}
	}
	bool alphabet[26];
	for (int i = 0; i < 26; i++)
	{
		alphabet[i] = true;
	}
	char table[5][5];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			table[i][j] = '0';
		}
	}
	int keyPos = 0;
	for (int i = 0; i < 5 && keyPos < strlen(key); i++)
	{
		for (int j = 0; j < 5 && keyPos < strlen(key); j++)
		{
			if (alphabet[key[keyPos] - 'a'])
			{
				table[i][j] = key[keyPos];
				alphabet[key[keyPos] - 'a'] = false;
				keyPos++;
			}
			else
			{
				j--;
				keyPos++;
			}
		}
	}
	keyPos = 0;
	for (int i = 0; i < 5 && keyPos < 26; i++)
	{
		for (int j = 0; j < 5 && keyPos < 26; j++)
		{
			if (table[i][j] != '0')
			{
				continue;
			}
			if (keyPos == 'j' - 'a')
			{
				keyPos++;
			}
			if (alphabet[keyPos])
			{
				table[i][j] = keyPos + 'a';
				alphabet[keyPos] = false;
				keyPos++;
			}
			else
			{
				keyPos++;
				j--;
			}
		}
	}

	char* Encrypt = new char[strlen(input) + 1];
	for (int i = 0; i < strlen(input) + 1; i++)
	{
		Encrypt[i] = '\0';
	}
	int EncryptPos = 0;
	for (int i = 0; i < strlen(input); i++)
	{
		if (i + 1 >= strlen(input) && EncryptPos % 2 == 1)
		{
			char* temp = (char*)malloc(sizeof(char) * (EncryptPos + 2));
			for (int j = 0; j < EncryptPos + 2; j++)
			{
				temp[j] = '\0';
			}
			for (int j = 0; j < EncryptPos; j++)
			{
				temp[j] = Encrypt[j];
			}
			temp[EncryptPos] = 'x';
			Encrypt = temp;
			EncryptPos++;
			break;
		}
		if (input[i] == input[i + 1])
		{
			char* temp = (char*)malloc(sizeof(char) * (EncryptPos + strlen(input) - i + 2));
			for (int j = 0; j < EncryptPos + strlen(input) - i + 2; j++)
			{
				temp[j] = '\0';
			}
			int curPos = 0;
			for (int j = 0; j < EncryptPos; j++, curPos++)
			{
				temp[curPos] = Encrypt[j];
			}
			temp[curPos] = input[i];
			curPos++;
			temp[curPos] = 'x';
			curPos++;
			for (int j = i + 1; j < EncryptPos + strlen(input) - i + 2; j++, curPos++)
			{
				temp[curPos] = input[j];
			}
			Encrypt = temp;
			EncryptPos += 2;
		}
		else
		{
			Encrypt[EncryptPos] = input[i];
			EncryptPos++;
		}
	}
	if (EncryptPos % 2 == 1)
	{
		char* temp = (char*)malloc(sizeof(char) * (EncryptPos + 2));
		for (int j = 0; j < EncryptPos + 2; j++)
		{
			temp[j] = '\0';
		}
		for (int j = 0; j < strlen(Encrypt); j++)
		{
			temp[j] = Encrypt[j];
		}
		temp[EncryptPos] = 'x';
		Encrypt = temp;
		EncryptPos++;
	}
	char* EncryptResult = new char[EncryptPos];
	for (int i = 0; i < EncryptPos + 1; i++)
	{
		EncryptResult[i] = '\0';
	}
	for (int i = 0; i < EncryptPos; i += 2)
	{
		int row0, col0, row1, col1;
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (Encrypt[i] == table[j][k])
				{
					row0 = j;
					col0 = k;
				}
				if (Encrypt[i + 1] == table[j][k])
				{
					row1 = j;
					col1 = k;
				}
			}
		}

		if (row0 == row1)
		{
			col0++;
			col1++;
			col0 %= 5;
			col1 %= 5;
		}
		else if (col0 == col1)
		{
			row0++;
			row1++;
			row0 %= 5;
			row1 %= 5;
		}
		else
		{
			int temp = col0;
			col0 = col1;
			col1 = temp;
		}
		EncryptResult[i] = table[row0][col0] - 'a' + 'A';
		EncryptResult[i + 1] = table[row1][col1] - 'a' + 'A';
	}
	return EncryptResult;
}

char* VernamEncrypt(char* input, char* key)
{
	int inputPos = 0;
	int count = strlen(key);
	char* keykey = (char*)malloc(sizeof(char) * strlen(input));
	for (int i = 0; i < strlen(input); i++)
	{
		if (i < strlen(key))
		{
			keykey[i] = key[i];
		}
		else
		{
			keykey[i] = input[inputPos];
			inputPos++;
		}
	}
	char* encryption = input;
	for (int i = 0; i < strlen(input); i++)
	{
		int letter = 0;
		int keyletter = keykey[i] - 'a';
		int inputletter = input[i] - 'a';
		int power = 1;
		for (int j = 0; j < 5; j++)
		{
			bool xorRes = (keyletter % 2) ^ (inputletter % 2);
			keyletter = keyletter / 2;
			inputletter = inputletter / 2;
			letter = letter + xorRes * power;
			power = power * 2;
		}
		letter = letter % 26;
		encryption[i] = (letter + 'A');
	}
	return encryption;
}

char* RailFenceEncrypt(char* input, char* key)
{
	int rowNum = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		rowNum = rowNum * 10;
		rowNum = rowNum + key[i] - '0';
	}
	int colNum = strlen(input);
	char** table = new char* [rowNum];
	for (int i = 0; i < rowNum; i++)
	{
		table[i] = new char[colNum];
		for (int j = 0; j < colNum; j++)
		{
			table[i][j] = '0';
		}
	}

	bool direction = 0;
	for (int i = 0, j = 0; i < colNum; i++)
	{
		if (j == 0)
		{
			direction = true;
		}
		else if (j == rowNum - 1)
		{
			direction = false;
		}
		table[j][i] = input[i];
		if (direction)
		{
			j++;
		}
		else
		{
			j--;
		}
	}
	char* Encrypt = input;
	int Num = 0;
	for (int i = 0; i < rowNum; i++)
	{
		for (int j = 0; j < colNum; j++)
		{
			if (table[i][j] != '0')
			{
				Encrypt[Num] = (table[i][j] - 'a' + 'A');
				Num++;
			}
		}
	}
	return Encrypt;
}

char* RowEncrypt(char* input, char* key)
{
	int keyorder[10];
	for (int i = 0; i < 10; i++)
	{
		keyorder[i] = -1;
	}
	for (int i = 0; i < strlen(key); i++)
	{
		keyorder[key[i] - '0'] = i;
	}
	int colNum = strlen(key);
	int rowNum = strlen(input) / colNum;
	if (strlen(input) % colNum != 0)
	{
		rowNum++;
	}
	char** table = new char* [rowNum];
	for (int i = 0; i < rowNum; i++)
	{
		table[i] = new char[colNum];
		for (int j = 0; j < colNum; j++)
		{
			table[i][j] = '0';
		}
	}
	for (int i = 0; i < rowNum; i++)
	{
		for (int j = 0; j < colNum; j++)
		{
			if (i * colNum + j < strlen(input))
			{
				table[i][j] = input[i * colNum + j];
			}
			else
			{
				break;
			}
		}
	}
	int encryptPos = 0;
	char* Encrypt = input;
	for (int i = 0; i < 10; i++)
	{
		if (keyorder[i] != -1)
		{
			int col = keyorder[i];
			for (int j = 0; j < rowNum; j++)
			{
				if (table[j][col] != '0')
				{
					Encrypt[encryptPos] = table[j][col] - 'a' + 'A';
					encryptPos++;
				}
			}
		}
	}
	return Encrypt;
	
}

int main(int argc, char** argv)
{
	char* method = argv[1];
	char* input = argv[1];
	char* key = argv[1];
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-m") == 0)
		{
			method = argv[i + 1];
		}
		if (strcmp(argv[i], "-i") == 0)
		{
			input = argv[i + 1];
		}
		if (strcmp(argv[i], "-k") == 0)
		{
			key = argv[i + 1];
		}
	}

	if (strcmp(method, "caesar") == 0)
	{
		cout << CaesarEncrypt(input, key);
	}
	else if (strcmp(method, "playfair") == 0)
	{
		cout << PlayFairEncrypt(input, key);
	}
	else if (strcmp(method, "vernam") == 0)
	{
		cout << VernamEncrypt(input, key);
	}
	else if (strcmp(method, "railfence") == 0)
	{
		cout << RailFenceEncrypt(input, key);
	}
	else if (strcmp(method, "row") == 0)
	{
		cout << RowEncrypt(input, key);
	}
	cout << endl;
	return 0;
}
