#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void cat(char const *path, bool flag_n, bool flag_s, bool flag_e) {
FILE *file = fopen(path, "r");
if (!file) {
printf("Error opening file: %s\n", path);
return;
  }
char str[1024];
int line = 1;
bool p_blank = false;
bool c_blank = false;
while (fgets(str, sizeof(str), file)) {
c_blank = (strcmp(str, "\n") == 0);
if (flag_s && c_blank && p_blank) {
continue;
}
p_blank = c_blank;
if (flag_n) {
printf("%d %s", line++, str);
}
else if (flag_e) 
{
size_t size = strlen(str);
if (size > 0 && str[size - 1] == '\n') {
str[size - 1] = '\0';
printf("%s$\n", str);
} 
else {
printf("%s", str);
}
} else 
{
printf("%s", str);
}
}
fclose(file);
}

int main(int argc, char *argv[]) {
    bool f_n = false;
    bool f_s = false;
    bool f_e = false;
    char *file = NULL;
    char *files[100];
    int file_count = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0)
            f_n = true;
        else if (strcmp(argv[i], "-s") == 0)
            f_s = true;
        else if (strcmp(argv[i], "-e") == 0)
            f_e = true;
        else
            files[file_count++] = argv[i];
    }

    if (file_count == 0) {
        printf("Usage: %s [-n] [-s] [-e] file1 [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 0; i < file_count; i++) {
        printf("%s \n", files[i]);
        cat(files[i], f_n, f_s, f_e);
    }

    return 0;
}

