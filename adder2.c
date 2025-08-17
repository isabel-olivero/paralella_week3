#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n, i;
    int nproc = 3;  // número fijo de procesos hijos
    int *nums;

    printf("Cantidad de números: ");
    scanf("%d", &n);

    nums = malloc(n * sizeof(int));
    if (nums == NULL) {
        perror("malloc");
        exit(1);
    }

    printf("Ingrese los números:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    int pipes[nproc][2];
    int chunk = n / nproc;
    int remainder = n % nproc;

    for (i = 0; i < nproc; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            free(nums);
            exit(1);
        }
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            free(nums);
            exit(1);
        }
        if (pid == 0) {
            // hijo
            close(pipes[i][0]);

            int start = i * chunk + (i < remainder ? i : remainder);
            int end   = start + chunk - 1 + (i < remainder ? 1 : 0);

            int sum = 0;
            for (int j = start; j <= end && j < n; j++) {
                sum += nums[j];
            }

            write(pipes[i][1], &sum, sizeof(sum));
            close(pipes[i][1]);
            free(nums);
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

    free(nums);
    return 0;
}
