#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int tty;
    char c;

    tty = open("/dev/tty", O_RDONLY);

    while (1) {
       read(tty, &c, 1);
       printf("%c", c);
    }

    close(tty);
    return 0;
}
	