#include <iostream>
#include <string>
#include <vector>

void caesar(std::string &text, int shift, bool decrypt) {
    int s = ((shift % 26) + 26) % 26; // normalizar a 0–25
    if (decrypt) s = (26 - s) % 26;   // invertir desplazamiento

    for (char &c : text) {
        if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' + s) % 26;
        } else if (c >= 'a' && c <= 'z') {
            c = 'a' + (c - 'a' + s) % 26;
        }
        // otros caracteres no cambian
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Uso: " << argv[0] << " [-d] <rotacion> <texto...>\n";
        return 1;
    }

    bool decrypt = false;
    int shift_arg = 1;

    // ¿Primer argumento es -d?
    if (std::string(argv[1]) == "-d") {
        decrypt = true;
        shift_arg = 2;
        if (argc < 4) {
            std::cerr << "Uso: " << argv[0] << " [-d] <rotacion> <texto...>\n";
            return 1;
        }
    }

    int shift = std::stoi(argv[shift_arg]);

    // Unir el resto de los argumentos en un solo string
    std::string text;
    for (int i = shift_arg + 1; i < argc; i++) {
        if (!text.empty()) text += " ";
        text += argv[i];
    }

    caesar(text, shift, decrypt);
    std::cout << text << "\n";

    return 0;
}
