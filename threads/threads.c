#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* hello(){
	//while(1)
		printf("hellou ourdi.\n");
}
void* haha(){
	//while(1)
		printf("hahahahahaahahaha.\n");
}
void* text(char* text){
	//while(1)
		printf("%s.\n",text);
}
int main (int argv,char* argc[]){
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	int n;
	pthread_create(&t1,NULL,hello,NULL);
	pthread_create(&t2,NULL,haha,NULL);
	pthread_create(&t3,NULL,text("yolo"),NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	while(1)
		n++;
	return 1;
}