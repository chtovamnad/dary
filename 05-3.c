#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
        int fd[2], result;
        size_t size;
        char resstring[13];
        if(pipe(fd) < 0){
                printf("Невозможно создать pipe\n");
                exit(-1);
        }
        result = fork();
        if(result < 0){
                printf("Невозможно создать процесс-ребенок\n");
                exit(-1);
        }
        else if(result > 0) {
        close(fd[0]);
        size = write(fd[1], "Привет, мир!", 13);
        if(size != 13){
                printf("Невозможно записать всю строку\n");
                exit(-1);
        }
        close(fd[1]);
        printf("Родитель прекращает работу\n");
        } else {
        close(fd[1]);
        size = read(fd[0], resstring, 13);
        if(size < 0){
                printf("Невозможно прочитать строку\n");
                exit(-1);
        }
        printf("%s\n", resstring);
        close(fd[0]);
        }
	return 0;
}
