#include <stdio.h>
#include <alloc.h>
#undef malloc

void *alloc(size_t size){
	void *new_mem;
	new_mem = malloc(size);
	if(NULL == new_mem){
		printf("Out of memory!\n");
		exit(1);
	}
	return new_mem;

}