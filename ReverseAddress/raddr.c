#include "functions.h"

int main(int argc, char** argv) {
    if (argc == 1) {
        Help();
        return 0;
    } else if (argc != 2 && argc != 3) {
        printf("Usage: %s [OPTION] <hex>", argv[0]);
        return 1;
    }

    int mode = 0;

    if (strcmp(argv[1], "-a") == 0) {
        mode = 1;
    } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        Help();
    } else if (strcmp(argv[1], "-i") == 0) {
        mode = 2;
    } else if (strcmp(argv[1], "-o") == 0) {
        mode = 3;
    } else if (strcmp(argv[1], "-s") == 0) {
        mode = 4;
    } else if (strcmp(argv[1], "--version") == 0) {
        printf("Reverse Hexa Value %s - %s\n", VERSION, DATE);
        printf("  - by Aiden");
    } else {
        printf("%s: Option \'%s\' inconnue (pour plus d'informations \"%s --help\")\n", argv[0], argv[1], argv[0]);
        return 1;
    }

    char message[MESSAGE_SIZE];
    if (!CheckInput(argv[2], strlen(argv[2]), mode, message)) {
        printf("[-] Erreur : Saisie invalide.\n");
        printf("       - Raison : %s\n", message);
        return 1;
    }

    if (mode != 0) {
        ReverseAddress* reverse_address = Create_Reverse_Address(argv[2], strlen(argv[2]));
        reverse_address->Reverse(reverse_address, mode);
        reverse_address->Print(reverse_address);

        free(reverse_address);
    }
    return 0;
}
