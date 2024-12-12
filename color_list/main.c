#include "functions.h"

int main(void) {
    printf("- Standard 16 colors\n");
    printf("    Formule : \\e[0;XXm or \\033[0;XXm or \\x1B[0;XXm for theses XX values :\n|");
    DisplaySimple(30, 37);
    DisplaySimple(90, 97);
    printf("\n\n");

    printf("- RGB Colors\n");
    printf("    Formule : \\e[38;2;XX;YY;ZZm or \\033[38;2;XX;YY;ZZm or \\x1B[38;2;XX;YY;ZZm for theses XX, YY, ZZ values :\n");
    DisplayRGB();
    printf("- Change the font\n");
    printf("    Formule : \\e[Y;XXm or \\033[Y;XXm or \\x1B[Y;XXm with XX that correspond to standard color or RGB color and Y for theses values :\n");
    printf("| A | B | C | D | E | F | G | H | I | J |\n|");
    DisplayFont(0, 9);
    printf("\n\n\033[3;37mLegend :\n");
    printf("\t- A : Reset all attributs\n");
    printf("\t- B : Bold text\n");
    printf("\t- C : Low intensity\n");
    printf("\t- D : Italicize text\n");
    printf("\t- E : Underline text\n");
    printf("\t- F : Make text flash\n");
    printf("\t- G : Make text flash\n");
    printf("\t- H : Invert text\n");
    printf("\t- I : Invisible text\n");
    printf("\t- J : Cross out text\033[0m\n");
    return 0;
}
