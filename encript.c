#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void caesar(char *text, int shift, int decrypt) {
    int s = ((shift % 26) + 26) % 26; // normalizar a 0–25
    if (decrypt) s = (26 - s) % 26;   // invertir el desplazamiento

    for (int i = 0; text[i]; i++) {
        unsigned char c = text[i];

        if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + s) % 26;
        } else if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + s) % 26;
        }
        text[i] = c; // otros caracteres (espacios, ñ, acentos, etc.) no cambian
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s [-d] <rotacion> <texto...>\n", argv[0]);
        return 1;
    }

    int decrypt = 0;
    int shift_arg = 1;

    // ¿Primer argumento es -d?
    if (strcmp(argv[1], "-d") == 0) {
        decrypt = 1;
        shift_arg = 2;
        if (argc < 4) {
            fprintf(stderr, "Uso: %s [-d] <rotacion> <texto...>\n", argv[0]);
            return 1;
        }
    }

    int shift = atoi(argv[shift_arg]);

    // Construir el texto completo
    char text[1024] = "";
    strcpy(text, argv[shift_arg + 1]);
    for (int i = shift_arg + 2; i < argc; i++) {
        strcat(text, " ");
        strcat(text, argv[i]);
    }

    caesar(text, shift, decrypt);
    printf("%s\n", text);
    return 0;
}
