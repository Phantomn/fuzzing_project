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

전처리 - 어떤종류의 인풋을 만들어 낼 것인가
