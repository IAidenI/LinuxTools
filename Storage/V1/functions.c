#include "functions.h"

void Prompt() {
	printf("   _____ _                               _____  _           _             \n");
	printf("  / ____| |                             |  __ \\(_)         | |            \n");
	printf(" | (___ | |_ ___  _ __ __ _  __ _  ___  | |  | |_ ___ _ __ | | __ _ _   _ \n");
	printf("  \\___ \\| __/ _ \\| '__/ _` |/ _` |/ _ \\ | |  | | / __| '_ \\| |/ _` | | | |\n");
	printf("  ____) | || (_) | | | (_| | (_| |  __/ | |__| | \\__ \\ |_) | | (_| | |_| |\n");
	printf(" |_____/ \\__\\___/|_|  \\__,_|\\__, |\\___| |_____/|_|___/ .__/|_|\\__,_|\\__, |\n");
	printf("                             __/ |                   | |             __/ |\n");
	printf("                            |___/                    |_|            |___/ \n\n");
}

void GetStorage(char* storage) {
	FILE *fp;

	fp = popen("df -h --output=size,used,avail / | tail -n 1 | awk '{$1=$1; print}' | tr -d '\n'", "r");
	if (fp == NULL) {
		printf("Can't run the command.");
		exit(1);
	}

	if (fgets(storage, MAX_LENGHT_COMMAND, fp) == NULL) {
		printf("Can read output command.");
	}
	pclose(fp);
}

void Display(char* total_size, char* used, char* avaliable) {
	Prompt();
	float percent_used = (atoi(used) * 100) / atoi(total_size);
	unsigned int round_percent_used = round(percent_used);

        float percent_avaliable = (atoi(avaliable) * 100) / atoi(total_size);

	unsigned int system_size = atoi(total_size) - (atoi(used) + atoi(avaliable));
	float percent_system = 100 - (round_percent_used + round(percent_avaliable));

	const char* color;
	if (round_percent_used > 0 && round_percent_used < 33) {
		color = "\e[0;32m";
	} else if (round_percent_used > 33 && round_percent_used < 66) {
		color = "\033[0;33m";
	} else {
		color = "\e[0;31m";
	}

	printf("[");
	for(unsigned int i = 0; i < round_percent_used; i++) {
		printf("%s\u2588", color);
	}
	for(unsigned int i = round_percent_used; i < 100; i++) {
		printf("\e[0m:");
	}
	printf("] %.2f%% used.\n\n", percent_used);

	printf("\e[0;34m[ ] Informations about storage :\n");
        printf("\t- Volume total     : %s\n", total_size);
	printf("\t- Volume used      : %s (%.2f%%)\n", used, percent_used);
	printf("\t- Volume avaliable : %s (%.2f%%)\n", avaliable, percent_avaliable);
	printf("\t- Volume system    : %dG (%.2f%%)\n\e[0m", system_size, percent_system);
}
