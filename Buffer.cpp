#include "Buffer.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Buffer::Buffer(char *filePath) {
// Groesse des Buffers festgelegt und zwei Buffer werden erstellt
	BufferSize = 1024;
	char *FirstBuffer;
	char *SecondBuffer;

	posix_memalign((void**) &FirstBuffer, 1024, BufferSize);
	posix_memalign((void**) &SecondBuffer, 1024, BufferSize);
    path = filePath;
	file = open(path, O_RDONLY | O_DIRECT);

// Anfang des Buffers und wie man daraus liest und schreibt
	readForward = 0;
	writeForward = 0;
//Eingang des ersten Buffers
	entryLeft = current = next = &FirstBuffer[0];
//Eingang des Zweiten Buffers
	entryRight = &SecondBuffer[0];
//Ende der datei und erstellte neue Datei
	isEOF = false;
//ist da
	isChar = true;
	cout << "FirstBUFFER zeigt momentan auf Speicher: " << hex
			<< ((void*) FirstBuffer) << endl;
}

Buffer::~Buffer() {
	delete FirstBuffer;
	delete SecondBuffer;
	close(file);
};
char Buffer::getChar() {
//Das nächste Zeichen gesetzt als aktueles Zeichen nehmen
	current = next;
//Prüft ob die Datei offen ist oder schon erstellt wurde
	if (!isOpen) {
		BufferOpen();
		BufferFill();
	}
//wenn es die ende der Datei ist dann soll
//es zum letzter Zeichen zurückkehren
	if (*current == eof) {
		isEOF = true;
		close(readForward);
		return *current;
	}
// fängt Fehler ab wenn die current Zeichen Außerhalb des Speichers ist -First Buffer
if(true){
// wenn man sich im letzte Zeichen befindet
	if (current == entryRight + BufferSize - 1) {
		isChar == true;
//erste Buffer wird befüllt
		BufferFill();
		next = entryLeft;
		return *current;
	}
	if (current == entryLeft + BufferSize - 1) {
		isChar == false;
//zweite Buffer wird befüllt
		BufferFill();
		next = entryRight;
		return *current;
	}
//Zeichen ist nicht am Ende des Buffers
	next++;
	return *current;
}
cout << endl << "!!! ZEIGER AUSERHALB DES SPEICHERBEREICHES !!!" << endl;
	return '\n';
};
void Buffer::ungetChar() {
// current steht im zweiten Buffer
	if (current == entryRight) {
		next = &SecondBuffer[BufferSize - 1];
		isChar = true;
//current steht in ersten Buffer
	} else if (current == entryLeft) {
		next = &SecondBuffer[BufferSize - 1];
		isChar = false;
	} else {
//current steht im Speicher
		next--;
	}
	current = next;
};
void Buffer :: BufferFill(){
	if (isChar) {
			read(readForward, entryLeft, BufferSize);
		} else {
			read(readForward, entryRight,BufferSize);
		}
}
void Buffer :: BufferOpen(){
	cout << endl << "in Buffer::openFile()" << endl;
		readForward = open(path, O_DIRECT);
}

