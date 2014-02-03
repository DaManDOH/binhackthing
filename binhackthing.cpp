#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

float readBigEndianFloat(ifstream & input) {
	char retval[4], buff[4];
	input.read(buff, 4);
	retval[0] = buff[3];
	retval[1] = buff[2];
	retval[2] = buff[1];
	retval[3] = buff[0];
	return *((float*)retval);
}

unsigned int readBigEndianUInt(ifstream & input) {
	char retval[4], buff[4];
	input.read(buff, 4);
	retval[0] = buff[3];
	retval[1] = buff[2];
	retval[2] = buff[1];
	retval[3] = buff[0];
	return *((unsigned int*)retval);
}

int main( int argc, char* argv[] ) {
	if (argc > 1) {
		string filepath = argv[1];
		unsigned int colWidth, rowCount;
		float test;
		vector<float> allFloats;
		ifstream binFile(filepath, ios::binary);
		colWidth = readBigEndianUInt(binFile);
		rowCount = readBigEndianUInt(binFile);
		/*
		for (unsigned int i = 0; i < rowCount; i++) {
			test = readBigEndianFloat(binFile);
			cout << test << '\n';
		}
		*/
		binFile.close();
		binFile.open(filepath, ios::ate | ios::binary);
		binFile.seekg(-8, binFile.end);
		test = readBigEndianFloat(binFile);
		cout << test << " (0x" << hex << *((unsigned *)&test) << dec << ")\n";
		test = readBigEndianFloat(binFile);
		cout << test << " (0x" << hex << *((unsigned *)&test) << dec << ")\n";
		binFile.close();
		cout << flush;
	}
	return 0;
}
