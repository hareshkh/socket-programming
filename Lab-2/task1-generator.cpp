#include <iostream>
#include <string.h>

using namespace std;

int main() {
	string data, poly;
	cin >> data >> poly;
	int data_size = data.length();
	int poly_size = poly.length();
	string data_copy = data;
	for (int i = 0; i < poly_size - 1; i++) {
		data_copy += '0';
	}

	for (int i = 0; i < data_size; i++) {
		if (data_copy[i] == '0') {
			continue;
		}
		for (int j = 0; j < poly_size; j++) {
			if (data_copy[j + i] == poly[j]) {
				data_copy[j + i] = '0';
			} else {
				data_copy[j + i] = '1';
			}
		}
	}

	string crc = "";
	for (int i = data_size; i < data_size + poly_size - 1; i++) {
		crc += data_copy [i];
	}

	string output = data + crc;
	
	cout << output << endl;
	cout << poly << endl;
	return 0;
}