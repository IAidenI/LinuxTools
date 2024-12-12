#include "functions.h"

int main() {
    const char proc_mounts_path[] = "/proc/mounts";
    const char label_list_init[MAX_LIST][MAX_CONTENT] = {"MOUNTED ON", "SIZE", "USED", "AVAILABLE", "USED%", "FREE", "TYPE", "FILESYSTEM"};
    unsigned int len_file = LenFile(proc_mounts_path);

    char data[len_file][MAX_LENGTH_LINE];
    unsigned int size_max[MAX_LIST];

    const char special_types[10][10] = {"tmpfs", "devtmpfs", "proc", "sysfs", "cgroup", "overlay", "squashfs", "fuse", "efivarfs", "#"};

    for (unsigned int i = 0; i < len_file; i++) {
        ReadLine(proc_mounts_path, data[i], i);
    }

    GetMaxLength(data, label_list_init, len_file, size_max);

    for (unsigned int i = 0; i < len_file; i++) {
        struct SysInfoSize info = GetSysInfo(data[i]);
        if (i == 0) {
            DisplayTitle(size_max, label_list_init, info, 1);
        }
        if (InfoIs_Present(info)) {
            if (!IsDevice(info.type, special_types)) {
                DisplayContent(info, size_max);
            }
        }
    }
    DisplayBot(size_max);

    for (unsigned int i = 0; i < len_file; i++) {
        ReadLine(proc_mounts_path, data[i], i);
    }

    GetMaxLength(data, label_list_init, len_file, size_max);

    for (unsigned int i = 0; i < len_file; i++) {
        struct SysInfoSize info = GetSysInfo(data[i]);
        if (i == 0) {
            DisplayTitle(size_max, label_list_init, info, 0);
        }
        if (InfoIs_Present(info)) {
            if (IsDevice(info.type, special_types)) {
                DisplayContent(info, size_max);
            }
        }
    }
    DisplayBot(size_max);
    printf("\n%sDifference between free and available :\n", ITALIC);
    printf("  - Free : Free space (with reserved block)\n");
    printf("  - Available : Real free space for non-root users)\n%s", NOCOLOR);
    return 0;
}
