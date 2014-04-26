#include "Buffer.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	Buffer*  buffer;

	buffer = new Buffer("/home/su/test.cpp");
	cout << "Buffer liest: " << buffer->getChar();
	cout << "Buffer liest: " << buffer->getChar();
	cout << "Buffer liest: " << buffer->getChar();
	cout << "Buffer liest: " << buffer->getChar();
	cout << "Buffer liest: " << buffer->getChar();
	cout << "Buffer liest: " << buffer->getChar();
	cout << "Buffer liest: " << buffer->getChar();
	// scanner "/user/su/Dekstop/einlesen.txt" "ausgabe.txt"

}
