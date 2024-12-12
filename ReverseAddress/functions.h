#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ADDRESS_SIZE 50
#define MESSAGE_SIZE 30
#define VERSION "V 0.3"
#define DATE "22/09/2024"


typedef struct ReverseAddress {
    char address[ADDRESS_SIZE];
    size_t address_size;

    void (*Reverse)(struct ReverseAddress*, int);
    void (*Print)(struct ReverseAddress*);
} ReverseAddress;

int CheckInput(char* address, size_t address_size, int mode, char* message);
ReverseAddress* Create_Reverse_Address();
void Help();
