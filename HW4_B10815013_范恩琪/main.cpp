#include<iostream>
#include<string>
#include<cmath>
#include<stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;

int gcd(int a, int b) {
	int temp;
	while (1) {
		temp = a % b;
		if (temp == 0)return b;
		a = b;
		b = temp;
	}
}

int main(int argc, char** argv) {
	string method, key, met, msg;
	//cin >> input;
	//cin >> key;
	//method = argv[2];
	//key = argv[4];

	int p, q, phi, N, e, d;

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			method = argv[i];
			met = "keyGen";

			p = rand();
			q = rand();

			N = p * q;
			phi = (p - 1) * (q - 1);
			e = rand();
			int temp;
			while (e < phi) {
				temp = gcd(e, phi);
				if (temp == 1)break;
				else e++;
			}
			d = fmod((1 / e), phi);

			cout << "p=" << p << endl;
			cout << "q=" << q << endl;
			cout << "N=" << N << endl;
			cout << "phi=" << phi << endl;
			cout << "e=" << e << endl;
			cout << "d=" << d << endl;
		}
		if (strcmp(argv[i], "-e") == 0) {
			method = argv[i];
			met = "encrypt";
			msg = argv[i + 1];
			N = atoi(argv[i + 2]);
			e = atoi(argv[i + 3]);

			int temp = pow(atoi(msg.c_str()), e);
			temp = fmod(temp, N);
			cout << temp;
		}
		if (strcmp(argv[i], "-d") == 0) {
			method = argv[i];
			met = "decrypt";
			msg = argv[i + 1];
			N = atoi(argv[i + 2]);
			d = atoi(argv[i + 3]);

			int temp = pow(atoi(msg.c_str()), d);
			temp = fmod(temp, N);
			cout << temp;
		}
		if (strcmp(argv[i], "-CRT") == 0) {
			method = argv[i];
			met = "crt";
			msg = argv[i + 1];
			p = atoi(argv[i + 2]);
			q = atoi(argv[i + 3]);
			d = atoi(argv[i + 4]);
		}
	}

	return 0;
}