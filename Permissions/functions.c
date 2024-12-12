#include "functions.h"

void InputColor(const char input[MAX_BUFFER], char newInput[MAX_BUFFER_COLOR], const Colors color) {
	char *current_pos = newInput;

	for (unsigned int i = 0; i < MAX_BUFFER - 1; i++) {
		if (input[i] == '-') {
			current_pos += sprintf(current_pos, "%s%c", color.RESET, input[i]);
		} else if (input[i] == 'd') {
			current_pos += sprintf(current_pos, "%s%c%s", color.DARK_BLUE, input[i], color.RESET);
		} else if (input[i] == 'l') {
			current_pos += sprintf(current_pos, "%s%c%s", color.PINK, input[i], color.RESET);
		} else if (input[i] == 'r') {
			current_pos += sprintf(current_pos, "%s%c%s", color.RED, input[i], color.RESET);
		} else if (input[i] == 'w') {
			current_pos += sprintf(current_pos, "%s%c%s", color.YELLOW, input[i], color.RESET);
		} else if (input[i] == 'x') {
			current_pos += sprintf(current_pos, "%s%c%s", color.BLUE, input[i], color.RESET);
		} else {
			(input[0] != '#') ? (current_pos += sprintf(current_pos, "%s%c%s", color.RESET, input[i], color.RESET)) : (void)0;
		}
	}
}

void Help(const char* buffer) {
	printf("Usage: %s [OPTION]\n", buffer);
	printf("Permet d'avoir toutes les informations sur les permissions UNIX.\n\n");
	printf("Les options sont :\n");
	printf("  -c, --cheat-sheets  Affiche toutes informations importantes à savoir sur\n");
	printf("                      les permissions UNIX, \n");
	printf("  -h, --help          Affiche ce message\n");
	printf("  -i, --interactive   Rend ce script interactif, avec un menu\n");
	printf("  -o                  Affiche la valeur octal du file mode passé. Permet notament\n");
	printf("                      de s'en servir pour chmod <valeur octal> <script>\n");
	printf("  -r <file mode>      Permet de ressortir toutes les informations possible\n");
	printf("                      a partir de l'argument <file mode> (ex : -rwxr-xr-x)\n");
	printf("                      Il est possible de ne pas spécifier le type de\n");
	printf("                      fichier. (par exemple rwxr-xr-x)\n");
	printf("      --version       Affiche la version du script\n");
}

void ModeToOctal(const char buffer[MAX_BUFFER], const Colors color) {
	char tab[MAX_MODE][MAX_MODE];
	char octal[MAX_MODE] = "";

	strncpy(tab[0], buffer, 1);
	tab[0][1] = '\0';

	strncpy(tab[1], buffer + 1, 3);
	tab[1][3] = '\0';

	strncpy(tab[2], buffer + 4, 3);
	tab[2][3] = '\0';

	strncpy(tab[3], buffer + 7, 3);
	tab[3][3] = '\0';

	for (unsigned int i = 1; i < MAX_MODE; i++) {
		if (strcmp(tab[i], "---") == 0) {
			strcat(octal, "0");
		} else if (strcmp(tab[i], "--x") == 0) {
			strcat(octal, "1");
		} else if (strcmp(tab[i], "-w-") == 0) {
			strcat(octal, "2");
		} else if (strcmp(tab[i], "-wx") == 0) {
			strcat(octal, "3");
		} else if (strcmp(tab[i], "r--") == 0) {
			strcat(octal, "4");
		} else if (strcmp(tab[i], "r-x") == 0) {
			strcat(octal, "5");
		} else if (strcmp(tab[i], "rw-") == 0) {
			strcat(octal, "6");
		} else if (strcmp(tab[i], "rwx") == 0) {
			strcat(octal, "7");
		} else {
			printf("%s[-] Erreur : Format fournit incorrect.%s\n", color.RED_ERROR, color.RESET);
			return;
		}
	}
	printf("%s[ ] File mode en octal : %s%s%s\n", color.GREY_PROMPT, color.GREEN, octal, color.RESET);
}

