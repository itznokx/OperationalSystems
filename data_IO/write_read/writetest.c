#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    int tty = open("/dev/tty", O_WRONLY);

    const char *str = "Universidade Federal do Ceara\n";

    write(tty, str, 32);

    close(tty);

    return 0;
}
