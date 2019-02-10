#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ORIGINAL_FILE_NAME "test.txt"
#define ALTERNATIVE_FILE_NAME "test2.txt"
#define MARKER_MACRO "marker:00000000000000000000\n"
#define MARKER_SIGNATURE "marker:" 
#define MARKER_POINT 27 // length of first line : 27

int nMarker;
const int DEADLINE_FOR_CLEAN = 5;

void rewrite_marker(FILE* fp, char* str) {
    fseek(fp, 0, SEEK_SET);
    fwrite(MARKER_MACRO, strlen(MARKER_MACRO), 1, fp);
    fseek(fp, MARKER_POINT - strlen(str) , SEEK_SET);
    fwrite(str, strlen(str), 1, fp);
}


void find_and_delete(FILE* fp, char* target, char* target2, int file_size) {
    char temp[256];
    char marker_str[256];
    int cur_point, before_point, critical_point;

    while(!feof(fp)) {
        before_point = critical_point = ftell(fp);
        fgets(temp, sizeof(temp), fp);
        if(!strcmp(temp, target) || !strcmp(temp, target2) && !strstr(temp, MARKER_SIGNATURE)) {
            temp[0] = '*';
            nMarker++;
            fseek(fp, before_point, SEEK_SET);
            fwrite(temp, strlen(temp), 1, fp);
        }
        cur_point = ftell(fp);
        fseek(fp, cur_point, SEEK_SET);
        
        if(file_size == cur_point) 
            goto EXIT1;
    }

EXIT1:
    sprintf(marker_str, "%d", nMarker);
    rewrite_marker(fp, marker_str);
    fclose(fp);
    printf("exited");
}

char* get_num_marker(FILE* fp) {
    char* temp = (char*)malloc(sizeof(char) * 256);
    char* nMarkers = NULL;
    int i=0;
    fgets(temp, 256, fp);
    temp += strlen("marker:");
    while(temp[i++] == '0');
    return temp + i - 1;
}

void clear_delete_marker(FILE** fp) {
    if(nMarker < DEADLINE_FOR_CLEAN) return;

    FILE* alternative_fp = fopen(ALTERNATIVE_FILE_NAME, "w");
    char temp[256];
    char marker_str[256];

    fseek(*fp, 0, SEEK_SET); 
    
    while(!feof(*fp)) {
        fgets(temp, sizeof(temp), *fp);
        if(temp[0] == '*') {
            nMarker--;
            continue;
        }
        fwrite(temp, strlen(temp), 1, alternative_fp);
    }
    sprintf(marker_str, "%d", nMarker);
    rewrite_marker(alternative_fp, marker_str);
    rename(ALTERNATIVE_FILE_NAME, ORIGINAL_FILE_NAME);
    remove(ALTERNATIVE_FILE_NAME);
    fclose(*fp);
    fclose(alternative_fp);

    *fp = fopen(ORIGINAL_FILE_NAME,"r+");
}

// 데이터 순서는 중요치않음 (arbitrary sequence)
int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage : ./a.out [string]");
        exit(-1);
    }
    
    FILE* fp = fopen(ORIGINAL_FILE_NAME,"r+");
    int total_size, pid, status;
    char target[256];
    char *target2 = argv[1];
    sprintf(target, "%s\n", argv[1]);

    nMarker = atoi(get_num_marker(fp));
    clear_delete_marker(&fp);

    fseek(fp, 0, SEEK_END);   
    total_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    find_and_delete(fp, target, target2, total_size);
}
