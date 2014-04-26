
#ifndef BUFFER_H_
#define BUFFER_H_

class Buffer {
public:
	Buffer(char *path);
	virtual ~Buffer();
	char getChar();
	void ungetChar();


private :
	 char* path;
	 int file;
	 void BufferFill();
     void BufferOpen ();
     void BufferClose ();
     unsigned int BufferSize;
     char *FirstBuffer;
     char *SecondBuffer;
     int readForward;
     int writeForward;
     char *current;
     char *next;
     char *entryRight;
     char *entryLeft;
     bool isChar;
     bool isEOF;
     int eof;
     bool isOpen;



};

#endif /* BUFFER_H_ */
