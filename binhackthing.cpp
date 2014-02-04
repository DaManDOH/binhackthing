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
		cout << "binFile.tellg(): " << binFile.tellg() << '\n';
		test = readBigEndianFloat(binFile);
		cout << test << " (0x" << hex << *((unsigned *)&test) << dec << ")\n";
		test = readBigEndianFloat(binFile);
		binFile.close();
		cout << test << " (0x" << hex << *((unsigned *)&test) << dec << ")\n";
		cout << flush;

		unsigned long byteCount = colWidth*rowCount;
		binFile.open(filepath, ios::binary);
		binFile.seekg(8);
		unsigned char * buffPtr = new unsigned char[byteCount];
		binFile.read((char*)buffPtr, byteCount);
		binFile.close();
		cout << "buffPtr[" << byteCount-4 << "]: " << hex << (int)buffPtr[byteCount-4] << '\n';
		cout << "buffPtr[" << byteCount-3 << "]: " << (int)buffPtr[byteCount-3] << '\n';
		cout << "buffPtr[" << byteCount-2 << "]: " << (int)buffPtr[byteCount-2] << '\n';
		cout << "buffPtr[" << byteCount-1 << "]: " << (int)buffPtr[byteCount-1] << dec << '\n';
		vector<unsigned char> dynBuff;
		dynBuff.reserve(byteCount);
		dynBuff.assign(buffPtr, &buffPtr[byteCount]);
		cout << "dynBuff.at(" << byteCount-4 << "): " << hex << (int)dynBuff.at(byteCount-4) << '\n';
		cout << "dynBuff.at(" << byteCount-3 << "): " << (int)dynBuff.at(byteCount-3) << '\n';
		cout << "dynBuff.at(" << byteCount-2 << "): " << (int)dynBuff.at(byteCount-2) << '\n';
		cout << "dynBuff.at(" << byteCount-1 << "): " << (int)dynBuff.at(byteCount-1) << dec << '\n';
		delete [] buffPtr;
	}
	return 0;
}
