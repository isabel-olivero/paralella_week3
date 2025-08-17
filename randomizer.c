#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int n, i = 0;

    printf("n: ");
    scanf("%d", &n);

    srand((unsigned int)time(NULL));

    while (i < n) {
        printf("%d\n", rand());
        i++;
    }

    return 0;
}
