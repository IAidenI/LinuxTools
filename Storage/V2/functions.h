#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/statvfs.h>

#define MAX_LENGTH_LINE        256
#define MAX_LENGTH_BYTE_FORMAT 13
#define MAX_BUFFER             1500
#define MAX_LIST               8
#define MAX_LIST_PERCENT       4
#define MAX_CONTENT            50
#define LIMIT_CONTENT          30
#define MAX_USED               30
#define INDEX_USED             4
#define OFFSET                 21

#define MIDLESCORE       "\u2500"
#define CORNER_TOP_LEFT  "\u256D"
#define CORNER_TOP_RIGHT "\u256e"
#define CORNER_BOT_LEFT  "\u2570"
#define CORNER_BOT_RIGHT "\u256f"
#define WALL             "\u2502"
#define CROSS            "\u253C"
#define CROSS_TOP        "\u252C"
#define CROSS_BOT        "\u2534"
#define CROSS_LEFT       "\u251C"
#define CROSS_RIGHT      "\u2524"

#define NOCOLOR "\033[0;0m"
#define GREEN   "\033[38;2;153;255;204m"
#define PURPULE "\033[38;2;204;204;255m"
#define ORANGE  "\033[38;2;255;204;102m"
#define RED     "\033[38;2;153;51;51m"
#define BLUE    "\033[38;2;102;204;255m"
#define ITALIC  "\033[3;37m"

struct SysInfoSize {
    char* device;
    char* mount;
    char* type;
    double total;
    double free;
    double available;
    double used;
    double used_percent;
    double available_percent;
    double free_percent;
};


void ReadLine(const char file_path[], char* data, const unsigned int line);
void BytesToPrintable(double byte, char* converted_value, const unsigned int IsPercent);
unsigned int LenFile(const char file_path[]);
struct SysInfoSize GetSysInfo(char* data);
int InfoIs_Present(const struct SysInfoSize info);
void Line(const unsigned int size_max, char* buffer);
void LineContent(const unsigned int size_max, const char* content, const char* color, char* buffer, struct SysInfoSize info, const unsigned int IsPercent, const unsigned int IsTitle);
void GetMaxLength(const char data[][MAX_LENGTH_LINE], const char label_list_init[][MAX_CONTENT], const unsigned int len_file, unsigned int size_max[]);
void DisplayTitle(const unsigned int size_max[], const char label_list_init[][MAX_CONTENT], struct SysInfoSize info, const unsigned int check);
void DisplayContent(const struct SysInfoSize info, const unsigned int size_max[]);
void DisplayBot(const unsigned int size_max[]);
int IsDevice(const char *type, const char type_list[][10]);
void OctalReplace(char *str);
char OctalToChar(const char *octal);
void ProgressBar(double index, char* buffer, double total);
void CheckColor(char* color_list[MAX_LIST], const double info_list[MAX_LIST_PERCENT]);
