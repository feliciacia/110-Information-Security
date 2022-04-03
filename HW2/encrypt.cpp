#include<iostream>
#include<string>
#include<cmath>
using namespace std;

string hextoBinary(string input) {
	string res = "";
	for (int i = 0; i < input.length(); i++) {
		switch (input[i]) {
		case'0':res += "0000"; break;
		case'1':res += "0001"; break;
		case'2':res += "0010"; break;
		case'3':res += "0011"; break;
		case'4':res += "0100"; break;
		case'5':res += "0101"; break;
		case'6':res += "0110"; break;
		case'7':res += "0111"; break;
		case'8':res += "1000"; break;
		case'9':res += "1001"; break;
		case'a':
		case'A':
			res += "1010"; break;
		case'b':
		case'B':
			res += "1011"; break;
		case'c':
		case'C':
			res += "1100"; break;
		case'd':
		case'D':
			res += "1101"; break;
		case'e':
		case'E':
			res += "1110"; break;
		case'f':
		case'F':
			res += "1111"; break;
		}
	}
	return res;
}

string shift1(string key) {
	string shifted = "";
	for (int i = 1; i < 28; i++) {
		shifted += key[i];
	}
	shifted += key[0];
	return shifted;
}

string shift2(string key) {
	string shifted = "";
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 28; j++) {
			shifted += key[j];
		}
		shifted += key[0];
		key = shifted;
		shifted = "";
	}
	return key;
}

string Xor(string a, string b) {
	string result = "";
	int size = b.size();
	for (int i = 0; i < size; i++) {
		if (a[i] != b[i]) {
			result += "1";
		}
		else {
			result += "0";
		}
	}
	return result;
}

string dectobin(int dec) {
	string bin;
	while (dec != 0) {
		if (dec % 2 == 0)bin = "0" + bin;
		else bin = "1" + bin;
		dec /= 2;
	}
	while (bin.length() < 4)bin = "0" + bin;
	return bin;
}

int main(int argc, char** argv) {
	string input, key;
	//cin >> input;
	//cin >> key;
	input = argv[2];
	key = argv[4];
	input = input.substr(2, 16);
	key = key.substr(2, 16);
	string inputBin = hextoBinary(input);
	string keyBin = hextoBinary(key);

	//keyBin = "1010101010111011000010010001100000100111001101101100110011011101";
	//inputBin = "1010101111001101111001101010101111001101000100110010010100110110";

	//generate keys
	int pc1[56] = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4
	};

	int pc2[48] = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32
	};
	
	string Kn[16]; //round keys
	string permutated_key;
	for (int i = 0; i < 56; i++) {
		permutated_key += keyBin[pc1[i] - 1];
	}

	string leftKey = permutated_key.substr(0, 28);
	string rightKey = permutated_key.substr(28, 28);

	for (int i = 0; i < 16; i++) {
		if (i == 0 || i == 1 || i == 8 || i == 15) {
			leftKey = shift1(leftKey);
			rightKey = shift1(rightKey);
		}
		else {
			leftKey = shift2(leftKey);
			rightKey = shift2(rightKey);
		}

		//combine key
		string combine = leftKey + rightKey;
		string roundKey;
		for (int j = 0; j < 48; j++) {
			roundKey += combine[pc2[j] - 1];
		}
		Kn[i] = roundKey;
	}

	//des encrypt
	int ip[64] = {
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
	};

	int expansion[48] = {
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

	int permutation[32] = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25
	};

	int ip_inverse[64] = {
	40,8,48,16,56,24,64,32,
	39,7,47,15,55,23,63,31,
	38,6,46,14,54,22,62,30,
	37,5,45,13,53,21,61,29,
	36,4,44,12,52,20,60,28,
	35,3,43,11,51,19,59,27,
	34,2,42,10,50,18,58,26,
	33,1,41,9,49,17,57,25
	};
	string per;
	for (int i = 0; i < 64; i++)per += inputBin[ip[i] - 1];

	string left = per.substr(0, 32);
	string right = per.substr(32, 32);

	for (int i = 0; i < 16; i++) {
		string rightexp = "";
		for (int j = 0; j < 48; j++) {
			rightexp += right[expansion[j] - 1];
		}
		string xorr;
		string res = "";
		xorr = Xor(Kn[i], rightexp);
		for (int j = 0; j < 8; j++) {
			string row1, col1;
			int row = 0, col = 0;
			row1 = xorr.substr(j * 6, 1) + xorr.substr(j * 6 + 5, 1);
			int cnt = 0;
			for (int k = row1.length() - 1; k >= 0; k--){
				if (row1[k] == '1') {
					row += pow(2, cnt);
				}
				cnt++;
			}
			col1 = xorr.substr(j * 6 + 1, 1) + xorr.substr(j * 6 + 2, 1) + xorr.substr(j * 6 + 3, 1) + xorr.substr(j * 6 + 4, 1);
			cnt = 0;
			for (int k = col1.length() - 1; k >= 0; k--) {
				if (col1[k] == '1') {
					col += pow(2, cnt);
				}
				cnt++;
			}
			int temp = sbox[j][row][col];
			res += dectobin(temp);
		}
		string per2;
		for (int j = 0; j < 32; j++) {
			per2 += res[permutation[j] - 1];
		}
		xorr = Xor(per2, left);
		left = xorr;
		if (i < 15) {
			string temp = right;
			right = xorr;
			left = temp;
		}
	}
	//combine text
	string combineText = left + right;
	string cipherRes = "";
	for (int i = 0; i < 64; i++) {
		cipherRes += combineText[ip_inverse[i] - 1];
	}
	//cout << cipherRes;

	//convert binary to hexadecimal
	cout << "0x";
	int len = cipherRes.length();
	for (int i = 0; i < cipherRes.length(); i+=4) {
		string bin = cipherRes.substr(i, 4);
		int binInt = stoi(bin);
		int rem, dec = 0;
		int j = 1;
		int hex[1000];
		while (binInt > 0) {
			rem = binInt % 2;
			dec += rem * j;
			j *= 2;
			binInt /= 10;
		}
		j = 0;
		while (dec != 0) {
			hex[j] = dec % 16;
			dec /= 16;
			j++;
		}
		if (bin == "0000")cout << "0";
		for (int k = j - 1; k >= 0; k--) {
			if (hex[k] > 9)cout << (char)(hex[k] + 55);
			else cout << hex[k];
		}
	}
	return 0;
}
