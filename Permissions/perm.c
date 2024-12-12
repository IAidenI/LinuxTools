#include "functions.h"

int main(int argc, char** argv) {
	if (argc != 2 && argc != 3) {
		Help(argv[0]);
		return 1;
	}

	Colors color = {
		.GREEN          = "\033[38;2;0;255;0m",
		.BLUE           = "\033[38;2;102;204;255m",
		.RED            = "\033[38;2;204;0;50m",
		.YELLOW         = "\033[38;2;255;255;102m",
		.DARK_BLUE      = "\033[38;2;51;0;255m",
		.PINK           = "\033[38;2;255;0;204m",
		.GREY_PROMPT    = "\033[38;2;102;102;153m",
		.ORANGE         = "\033[38;2;255;102;0m",
		.YELLOW_WARNING = "\033[1;33;1;40m",
		.RED_ERROR      = "\033[1;31;1;40m",
		.RESET          = "\033[0;0m"
	};

	char* prompt = " _    _\n"
				   "| |  (_)_ _ _  ___ __\n"
				   "| |__| | ' \\ || \\ \\ /\n"
				   "|____|_|_||_\\_,_/_\\_\\\n"
				   " ___               _       _\n"
				   "| _ \\___ _ _ _ __ (_)_____(_)___ _ _  ___\n"
				   "|  _/ -_) '_| '  \\| (_-<_-< / _ \\ ' \\(_-<\n"
				   "|_| \\___|_| |_|_|_|_/__/__/_\\___/_||_/__/\n"
				   "                %s\n"
				   "   from Aiden\n\n"
				   "%s[ ] Rappel :\n"
				   "  %sr%s : %sRead\n"
				   "  %sw%s : %sWrite\n"
				   "  %sx%s : %sExecutable%s\n"
				   "  - : %sAucun droits%s\n\n"
				   "                  -       %sr%sw%sx       %sr%sw%s-   %sr%s-%sx%s\n"
				   "                  │        │         │     │\n"
				   "  %sType de fichier%s ╯  %sPropriétaire  Groupe%s  ╰ %sAutres utilisateurs%s\n"
				   "        │\n"
				   "        ├ - : %sFichier%s\n"
				   "        ├ %sd%s : %sDossier%s\n"
				   "        ╰ %sl%s : %sLien Symbolique\n\n"
				   "%s[!] Attention : Ce script ne prend pas en compte les bits spéciaux (comme par exemple les bits de setuid)%s\n\n";
	char* permissions = "╭───────┬────────┬───────────╮\n"
						"│ %sOctal%s │ %sBinary%s │ %sFile Mode%s │\n"
						"├───────┼────────┼───────────┤\n"
						"│   0   │   000  │    ---    │\n"
						"│   1   │   001  │    --%sx%s    │\n"
						"│   2   │   010  │    -%sw%s-    │\n"
						"│   3   │   011  │    -%sw%sx%s    │\n"
						"│   4   │   100  │    %sr%s--    │\n"
						"│   5   │   101  │    %sr%s-%sx%s    │\n"
						"│   6   │   110  │    %sr%sw%s-    │\n"
						"│   7   │   111  │    %sr%sw%sx%s    │\n"
						"╰───────┴────────┴───────────╯\n";
	char choice;
	char mode[MAX_BUFFER];

	if (strcmp(argv[1], "-r") == 0) {
		if (argc != 3) {
			printf("Usage: %s -r <file mode> (avec <file mode> chaîne de %d ou %d caractères, ex : -rwxr-xr-x ou rwxr-xr-x)\n", argv[0], MAX_BUFFER - 1, MAX_BUFFER - 2);
			return 1;
		}

		if (strlen(argv[2]) != MAX_BUFFER - 1 && strlen(argv[2]) != MAX_BUFFER - 2) {
			printf("%s[-] Erreur : Argument trop long ou trop court (<file mode> chaîne de %d ou %d caractères, ex : -rwxr-xr-x ou rwxr-xr-x)%s\n", color.RED_ERROR, MAX_BUFFER - 1, MAX_BUFFER - 2, color.RESET);
			return 1;
		} else if (strlen(argv[2]) == MAX_BUFFER - 2) {
			memmove(argv[2] + 1, argv[2], strlen(argv[2]) + 1);
			argv[2][0] = '#';
		}

		ModeToOctalVerbose(argv[2], color);
	} else if (strcmp(argv[1], "-o") == 0) {
		if (strlen(argv[2]) != MAX_BUFFER - 1 && strlen(argv[2]) != MAX_BUFFER - 2) {
			printf("%s[-] Erreur : Argument trop long ou trop court (<file mode> chaîne de %d ou %d caractères, ex : -rwxr-xr-x ou rwxr-xr-x)%s\n", color.RED_ERROR, MAX_BUFFER - 1, MAX_BUFFER - 2, color.RESET);
			return 1;
		} else if (strlen(argv[2]) == MAX_BUFFER - 2) {
			memmove(argv[2] + 1, argv[2], strlen(argv[2]) + 1);
			argv[2][0] = '#';
 		}

		ModeToOctal(argv[2], color);
	} else if (strcmp(argv[1], "--cheat-sheets") == 0 || strcmp(argv[1], "-c") == 0) {
		printf(prompt, VERSION, color.GREY_PROMPT, color.RED, color.RESET, color.GREY_PROMPT, color.YELLOW,
						color.RESET, color.GREY_PROMPT, color.BLUE, color.RESET, color.GREY_PROMPT,
						color.RESET, color.GREY_PROMPT, color.RESET, color.RED, color.YELLOW, color.BLUE,
						color.RED, color.YELLOW, color.RESET, color.RED, color.RESET, color.BLUE, color.RESET,
						color.GREY_PROMPT, color.RESET, color.GREY_PROMPT, color.RESET, color.GREY_PROMPT,
						color.RESET, color.GREY_PROMPT, color.RESET, color.DARK_BLUE, color.RESET,
						color.GREY_PROMPT, color.RESET, color.PINK, color.RESET, color.GREY_PROMPT,
						color.YELLOW_WARNING, color.RESET);

		printf(permissions, color.GREY_PROMPT, color.RESET, color.GREY_PROMPT, color.RESET, color.GREY_PROMPT,
							color.RESET, color.BLUE, color.RESET, color.YELLOW, color.RESET, color.YELLOW,
							color.BLUE, color.RESET, color.RED, color.RESET, color.RED, color.RESET, color.BLUE,
							color.RESET, color.RED, color.YELLOW, color.RESET, color.RED, color.YELLOW, color.BLUE,
							color.RESET);
		return 0;
	} else if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
		Help(argv[0]);
		return 0;
	} else if (strcmp(argv[1], "--interactive") == 0 || strcmp(argv[1], "-i") == 0) {
		printf(prompt, VERSION, color.GREY_PROMPT, color.RED, color.RESET, color.GREY_PROMPT, color.YELLOW,
						color.RESET, color.GREY_PROMPT, color.BLUE, color.RESET, color.GREY_PROMPT,
						color.RESET, color.GREY_PROMPT, color.RESET, color.RED, color.YELLOW, color.BLUE,
						color.RED, color.YELLOW, color.RESET, color.RED, color.RESET, color.BLUE, color.RESET,
						color.GREY_PROMPT, color.RESET, color.GREY_PROMPT, color.RESET, color.GREY_PROMPT,
						color.RESET, color.GREY_PROMPT, color.RESET, color.DARK_BLUE, color.RESET,
						color.GREY_PROMPT, color.RESET, color.PINK, color.RESET, color.GREY_PROMPT,
						color.YELLOW_WARNING, color.RESET);

		do {
			printf("[1] - Liste des permissions\n");
			printf("[2] - Conversion file mode en octal/binaire\n");
			printf("[3] - Exit\n\n> ");
			scanf("%c", &choice);
			int temp;
			while ((temp = getchar()) != '\n' && temp != EOF);

			if (choice == '1') {
				printf(permissions, color.GREY_PROMPT, color.RESET, color.GREY_PROMPT, color.RESET, color.GREY_PROMPT,
									color.RESET, color.BLUE, color.RESET, color.YELLOW, color.RESET, color.YELLOW,
									color.BLUE, color.RESET, color.RED, color.RESET, color.RED, color.RESET, color.BLUE,
									color.RESET, color.RED, color.YELLOW, color.RESET, color.RED, color.YELLOW, color.BLUE,
									color.RESET);
			} else if (choice == '2') {
				printf("\n%s[%s*%s] Saisir un file mode. Par exemple : %s-%sr%sw%sx%sr%s-%sx%sr%s-%sx%s\n> ", color.GREY_PROMPT, color.ORANGE, color.GREY_PROMPT,
																												color.RESET, color.RED, color.YELLOW, color.BLUE,
																												color.RED, color.RESET, color.BLUE, color.RED,
																												color.RESET, color.BLUE, color.RESET);
				scanf("%10s", mode);
				while ((temp = getchar()) != '\n' && temp != EOF);

				if (strlen(mode) == MAX_BUFFER - 2) {
					memmove(mode + 1, mode, strlen(mode) + 1);
					mode[0] = '#';
				}

				printf("\n");
				ModeToOctalVerbose(mode, color);
				printf("\n");
			} else if (choice != '3') {
				printf("\n%s[-] Erreur : Vous avez saisi :%s %c\n\n", color.RED_ERROR, color.RESET, choice);
			}
		} while (choice != '3');
	} else if (strcmp(argv[1], "--version") == 0) {
		printf("Linux Permissions %s - %s\n", VERSION, VERSION_DATE);
		printf("  - by Aiden\n");
		return 0;
	} else {
		printf("%s: Option '%s' inconnue (pour plus d'informations \"%s --help\")\n", argv[0], argv[1], argv[0]);
		return 1;
	}
	return 0;
}
