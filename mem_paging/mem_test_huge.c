#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>

#define NUM_ALLOCS 100
#define ALLOC_SIZE (2*1048576)

void* allocmem (size_t size){
	void* ptr = mmap(	NULL,
						size,
						PROT_READ | PROT_WRITE,
						MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,
						-1,
						0);
	if (ptr == MAP_FAILED){
		perror ("Erro ao alocar páginas");
		exit(1);
	}
	return ptr;
}
void fillmem (void* ptr,size_t size) {
	memset(ptr,0,size);
}
int main (){
	struct timeval start,end;
	long seconds,useconds;

	void *allocs[NUM_ALLOCS];

	gettimeofday(&start,NULL);

	for (int i=0; i<NUM_ALLOCS;i++){
		allocs[i] = allocmem(ALLOC_SIZE);
		if (allocs[i]){ 
			perror("Erro ao alocar.\n");
			exit(1);
		}
		fillmem(allocs[i],ALLOC_SIZE);
	}
	gettimeofday (&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	double total = seconds + useconds/1000000.0;

	printf("Tempo de execução: %f.6f segundos\n",total);

	for (int i=0; i<NUM_ALLOCS;i++){
		munmap(allocs[i],ALLOC_SIZE);
	}
	return 0;
}