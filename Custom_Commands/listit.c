#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#define MAX 500
void list_dir(const char* path, bool flag_a, bool flag_1, bool flag_r) {
DIR *dir = opendir(path);
if (!dir) {
printf("failed to open directory: %s\n", path);
return;
}
struct dirent *entry;
char *files[MAX];
int c = 0;
while ((entry = readdir(dir)) != NULL) {
if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
continue;
if (!flag_a && entry->d_name[0] == '.')
continue;
if (c < MAX) {
files[c] = strdup(entry->d_name);
c++;
}
}
closedir(dir);
if (flag_r) {
for (int i = c - 1; i >= 0; i--) {
if (flag_1)
printf("%s\n", files[i]);
else
printf("%s ", files[i]);
free(files[i]);
}
}
else {
for (int i = 0; i < c; i++) {
if (flag_1)
printf("%s\n", files[i]);
else
{printf("%s ", files[i]);}
free(files[i]);
}
if (!flag_1)
printf("\n");
}

int main(int argc, char* argv[]) {
bool f_a = false, f_1 = false, f_r = false;
int dir_count = 0;
char *dirs[MAX];

if (argc == 1) {
list_dir(".", false, false, false);
return 0;
}

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-a") == 0) {
            f_a = true;
        } else if (strcmp(argv[i], "-1") == 0) {
            f_1 = true;
        } else if (strcmp(argv[i], "-r") == 0) {
            f_r = true;
        } else {
            dirs[dir_count++] = argv[i];
        }
    }

    if (dir_count == 0) {
        list_dir(".", f_a, f_1, f_r);
    } else {
        for (int i = 0; i < dir_count; i++) {
            printf("%s:\n", dirs[i]);
            list_dir(dirs[i], f_a, f_1, f_r);
        }
    }
    return 0;
}

