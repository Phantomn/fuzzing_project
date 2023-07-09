#include <stdio.h>
#include <string.h>


void vuln(){
	char buf[80];
	return read(0, buf, 256);
}

int main(){
	vuln();
	return write(1, "WIN\n", 4);
}