#include <iostream>
#include <string>
#include <cmath>
#include <string.h>
using namespace std;

string RightShift_1Bit(string key)
{
	string decrypt = "";
	decrypt += key[27];
	for (int j = 0; j < 27; j++)
	{
		decrypt += key[j];
	}
	return decrypt;
}

string RightShift_2Bit(string key)
{
	string decrypt = "";
	for (int i = 0; i < 2; i++)
	{
		decrypt += key[27];
		for (int j = 0; j < 27; j++)
		{
			decrypt += key[j];
		}
		key = decrypt;
		decrypt = "";
	}
	return key;
}

string ConvertHexatoBin(string hexa)
{
	string bin = "";
	for (int i = 0; i < hexa.length(); i++)
	{
		if (hexa[i] == '0')
		{
			bin += "0000";
		}
		else if (hexa[i] == '1')
		{
			bin += "0001";
		}
		else if (hexa[i] == '2')
		{
			bin += "0010";
		}
		else if (hexa[i] == '3')
		{
			bin += "0011";
		}
		else if (hexa[i] == '4')
		{
			bin += "0100";
		}
		else if (hexa[i] == '5')
		{
			bin += "0101";
		}
		else if (hexa[i] == '6')
		{
			bin += "0110";
		}
		else if (hexa[i] == '7')
		{
			bin += "0111";
		}
		else if (hexa[i] == '8')
		{
			bin += "1000";
		}
		else if (hexa[i] == '9')
		{
			bin += "1001";
		}
		else if (hexa[i] == 'A' || hexa[i] == 'a')
		{
			bin += "1010";
		}
		else if (hexa[i] == 'B' || hexa[i] == 'b')
		{
			bin += "1011";
		}
		else if (hexa[i] == 'C' || hexa[i] == 'c')
		{
			bin += "1100";
		}
		else if (hexa[i] == 'D' || hexa[i] == 'd')
		{
			bin += "1101";
		}
		else if (hexa[i] == 'E' || hexa[i] == 'e')
		{
			bin += "1110";
		}
		else if (hexa[i] == 'F' || hexa[i] == 'f')
		{
			bin += "1111";
		}
	}
	return bin;
}

string ConvertBintoHexa(string bin)
{
	string ans = "";
	for (int i = 0; i < bin.length(); i += 4)
	{
		int numerical = 0;
		string bincut = bin.substr(i, 4);
		if (bincut[0] == '1')
		{
			numerical += 8;
		}
		if (bincut[1] == '1')
		{
			numerical += 4;
		}
		if (bincut[2] == '1')
		{
			numerical += 2;
		}
		if (bincut[3] == '1')
		{
			numerical += 1;
		}
		if (numerical <= 9)
		{
			ans += (char)(numerical + '0');
		}
		else
		{
			ans += (char)(numerical + 'A' - 10);
		}
	}
	return ans;
}

string XOR(string input1, string input2)
{
	string ans = "";
	for (int i = 0; i < input2.size(); i++)
	{
		if (input1[i] == input2[i])
		{
			ans += "0";
		}
		else
		{
			ans += "1";
		}
	}
	return ans;
}

int permutation64to56[56] = {
57,49,41,33,25,17,9,
1,58,50,42,34,26,18,
10,2,59,51,43,35,27,
19,11,3,60,52,44,36,
63,55,47,39,31,23,15,
7,62,54,46,38,30,22,
14,6,61,53,45,37,29,
21,13,5,28,20,12,4
};

int permutation56to48[48] = {
14,17,11,24,1,5,
3,28,15,6,21,10,
23,19,12,4,26,8,
16,7,27,20,13,2,
41,52,31,37,47,55,
30,40,51,45,33,48,
44,49,39,56,34,53,
46,42,50,36,29,32
};

int inputInitialPermutation[64] = {
58,50,42,34,26,18,10,2,
60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,
64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,
59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,
63,55,47,39,31,23,15,7
};

int input32to48[48] = {
32,1,2,3,4,5,4,5,
6,7,8,9,8,9,10,11,
12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,
22,23,24,25,24,25,26,27,
28,29,28,29,30,31,32,1
};

int sbox[8][4][16] =
{ {
	14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
	0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},
{
	15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
	3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},
{
	10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
	13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},
{
	7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
	13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},
{
	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},
{
	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
	10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},
{
	4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
	13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},
{
	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
	1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
} };

int inputFinalPermutation32to32[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};

int inputInversePermutation[64] = {
40,8,48,16,56,24,64,32,
39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,
37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,
35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,
33,1,41,9,49,17,57,25
};

