#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
        int fd[2];
        size_t size;
        char string[] = "Привет, мир!";
        char resstring[13];
        if(pipe(fd) < 0){
                printf("Невозможно создать pipe\n");
                exit(-1);
        }
        size = write(fd[1], string, 13);
        if(size != 13){
                printf("Невозможно записать всю строку\n");
                exit(-1);
        }
        size = read(fd[0], resstring, 13);
        if(size < 0){
                printf("Невозможно прочитать строку\n");
                exit(-1);
        }
        printf("%s\n", resstring);
        if(close(fd[0]) < 0){
                printf("Невозможно закрыть входной поток\n");
        }
        if(close(fd[1]) < 0){
                printf("Невозможно закрыть выходной поток\n");
        }
        return 0;
}

