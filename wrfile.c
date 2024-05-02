#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
        int fd;
        size_t size;
        char string[] = "Gr. 3.008.2.23";
        if((fd = open("wrfile.txt", O_WRONLY|O_CREAT, 0666))< 0) {
                printf("Ошибка при открытии файла на запись\n");
                exit(-1);
        }
        size = write(fd, string, 14);
        if(size !=14) {
                printf("Не удалось записать 14 байт в файл\n");
                exit(-1);
        }
        else printf("Строка записана в файл\n");
        if (close(fd) < 0) {
                printf("Не получилось закрыть файл\n");
                exit(-1);
        }
        return 0;
}
