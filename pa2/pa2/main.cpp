#include <iostream>
#include <fstream>
#include "HCTree.hpp"
#include "HCNode.hpp"

int main() {
	ifstream in;
	in.seekg(0, ios_base::beg);
	byte symbol;
	vector<int> v(256, 0);
	in.open("test.txt", ios::binary);
	while (1) {
		symbol = in.get();
		if (in.eof()) break;
		v[symbol]++;
	}
	HCTree t;
	t.build(v);
	t.printAll();
	in.close();
	return 0;
}
