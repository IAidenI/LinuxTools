#include "functions.h"

void DisplaySimple(const unsigned int index_mini, const unsigned int index_max) {
    for (unsigned int i = index_mini; i <= index_max; i++) {
        printf("\033[0;%dm%*.d\033[0m|", i, WIDTH, i);
    }
}

void DisplayRGB() {
    for (unsigned int i = 0; i < 256; i += 51) {
        for (unsigned int j = 0; j < 256; j += 51) {
            if (j == 0) {
                printf("|");
            }
            for (unsigned int k = 0; k < 256; k += 51) {
                if (k == 0 && j != 0) {
                    printf("|");
		}
                printf("\033[38;2;%d;%d;%dm%3d;%3d;%3d\033[0m|", i, j, k, i, j, k);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void DisplayFont(const unsigned int index_mini, const unsigned int index_max) {
    for (unsigned int i = index_mini; i <= index_max; i++) {
        printf("\033[%d;37m%*.d\033[0m|", i, WIDTH_FONT, i);
    }
}
