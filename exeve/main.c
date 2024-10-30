#include <stdio.h>
#include <unistd.h>

int main (int argc,char* argv[]){
	pid_t pid = fork();
	if (pid < 0){
		printf("Falha na criação de processo filho.\n");
		return 0;
	}
	if (pid == 0){
		printf("Processo filho.\n");
		char *args[] = {"./fatorial","5",NULL};
		char *env_arg[] = {NULL};
		execve(args[0],args,env_arg);
		perror("execve");
		printf("Final programa filho\n");
	}
	if (pid >0){
		printf("Processo Pai.\n");
	}
	return 1;
}