void ModeToOctalVerbose(const char buffer[MAX_BUFFER], const Colors color) {
	char bufferColor[MAX_BUFFER_COLOR];
	char tab[MAX_MODE][MAX_MODE];
	char octal[MAX_MODE] = "";
	char binary[MAX_BUFFER + 4] = "";
	char type[MAX_TYPE] = "";
	char rights[3][54];

	strncpy(tab[0], buffer, 1);
	tab[0][1] = '\0';

	strncpy(tab[1], buffer + 1, 3);
	tab[1][3] = '\0';

	strncpy(tab[2], buffer + 4, 3);
	tab[2][3] = '\0';

	strncpy(tab[3], buffer + 7, 3);
	tab[3][3] = '\0';

	if (strcmp(tab[0], "d") == 0) {
		snprintf(type, 42, "Type : %sDossier%s", color.GREEN, color.RESET);
	} else if (strcmp(tab[0], "l") == 0) {
		snprintf(type, 50, "Type : %sLien Symbolique%s", color.GREEN, color.RESET);
	} else if (strcmp(tab[0], "-") == 0) {
		snprintf(type, 42, "Type : %sFichier%s", color.GREEN, color.RESET);
	} else {
		snprintf(type, 49, "Type : %sFormat Inconnu%s", color.GREEN, color.RESET);
	}

	unsigned int pos = 0;
	for (unsigned int i = 1; i < MAX_MODE; i++) {
		if (strcmp(tab[i], "---") == 0) {
			strcat(binary, "000 ");
			strcat(octal, "0");
			strcpy(rights[pos++], "Aucun droits.");
		} else if (strcmp(tab[i], "--x") == 0) {
			strcat(binary, "001 ");
			strcat(octal, "1");
			strcpy(rights[pos++], "Exécution uniquement.");
		} else if (strcmp(tab[i], "-w-") == 0) {
			strcat(binary, "010 ");
			strcat(octal, "2");
			strcpy(rights[pos++], "Ecriture uniquement.");
		} else if (strcmp(tab[i], "-wx") == 0) {
			strcat(binary, "011 ");
			strcat(octal, "3");
			strcpy(rights[pos++], "Ecriture et exécution.");
		} else if (strcmp(tab[i], "r--") == 0) {
			strcat(binary, "100 ");
			strcat(octal, "4");
			strcpy(rights[pos++], "Lecture uniquement");
		} else if (strcmp(tab[i], "r-x") == 0) {
			strcat(binary, "101 ");
			strcat(octal, "5");
			strcpy(rights[pos++], "Lecture et exécution.");
		} else if (strcmp(tab[i], "rw-") == 0) {
			strcat(binary, "110 ");
			strcat(octal, "6");
			strcpy(rights[pos++], "Lecture et écriture.");
		} else if (strcmp(tab[i], "rwx") == 0) {
			strcat(binary, "111 ");
			strcat(octal, "7");
			strcpy(rights[pos++], "Lecture, écriture et exécution.");
		} else {
			printf("%s[-] Erreur : Format fournit incorrect.%s\n", color.RED_ERROR, color.RESET);
			return;
		}
	}

	strcat(binary, "\0");
	strcat(octal, "\0");
	InputColor(buffer, bufferColor, color);
	printf("%s[%s+%s] Informations trouvé à partir de la chaîne : %s%s\n", color.GREY_PROMPT, color.GREEN, color.GREY_PROMPT, color.RESET, bufferColor);
	printf("\t%s[ ] %s\n", color.GREY_PROMPT, type);
	printf("\t%s[ ] Détails des permissions :\n", color.GREY_PROMPT);
	printf("\t\t- Le propriétaire du fichier à les droits de              : %s%s%s\n", color.GREEN, rights[0], color.GREY_PROMPT);
	printf("\t\t- Le groupe associer au fichier à les droits de           : %s%s%s\n", color.GREEN, rights[1], color.GREY_PROMPT);
	printf("\t\t- Le les autres utilisateurs du fichier ont les droits de : %s%s%s\n", color.GREEN, rights[2], color.GREY_PROMPT);
	printf("\t[ ] File mode en binaire : %s%s%s\n", color.GREEN, binary, color.GREY_PROMPT);
	printf("\t[ ] File mode en octal   : %s%s%s\n", color.GREEN, octal, color.RESET);
}
