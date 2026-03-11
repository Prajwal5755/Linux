#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <sys/stat.h>
#include <dirent.h>

bool is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) return false;
    return S_ISDIR(statbuf.st_mode);
}
void grep_file(bool flag_n,bool flag_v,bool flag_c,const char *word,const char*path){
FILE*file_ptr=fopen(path,"r");
if(!file_ptr){
printf("Error in opening file");
return;
}
char str[1000];
int line=0;
int i=0;
int j=0;
while(fgets(str,sizeof(str),file_ptr)){
line++;
if(!flag_v&& flag_n && !flag_c && strstr(str,word)!=NULL){
printf("%d: %s",line,str);}

if(strstr(str,word)!=NULL){
i++;}
if(strstr(str,word)==NULL){
j++;}

if(flag_v &&!flag_c&& strstr(str,word)==NULL){
printf(" %s",str);}
if(flag_v && flag_n && strstr(str,word)==NULL ){
printf("%d: %s",line,str);}
}

if(flag_c&&!flag_v|| flag_c && flag_n){
printf("%d\n",i);}
if(flag_c && flag_v){
printf("%d",j);}
fclose(file_ptr);
}
void grep_directory(bool flag_n, bool flag_v, bool flag_c, const char *word, const char *dir) {
    DIR *dp = opendir(dir);
    if (!dp) {
        fprintf(stderr, "Cannot open directory: %s\n", dir);
        return;
    }
    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        if (is_directory(path)) {
            grep_directory(flag_n, flag_v, flag_c, word, path);
        } else {
            grep_file(flag_n, flag_v, flag_c, word, path);
        }
    }
    closedir(dp);
}
int main(int argc, char *argv[]) {
    bool f_n = false, f_v = false, f_c = false;
    bool invalid_flag = false;
    char *word = NULL;
    int first_path_index = -1;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-n") == 0) f_n = true;
            else if (strcmp(argv[i], "-v") == 0) f_v = true;
            else if (strcmp(argv[i], "-c") == 0) f_c = true;
            else {
                fprintf(stderr, "Invalid flag: %s\n", argv[i]);
                invalid_flag = true;
            }
        } else {
            if (!word) {
                word = argv[i];
            } else if (first_path_index == -1) {
                first_path_index = i;
            }
        }
    }

    if (invalid_flag || !word || first_path_index == -1) {
        fprintf(stderr, "Usage: %s [-n] [-v] [-c] word file1 [file2 ... dir1 ...]\n", argv[0]);
        return 1;
    }

    for (int i = first_path_index; i < argc; i++) {
        if (is_directory(argv[i])) {
            grep_directory(f_n, f_v, f_c, word, argv[i]);
        } else {
            grep_file(f_n, f_v, f_c, word, argv[i]);
        }
    }

    return 0;
}
