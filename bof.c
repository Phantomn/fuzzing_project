#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int vuln(){
	char buf[80];
	return read(0, &buf, 256);
}

int main(int argc, char** argv) {
	vuln();
	return write(1, "WIN\n", 4);
}
