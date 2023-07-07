#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	char buf[80];

	if(argc < 2){
		printf("usage: ./bof argv\n");
		return 0;
	}

	strcpy(buf, argv[1]);
	printf("%s\n", buf);
	return 0;
}
