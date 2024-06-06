#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255

int main() {
        int msqid;
        char pathname[] = "key.ipc";
        key_t key;
        int len, maxlen;
        struct mymsgbuf {
                long mtype;
                char mtext[81];
        } mybuf;

        if((key = ftok(pathname, 0)) < 0) {
                printf("Не удалось сгенерировать ключ ipc\n");
                exit(-1);
        }
        if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
                printf("Не удалось создать или найти очередь сообщений\n");
                exit(-1);
        }
        while(1) {
                maxlen = 81;
                if((len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0) {
                        printf("Не удалось получить сообщение из очереди\n");
                        exit(-1);
                }
                if((mybuf.mtype == LAST_MESSAGE) < 0) {
                        msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
                        exit(0);
                }
                printf("Тип сообщения %ld, текст: %s\n", mybuf.mtype, mybuf.mtext);
        }
        return 0;
}