int main(int argc, char** argv)
{
	string input = argv[1], key = argv[1];
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			input = argv[i + 1];
		}
		if (strcmp(argv[i], "-k") == 0)
		{
			key = argv[i + 1];
		}
	}
	if (input.length() < 18)
	{
		int inputLen = input.length() - 2;
		string tempInput = "0x";
		for (int i = 0; i < 16 - inputLen; i++)
		{
			tempInput += '0';
		}
		for (int i = 0; i < inputLen; i++)
		{
			tempInput += input[2 + i];
		}
		input = tempInput;
	}
	if (key.length() < 18)
	{
		int keyLen = key.length() - 2;
		string tempKey = "0x";
		for (int i = 0; i < 16 - keyLen; i++)
		{
			tempKey += '0';
		}
		for (int i = 0; i < keyLen; i++)
		{
			tempKey += key[2 + i];
		}
		key = tempKey;
	}

	input = input.substr(2, 16);
	key = key.substr(2, 16);

	string BinaryInput = ConvertHexatoBin(input);
	string BinaryKey = ConvertHexatoBin(key);

	string roundKeys[16];
	string BinaryKeyPermuted;

	for (int i = 0; i < 56; i++)
	{
		BinaryKeyPermuted += BinaryKey[permutation64to56[i] - 1];
	}

	string BinaryKeyPermutedLeft = BinaryKeyPermuted.substr(0, 28);
	string BinaryKeyPermutedRight = BinaryKeyPermuted.substr(28, 28);

	for (int i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			//do nothing
		}
		if (i == 1 || i == 8 || i == 15)
		{
			BinaryKeyPermutedLeft = RightShift_1Bit(BinaryKeyPermutedLeft);
			BinaryKeyPermutedRight = RightShift_1Bit(BinaryKeyPermutedRight);
		}
		if (i != 0 && i != 1 && i != 8 && i != 15)
		{
			BinaryKeyPermutedLeft = RightShift_2Bit(BinaryKeyPermutedLeft);
			BinaryKeyPermutedRight = RightShift_2Bit(BinaryKeyPermutedRight);
		}

		string BinaryKeyPermutedShifted = BinaryKeyPermutedLeft + BinaryKeyPermutedRight;
		string RoundKey56to48;

		for (int j = 0; j < 48; j++)
		{
			RoundKey56to48 += BinaryKeyPermutedShifted[permutation56to48[j] - 1];
		}

		roundKeys[i] = RoundKey56to48;
	}
	//Preparation for Keys is Done at this Point



	string inputPermutation;
	for (int i = 0; i < 64; i++)
	{
		inputPermutation += BinaryInput[inputInitialPermutation[i] - 1];
	}

	string InputPermutedLeft = inputPermutation.substr(0, 32);
	string InputPermutedRight = inputPermutation.substr(32, 32);

	for (int i = 0; i < 16; i++)
	{
		string InputPermutedRightExpanded;
		for (int j = 0; j < 48; j++)
		{
			InputPermutedRightExpanded += InputPermutedRight[input32to48[j] - 1];
		}

		string InputPermutedRightXor = XOR(roundKeys[i], InputPermutedRightExpanded);
		string InputPermutedRightResult;
		
		for (int j = 0; j < 8; j++)
		{
			string rowString, colString;
			int row = 0, col = 0;
			rowString = InputPermutedRightXor.substr(j * 6, 1) + InputPermutedRightXor.substr(j * 6 + 5, 1);
			colString = InputPermutedRightXor.substr(j * 6 + 1, 4);

			if (rowString == "11")
			{
				row = 3;
			}
			else if (rowString == "10")
			{
				row = 2;
			}
			else if (rowString == "01")
			{
				row = 1;
			}
			else if (rowString == "00")
			{
				row = 0;
			}

			for (int k = 0; k < 4; k++)
			{
				if (colString[k] == '1')
				{
					col += (int)pow(2, 3 - k);
				}
			}

			int temp = sbox[j][row][col];
			string binarytemp;
			for (int k = 0; k < 4; k++)
			{
				if (temp % 2 == 1)
				{
					binarytemp = '1' + binarytemp;
				}
				else
				{
					binarytemp = '0' + binarytemp;
				}
				temp = temp / 2;
			}
			InputPermutedRightResult += binarytemp;
		}
		string InputDoublePermutedRight;
		for (int j = 0; j < 32; j++)
		{
			InputDoublePermutedRight += InputPermutedRightResult[inputFinalPermutation32to32[j] - 1];
		}

		string InputPermutedLeftXor = XOR(InputDoublePermutedRight, InputPermutedLeft);
		InputPermutedLeft = InputPermutedLeftXor;
		if (i < 15)
		{
			string tempSwitch = InputPermutedRight;
			InputPermutedRight = InputPermutedLeftXor;
			InputPermutedLeft = tempSwitch;
		}
	}

	string InputDoublePermuted = InputPermutedLeft + InputPermutedRight;
	string DecryptResult = "";

	for (int i = 0; i < 64; i++)
	{
		DecryptResult += InputDoublePermuted[inputInversePermutation[i] - 1];
	}

	string DecryptResultHex = ConvertBintoHexa(DecryptResult);

	cout << "0x" << DecryptResultHex << endl;

}
