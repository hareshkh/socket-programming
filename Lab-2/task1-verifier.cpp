#include <iostream>
#include <string.h>
using namespace std;

int main() {
	string data, poly;
	cin >> data >> poly;
	int data_size = data.length();
	int poly_size = poly.length();

	for (int i = 0; i < data_size - poly_size + 1; i++) {
		if (data[i] == '0') {
			continue;
		}
		for (int j = 0; j < poly_size; j++) {
			if (data[j + i] == poly[j]) {
				data[j + i] = '0';
			} else {
				data[j + i] = '1';
			}
		}
	}

	for (int i = 0; i < data_size; i++) {
		if (data[i] == '1') {
			cout << "Wrong" << endl;
			return 1;
		}
	}
	cout << "Right" << endl;
	return 0;
}