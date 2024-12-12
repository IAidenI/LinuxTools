#include "functions.h"

void ReadLine(const char file_path[], char* data, const unsigned int line) {
    unsigned int current_line = 0;
    FILE* file = NULL;
    file = fopen(file_path, "r");

    if (file == NULL) {
        fprintf(stderr, "[-] Impossible de récupérer les informations relatives à l'appareil.");
        exit(EXIT_FAILURE);
    }

    while (fgets(data, MAX_LENGTH_LINE, file) != NULL) {
        if (current_line == line) {
            break;
        }
        current_line++;
    }
    fclose(file);
}

unsigned int LenFile(const char file_path[]) {
    char trash[MAX_LENGTH_LINE];
    unsigned int line = 0;
    FILE* file = NULL;
    file = fopen(file_path, "r");

    if (file == NULL) {
        fprintf(stderr, "[-] Impossible de récupérer les informations relatives à l'appareil.");
        exit(EXIT_FAILURE);
    }

    while (fgets(trash, MAX_LENGTH_LINE, file) != NULL) {
        line++;
    }
    fclose(file);
    return line;
}

void GetMaxLength(const char data[][MAX_LENGTH_LINE], const char label_list_init[][MAX_CONTENT], const unsigned int len_file, unsigned int size_max[]) {
    char device[len_file][MAX_CONTENT];
    memset(device, '\0', sizeof(device));
    char mount[len_file][MAX_CONTENT];
    memset(mount, '\0', sizeof(mount));
    char type[len_file][MAX_CONTENT];
    memset(type, '\0', sizeof(type));

    for (unsigned int i = 0; i < len_file; i++) {
        char temp[MAX_LENGTH_LINE];
        strncpy(temp, data[i], MAX_LENGTH_LINE);

        char *token = strtok(temp, " ");
        if (token != NULL) {
            strncpy(device[i], token, MAX_CONTENT);
        }

        token = strtok(NULL, " ");
        if (token != NULL) {
            strncpy(mount[i], token, MAX_CONTENT);
        }

        token = strtok(NULL, " ");
        if (token != NULL) {
            strncpy(type[i], token, MAX_CONTENT);
        }
    }

    struct statvfs stats;
    double total_byte[len_file];
    double free_byte[len_file];
    double available_byte[len_file];
    double used_byte[len_file];

    for (unsigned int i = 0; i < len_file; i++) {
        if (statvfs(mount[i], &stats) != 0) {
            total_byte[i] = 0;
            free_byte[i] = 0;
            available_byte[i] = 0;
            used_byte[i] = 0;
        } else {
            total_byte[i] = (double) stats.f_frsize * (double) stats.f_blocks;
            free_byte[i] = (double) stats.f_frsize * (double) stats.f_bfree;
            available_byte[i] = (double) stats.f_frsize * (double) stats.f_bavail;
            used_byte[i] = total_byte[i] - free_byte[i];
        }
    }

    char total[len_file][MAX_LENGTH_BYTE_FORMAT];
    char free[len_file][MAX_LENGTH_BYTE_FORMAT];
    char available[len_file][MAX_LENGTH_BYTE_FORMAT];
    char used[len_file][MAX_LENGTH_BYTE_FORMAT];
    char used_percent[len_file][MAX_LENGTH_BYTE_FORMAT];
    for (unsigned int i = 0; i < len_file; i++) {
        BytesToPrintable(total_byte[i], total[i], 0);
        BytesToPrintable(free_byte[i], free[i], 0);
        BytesToPrintable(available_byte[i], available[i], 0);
        BytesToPrintable(used_byte[i], used[i], 0);
        BytesToPrintable(used_byte[i], used_percent[i], 1);
    }

    char info_list[MAX_LIST][len_file][MAX_CONTENT];
    for (unsigned int i = 0; i < len_file; i++) {
        if (!(total_byte[i] == 0 && free_byte[i] == 0 && available_byte[i] == 0 && used_byte[i] == 0)) {
            strcpy(info_list[0][i], mount[i]);
            strcpy(info_list[1][i], total[i]);
            strcpy(info_list[2][i], used[i]);
            strcpy(info_list[3][i], available[i]);
            strcpy(info_list[4][i], used_percent[i]);
            strcpy(info_list[5][i], free[i]);
            strcpy(info_list[6][i], type[i]);
            strcpy(info_list[7][i], device[i]);
        } else {
            strcpy(info_list[0][i], "");
            strcpy(info_list[1][i], "");
            strcpy(info_list[3][i], "");
            strcpy(info_list[4][i], "");
            strcpy(info_list[5][i], "");
            strcpy(info_list[6][i], "");
            strcpy(info_list[7][i], "");
        }
    }

    size_max[INDEX_USED] = MAX_USED;
    for (unsigned int i = 0; i < MAX_LIST; i++) {
        for (unsigned int j = 0; j < len_file; j++) {
            if ((strlen(info_list[i][j]) > strlen(label_list_init[i])) && (strlen(info_list[i][j]) > size_max[i]) && (i != INDEX_USED)) {
                size_max[i] = strlen(info_list[i][j]);
            } else if ((strlen(info_list[i][j]) < strlen(label_list_init[i])) && (strlen(label_list_init[i]) > size_max[i]) && (i != INDEX_USED)) {
                size_max[i] = strlen(label_list_init[i]);
            }

            if (size_max[i] > LIMIT_CONTENT) {
                size_max[i] = LIMIT_CONTENT;
            }
        }
    }
}

