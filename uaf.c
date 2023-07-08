#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct {
    char name[10];
    void (*print)(void*);
} test;
 
typedef struct {
    char name[128];
} string;
 
void printName(test* t) {     printf("%s\n",t->name);}
 
void shell(void) {    printf("This is Shell\n");}
 
int main(int argc, char* argv[])
{
    test* t1;
    string* s1;
 
    /* malloc and free */
    t1 = malloc(256);
 
    strcpy(t1->name, "DOG");
    t1->print = (void*)printName;
    t1->print(t1);
    free(t1);
 
    /* malloc */
    s1 = malloc(256);

    strncpy(s1->name, argv[1], 128);
    /* use */
    t1->print(t1);
 
    return 0;
}