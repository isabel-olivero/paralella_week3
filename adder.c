#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int start = 0;
    int end;
    int pipes[3][2];  
    pid_t pid;
    int i, nproc = 3;

    
    printf("n: ");
    scanf("%d", &end);

    int length = end - start + 1;
    int chunk = length / nproc;
    int remainder = length % nproc;

    for (i = 0; i < nproc; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(1);
        }
        if (pid == 0) {
            // hijo
            close(pipes[i][0]);
            int sub_start = start + i * chunk + (i < remainder ? i : remainder);
            int sub_end   = sub_start + chunk - 1 + (i < remainder ? 1 : 0);

            int sum = 0;
            for (int j = sub_start; j <= sub_end; j++) {
                sum += j;
            }

            write(pipes[i][1], &sum, sizeof(sum));
            close(pipes[i][1]);
            exit(0);
        } else {
            // padre
            close(pipes[i][1]); 
        }
    }

    int total = 0, partial = 0;
    for (i = 0; i < nproc; i++) {
        wait(NULL);
        read(pipes[i][0], &partial, sizeof(partial));
        close(pipes[i][0]);
        total += partial;
    }

    printf("El resultado de la suma es: %d\n", total);

    return 0;
}
