#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    int start, end;

    
    if (pipe(pipefd) == -1) {
        perror("error");
        exit(1);
    }

    printf("inicio: ");
    scanf("%d", &start);
    printf("fin: ");
    scanf("%d", &end);

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // hijo
        close(pipefd[0]); 

        int sum = 0;
        for (int i = start; i <= end; i++) {
            sum += i;
        }

        write(pipefd[1], &sum, sizeof(sum));
        close(pipefd[1]); 
        exit(0);
    } else {
        // padre
        close(pipefd[1]); 

        int result;
        // espera al hijo
        wait(NULL);

        
        read(pipefd[0], &result, sizeof(result));
        close(pipefd[0]);

        printf("El resultado de la suma es: %d\n", result);
    }

    return 0;
}
