#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define ORIGINAL_FILE_NAME "test.txt"
#define ALTERNATIVE_FILE_NAME "test2.txt"

void find_and_delete(FILE* fp, FILE* write_fp, char* target, int file_size) {
    char temp[256];
    int cur_point, before_point, critical_point;

    while(!feof(fp)) {
        before_point = critical_point = ftell(fp);
        fgets(temp, sizeof(temp), fp);
        if(!strstr(temp, target))
            fwrite(temp, strlen(temp), 1, write_fp);
        cur_point = ftell(fp);
        
        if(file_size == cur_point) 
            goto EXIT2;
            
        /*
        if(strstr(temp, target)) {
            while(1) {
                before_point = ftell(fp);
                memset(&temp, 0, sizeof(temp));
                fgets(temp, sizeof(temp), fp);
                cur_point = ftell(fp);
                fseek(fp, critical_point, SEEK_SET);
                fwrite(temp, strlen(temp), 1, fp);
                printf("[%ld] : %s", ftell(fp), temp);
                fseek(fp, cur_point, SEEK_SET);
                critical_point = before_point;

                if(file_size == cur_point)        
                    goto EXIT1;
            }
        }
        */
    }

EXIT1:
    fclose(fp);
    truncate(ORIGINAL_FILE_NAME, before_point);
    printf("exited");

EXIT2:
    fclose(fp);
    fclose(write_fp);
    remove(ORIGINAL_FILE_NAME);
    rename(ALTERNATIVE_FILE_NAME, ORIGINAL_FILE_NAME);
    printf("exited");
}


int main(int argc, char* argv[]) {
    FILE* fp = fopen(ORIGINAL_FILE_NAME,"r+");
    FILE* write_fp = fopen(ALTERNATIVE_FILE_NAME, "w");
    int total_size;
    char* target = argv[1];

    fseek(fp, 0, SEEK_END);   
    total_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    find_and_delete(fp, write_fp, target, total_size);
}
