#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static int space(char c){
return (c == ' ' || c == '\n');
}

void wc(const char *path, bool flag_l, bool flag_w, bool flag_c) {
FILE *file = fopen(path, "r");
if (!file) {
printf("Error in opening file: %s\n", path);
return;
}
int line = 0;
int words = 0;
int characters = 0;
char str[1000];
while (fgets(str, sizeof(str), file)) {
line++;
int i = 0;
while (str[i] != '\0') {
characters++;
if ((i == 0 && !space(str[i])) || (!space(str[i]) && space(str[i - 1]))) {
words++;
}
i++;
}
}
fclose(file);
if (flag_l) {
printf("Lines are %d \n", line);
}
if (flag_w) {
printf("Words are %d \n", words);
}
if (flag_c) {
printf("Characters are %d \n", characters);
}
}

int main(int argc, char *argv[]) {
    bool f_l = false;
    bool f_w = false;
    bool f_c = false;
    char *files[100];
    int file_count = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0) {
            f_l = true;
        } else if (strcmp(argv[i], "-w") == 0) {
            f_w = true;
        } else if (strcmp(argv[i], "-c") == 0) {
            f_c = true;
        } else {
            files[file_count++] = argv[i];
        }
    }

    if (file_count == 0) {
        printf("No file provided\n");
        return 1;
    }

    printf("flags are %d,%d,%d\n", f_l, f_w, f_c);

    for (int i = 0; i < file_count; i++) {
        printf("==== %s ====\n", files[i]);
        wc(files[i], f_l, f_w, f_c);
    }

    return 0;
}

