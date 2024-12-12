#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER       11
#define MAX_BUFFER_COLOR 249
#define MAX_TYPE         51
#define MAX_MODE         4
#define VERSION          "V 0.2"
#define VERSION_DATE     "03/09/2024"

typedef struct {
	const char* GREEN;
	const char* RED;
	const char* BLUE;
	const char* LIGHT;
	const char* YELLOW;
	const char* DARK_BLUE;
	const char* PINK;
	const char* GREY_PROMPT;
	const char* ORANGE;
	const char* YELLOW_WARNING;
	const char* RED_ERROR;
	const char* RESET;
} Colors;

void InputColor(const char input[MAX_BUFFER], char newInput[MAX_BUFFER_COLOR], const Colors color);
void Help(const char* buffer);
void ModeToOctal(const char buffer[MAX_BUFFER], const Colors color);
void ModeToOctalVerbose(const char buffer[MAX_BUFFER], const Colors color);
