#include "analista.h"

sem_t* sem_block;

// 1024 buffer size
#define ALLOC_SIZE 1024
#define MAX_PRINT 10
#define nullptr NULL

void start_analist(){
	remove("pidanalista.txt");
	pid_t pid = getpid();
	FILE* pidanalista = fopen("pidanalista.txt","w+");
	if (!pidanalista){
		perror("pidanalista");
	}
	fprintf(pidanalista,"%d",pid);
	fclose(pidanalista);
}
int print_pids(int PID_MAX_PRINT){
    FILE* lng = fopen("lng.txt","r+");
    if (!lng) return 0; // Se não existe arquivo, retorna 0
    int pids[MAX_PRINT];
    int count = 0;
    while(count < PID_MAX_PRINT && fscanf(lng, "%d", &pids[count])==1) {
        printf("PID: %i\n",pids[count]);
        count++;
    }
    fclose(lng); // Fechar arquivo antes de retornar
    return count;
}

int main() {
    start_analist();
    sem_block = sem_open("/sem_block", O_RDWR);
    if (sem_block == SEM_FAILED) {
        sem_block = sem_open("/sem_block", O_CREAT, 0644, 1);
    }
    raise(SIGSTOP);
    while(1) {
        sem_wait(sem_block);
        // Verifica se LNG existe
        FILE *lng = fopen("lng.txt", "r");
        if (!lng) {
            sem_post(sem_block);
            raise(SIGSTOP);
            continue;
        }
        fclose(lng);

        int count = print_pids(10);
        if (count == 0) {
            sem_post(sem_block);
            raise(SIGSTOP);
            continue;
        }

        lng = fopen("lng.txt","r");
        int pidsArray[ALLOC_SIZE];
        int total = 0;
        int aux;
        int skip = count;
        while(fscanf(lng,"%d",&aux)==1) {
            if(skip>0) {
                skip--;
                continue;
            }
            pidsArray[total++]=aux;
        }
        fclose(lng);

        // Reescrever o arquivo sem os primeiros 'count'
        lng = fopen("lng.txt","w");
        for (int i=0; i<total; i++) {
            fprintf(lng,"%d\n",pidsArray[i]);
        }
        fclose(lng);

        sem_post(sem_block);
        // Volta a dormir
        raise(SIGSTOP);
    }
    return 0;
}
