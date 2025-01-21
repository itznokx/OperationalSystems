#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h> // Para constantes do ioctl
#include <sys/ioctl.h>

int main() {

    //df -h /home  :para saber o dispositivo do disco
    const char *nome_disco = "/dev/sda2"; 
    int disco;
    int block_size;

    disco = open(device, O_RDONLY);
    
    ioctl(fd, BLKSSZGET, &block_size);

    off_t blocknum = 2; 
    lseek(fd, blocknum * block_size, SEEK_SET);
    
    unsigned char buffer[block_size];

    read(fd, buffer, block_size);

    for (int i = 0; i < block_size; i++)
        printf("%02x ", buffer[i]);

    close(fd);
    
    return 0;
}