struct SysInfoSize GetSysInfo(char* data) {
    char* device = strtok(data, " ");
    char* mount = strtok(NULL, " ");
    char* type = strtok(NULL, " ");
    struct statvfs stats;
    struct SysInfoSize info;

    if (device) OctalReplace(device);
    if (mount) OctalReplace(mount);
    if (type) OctalReplace(type);

    info.device = device;
    info.mount = mount;
    info.type = type;

    if (statvfs(mount, &stats) != 0) {
        info.total = 0;
        info.free = 0;
        info.available = 0;
        info.used = 0;
        return info;
    }

    info.total = (double)stats.f_frsize * (double)stats.f_blocks;
    info.free = (double)stats.f_frsize * (double)stats.f_bfree;
    info.available = (double)stats.f_frsize * (double)stats.f_bavail;
    info.used = info.total - info.free;
    info.used_percent = (info.used * 100) / info.total;
    info.available_percent = (info.available * 100) / info.total;
    info.free_percent = (info.free * 100) / info.total;
    return info;
}

int IsDevice(const char *type, const char type_list[][10]) {
    for (int i = 0; strcmp(type_list[i], "#") != 0; i++) {
        if (strcmp(type, type_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void BytesToPrintable(double byte, char* converted_value, const unsigned int IsPercent) {
    char units[5][3] = {"o", "Ko", "Mo", "Go", "To"};
    int width = 5;
    for (unsigned int i = 0; i < 5; i++) {
        if (byte < 1024) {
            if (IsPercent) {
                sprintf(converted_value, "%*.1f %%", width, byte);
            } else {
                sprintf(converted_value, "%*.1f %s", width, byte, units[i]);
            }
            return;
        }
        byte = byte / 1024;
    }
}

int InfoIs_Present(const struct SysInfoSize info) {
    return (info.total == 0 && info.free == 0 && info.available == 0 && info.used == 0) ? 0 : 1;
}

void Line(const unsigned int size_max, char* buffer) {
    for (unsigned int i = 0; i < size_max + 2; i++) {
        sprintf(buffer + strlen(buffer), "%s", MIDLESCORE);
    }
}

void ProgressBar(double index, char* buffer, double total) {
    unsigned int index_20 = (unsigned int)round((index * 20) / total);
    for (unsigned int i = 0; i < index_20; ++i) {
        sprintf(buffer + strlen(buffer), "#");
    }
    for (unsigned int i = 0; i < 20 - index_20; i++) {
        sprintf(buffer + strlen(buffer), ".");
    }
}

void LineContent(const unsigned int size_max, const char* content, const char* color, char* buffer, struct SysInfoSize info, const unsigned int IsPercent, const unsigned int IsTitle) {
    if (IsPercent && !IsTitle) {
        sprintf(buffer + strlen(buffer), "%s[", color);
        ProgressBar(info.used, buffer, info.total);
        sprintf(buffer + strlen(buffer), "%s] %s%s", color, content, NOCOLOR);
    } else {
        char content_modify[MAX_CONTENT];
        strncpy(content_modify, content, MAX_CONTENT);

        if (strlen(content_modify) > LIMIT_CONTENT) {
            content_modify[LIMIT_CONTENT - 3] = '.';
            content_modify[LIMIT_CONTENT - 2] = '.';
            content_modify[LIMIT_CONTENT - 1] = '.';
            content_modify[LIMIT_CONTENT] = '\0';
        }

        sprintf(buffer + strlen(buffer), "%s%s%s", color, content_modify, NOCOLOR);
        if (strlen(content_modify) != size_max) {
            for (unsigned int i = 0; i < size_max - strlen(content_modify); i++) {
                sprintf(buffer + strlen(buffer), " ");
            }
        }
    }
}

void DisplayTitle(const unsigned int size_max[], const char label_list_init[][MAX_CONTENT], struct SysInfoSize info, const unsigned int check) {
    char label_list[MAX_LIST][MAX_CONTENT];
    for (int i = 0; i < MAX_LIST; i++) {
        strcpy(label_list[i], label_list_init[i]);
    }
    char* label;

    if (check) {
        label = "Local Devices";
    } else {
        label = "Special Devices";
    }
    
    unsigned int somme = 0;
    for (unsigned int i = 0; i < MAX_LIST; ++i) {
        somme += size_max[i];
    }

    char buffer_top[MAX_BUFFER];
    char buffer_type[MAX_BUFFER];
    char buffer_top_title[MAX_BUFFER];
    char buffer_title[MAX_BUFFER];
    char buffer_mid[MAX_BUFFER];

    sprintf(buffer_top, "%s", CORNER_TOP_LEFT);
    Line(somme + OFFSET, buffer_top);
    sprintf(buffer_top + strlen(buffer_top), "%s\n", CORNER_TOP_RIGHT);

    sprintf(buffer_type, "%s %s", WALL, label);
    for (unsigned int i = 0; i < (somme + OFFSET) - strlen(label); i++) {
        sprintf(buffer_type + strlen(buffer_type), "%s", " ");
    }
    sprintf(buffer_type + strlen(buffer_type), " %s\n", WALL);

    sprintf(buffer_top_title, "%s", CROSS_LEFT);
    sprintf(buffer_title, "%s ", WALL);
    sprintf(buffer_mid, "%s", CROSS_LEFT);

    for (unsigned int i = 0; i < MAX_LIST; i++) {
        Line(size_max[i], buffer_top_title);
        if (i == INDEX_USED) {
            LineContent(size_max[i], label_list_init[i], NOCOLOR, buffer_title, info, 1, 1);
        } else {
            LineContent(size_max[i], label_list_init[i], NOCOLOR, buffer_title, info, 0, 1);
        }
        Line(size_max[i], buffer_mid);

        if (i == (MAX_LIST - 1)) {
            sprintf(buffer_top_title + strlen(buffer_top_title), "%s\n", CROSS_RIGHT);
            sprintf(buffer_title + strlen(buffer_title), " %s\n", WALL);
            sprintf(buffer_mid + strlen(buffer_mid), "%s\n", CROSS_RIGHT);
        } else {
            sprintf(buffer_top_title + strlen(buffer_top_title), "%s", CROSS_TOP);
            sprintf(buffer_title + strlen(buffer_title), " %s ", WALL);
            sprintf(buffer_mid + strlen(buffer_mid), "%s", CROSS);
        }
    }
    printf("%s", buffer_top);
    printf("%s", buffer_type);
    printf("%s", buffer_top_title);
    printf("%s", buffer_title);
    printf("%s", buffer_mid);
}

void CheckColor(char* color_list[MAX_LIST], const double info_list[MAX_LIST_PERCENT]) {
    int values[] = {2,3, 4, 5};
    int inverse[] = {0, 1, 0, 1};
    int num_values = sizeof(values) / sizeof(values[0]);
    double temp;

    for (unsigned int i = 0; i < num_values; ++i) {
        if (inverse[i]) {
            temp = 100 - info_list[i];
        } else {
            temp = info_list[i];
        }
        if (temp < 33.33) {
            color_list[values[i]] = GREEN;
        } else if ((33.33 < temp) && (temp < 66.66)) {
            color_list[values[i]] = ORANGE;
        } else {
            color_list[values[i]] = RED;
        }
    }
}

void DisplayContent(const struct SysInfoSize info, const unsigned int size_max[]) {
    char buffer_content[MAX_BUFFER];

    char total[MAX_LENGTH_BYTE_FORMAT];
    char free[MAX_LENGTH_BYTE_FORMAT];
    char available[MAX_LENGTH_BYTE_FORMAT];
    char used[MAX_LENGTH_BYTE_FORMAT];
    char used_percent[MAX_LENGTH_BYTE_FORMAT];
    BytesToPrintable(info.total, total, 0);
    BytesToPrintable(info.free, free, 0);
    BytesToPrintable(info.available, available, 0);
    BytesToPrintable(info.used, used, 0);
    BytesToPrintable(info.used_percent, used_percent, 1);

    const char* info_list[MAX_LIST] = {info.mount, total, used, available, used_percent, free, info.type, info.device};
    const double info_percent[MAX_LIST_PERCENT] = {info.used_percent, info.available_percent, info.used_percent, info.free_percent};
    char* color_list[MAX_LIST] = {BLUE, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, NOCOLOR, PURPULE, PURPULE};
    CheckColor(color_list, info_percent);
    sprintf(buffer_content, "%s ", WALL);

    for (unsigned int i = 0; i < MAX_LIST; i++) {
        if (i == INDEX_USED) {
            LineContent(size_max[i], info_list[i], color_list[i], buffer_content, info, 1, 0);
        } else {
            LineContent(size_max[i], info_list[i], color_list[i], buffer_content, info, 0, 0);
        }

        if (i == (MAX_LIST - 1)) {
            sprintf(buffer_content + strlen(buffer_content), " %s\n", WALL);
        } else {
            sprintf(buffer_content + strlen(buffer_content), " %s ", WALL);
        }
    }
    printf("%s", buffer_content);
}

void DisplayBot(const unsigned int size_max[]) {
    char buffer_bot[MAX_BUFFER];

    sprintf(buffer_bot, "%s", CORNER_BOT_LEFT);

    for (unsigned int i = 0; i < MAX_LIST; i++) {
        Line(size_max[i], buffer_bot);

        if (i == (MAX_LIST - 1)) {
            sprintf(buffer_bot + strlen(buffer_bot), "%s\n", CORNER_BOT_RIGHT);
        } else {
            sprintf(buffer_bot + strlen(buffer_bot), "%s", CROSS_BOT);
        }
    }
    printf("%s", buffer_bot);
}

char OctalToChar(const char *octal) {
    return (char) strtol(octal, NULL, 8);
}

void OctalReplace(char *str) {
    char buffer[1024];
    char *p = str;
    char *q = buffer;

    while (*p) {
        if (*p == '\\' && *(p+1) >= '0' && *(p+1) <= '7') {
            char octal[4] = {0};
            int i;
            for (i = 0; i < 3 && *(p+1+i) >= '0' && *(p+1+i) <= '7'; i++) {
                octal[i] = *(p+1+i);
            }
            *q++ = OctalToChar(octal);
            p += 1 + i;
        } else {
            *q++ = *p++;
        }
    }
    *q = '\0';
    strcpy(str, buffer);
}
