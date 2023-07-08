#include <stdio.h>

void flag(){
	printf("Exploit Suceess!\n");
}

int main(int argc, char* argv[]){
	int result;
	int x;
	int y;

	y = 0x100000;
	printf("enter an INT\n");
	scanf("%d",&x);
	if(x <= 0){
		printf("no enter a positive number only\n");
		result = -2;
	}else if(x + y <= 152){
		flag();
		result = 2;
	}else{
		printf("sorry!! try again\n");
		result = -1;
	}
	return result;
}