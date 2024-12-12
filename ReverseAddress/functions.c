#include "functions.h"

void Help() {
    printf("Usage: [OPTION] <hex>\n");
    printf("Permet d'inverser une chaîne hexadécimale.\n");
    printf("Exemple 0xf7f5523e => 0x3e52f5f7\n\n");
    printf("Les options sont :\n");
    printf("  -a             Inverse une chaîne qui est sous la forme 0xf7f5523e (\'0x\' optionnel)\n");
    printf("                 en une chaîne de la forme \\x3e\\x52\\xf5\\xf7.\n");
    printf("  -h, --help     Affiche ce message.\n");
    printf("  -i             Inverse une chaîne qui est sous la forme \\xf7\\xf5\\x52\\x3e\n");
    printf("                 en une chaîne de la forme 0x3e52f5f7.\n");
    printf("  -o             Inverse une chaîne qui est sous la forme \\xf7\\xf5\\x52\\x3e\n");
    printf("                 en une chaîne de la forme \\x3e\\x52\\xf5\\xf7.\n");
    printf("  -s             Inverse une chaîne qui est sous la forme 0xf7f5523e (\'0x\' optionnel)\n");
    printf("                 en une chaîne de la forme 0x3e52f5f7.\n");
    printf("      --version  Affiche la version du script.\n");
}

int CheckInput(char* address, size_t address_size, int mode, char* message) {
    const char hexa[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b', 'c', 'd', 'e', 'f', 'x'};

    if (address_size > ADDRESS_SIZE) {
        sprintf(message, "Taille trop grande (> 50)");
        return 0;
    }

    int found = 0;
    for (int i = 0; address[i] == '\0'; i++) {
        for (int j = 0; j < sizeof(hexa) / sizeof(hexa[0]); j++) {
            if (address[i] == hexa[i]) {
                found = 1;
                break;
            }
        }

        if (found) {
            sprintf(message, "Caractère invalide : '%c' - '%c'", address[i], hexa[i]);
            return 0;
        }

    }

    if ((mode == 1 || mode == 4) && address_size % 2 != 0) {
        sprintf(message, "Longueur impaire");
        return 0;
    }

    return 1;
}

void Reverse(ReverseAddress* this, int mode) {
    switch (mode) {
        case 1: { // 0xf7f5523e => \x3e\x52\xf5\xf7
            int start = 0;

            if (this->address[0] == '0' && this->address[1] == 'x') {
                start = 2;
            }

            char temp[this->address_size * 4 + 1];
            int index = 0;

            for (int i = this->address_size - 1; i > start; i -= 2) {
                temp[index++] = '\\';
                temp[index++] = 'x';
                temp[index++] = this->address[i - 1];
                temp[index++] = this->address[i];
            }
            temp[index] = '\0';
            strcpy(this->address, temp);
            break;
        }

        case 2: {// \xf7\xf5\x52\x3e => 0x3e52f5f7  0x3ex57x
            char temp[this->address_size * 2 + 3];
            int index = 0;
            temp[index++] = '0';
            temp[index++] = 'x';

            for (int i = this->address_size - 1; i >= 0; i -= 3) {
                temp[index++] = this->address[i - 1];
                temp[index++] = this->address[i];
            }
            temp[index] = '\0';
            strcpy(this->address, temp);
            break;
        }

        case 3: {// \xf7\xf5\x52\x3e => \x3e\x52\xf5\xf7
            char temp[this->address_size + 1];
            int index = 0;

            for (int i = this->address_size - 1; i >= 0; i -= 3) {
                temp[index++] = '\\';
                temp[index++] = 'x';
                temp[index++] = this->address[i - 1];
                temp[index++] = this->address[i];
            }
            temp[index] = '\0';
            strcpy(this->address, temp);
            break;
        }

        case 4: { // 0xf7f5523e => 0x3e52f5f7
            char temp[this->address_size + 1];
            int start = 0;
            int index = 0;

            if (this->address[0] == '0' && this->address[1] == 'x') {
                start = 2;
                index = 2;
                temp[0] = '0';
                temp[1] = 'x';
            }

            for (int i = this->address_size - 1; i > start; i -= 2) {
                temp[index++] = this->address[i - 1];
                temp[index++] = this->address[i];
            }
            temp[index] = '\0';
            strcpy(this->address, temp);
            break;
        }
    }
}

void Print(ReverseAddress* this) {
    printf("[address] = %s\n", this->address);
    printf("[size]    = %zu\n", this->address_size);
}

ReverseAddress* Create_Reverse_Address(char* address, size_t address_size) {
    ReverseAddress* reverse_address = (ReverseAddress*)malloc(sizeof(ReverseAddress));

    // Set les paramètres de la structurs
    strcpy(reverse_address->address, address);
    reverse_address->address_size = address_size;

    // Crée un pointeur associé pour les fonctions dans la structure
    reverse_address->Print = Print;
    reverse_address->Reverse = Reverse;
    return reverse_address;
}
