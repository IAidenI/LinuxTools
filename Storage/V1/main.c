#include "functions.h"

int main() {
	char *total_size;
	char *used;
	char *avaliable;
	char storage[MAX_LENGHT_COMMAND];
	GetStorage(storage);

	total_size = strtok(storage, " ");
	used = strtok(NULL, " ");
	avaliable = strtok(NULL, " ");
	Display(total_size, used, avaliable);
	return 0;
}
