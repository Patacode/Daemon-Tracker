#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

#include "util.h"

String to_path(String dot_name){
    static char buf[BUF_LEN];
    char* current_dot;

    sprintf(buf, "/%s", dot_name);
    current_dot = strchr(buf, '.');
    while(current_dot != NULL){
        *current_dot = '/';
        current_dot = strchr(current_dot, '.');
    }

    return buf;
}

String extract_pdt(String path){
    static char buf[BUF_LEN];
    int dist = strrchr(path, '/') - path;
    strncpy(buf, path, dist);
    
    return buf; 
}

String extract_watched_dir(String path){
    return strrchr(path, '/') + 1;
}

String create_path(String arg, int parent_wd){
    Pair current_pair;
    char buf[BUF_LEN] = "";
    char tmp_buf[BUF_LEN] = "";
    static char final_buf[BUF_LEN] = "";

    current_pair = hashmap_get(wd_graph, HASHMAP_LEN, parent_wd);
    while(current_pair != NULL){
        sprintf(tmp_buf, "%s", buf);
        sprintf(buf, "/%s%s", current_pair -> name, tmp_buf);
        current_pair = hashmap_get(wd_graph, HASHMAP_LEN, current_pair -> right);
    }
    sprintf(final_buf, "%s%s/%s", pdt, buf, arg);

    return final_buf; 
}

int is_valid_path(String path){
    int fd = open(path, O_RDONLY);
    if(fd < 0)
        return 0;

    close(fd);
    return 1;
}

void flush_printf(String format, int nargs, ...){
    va_list args;
    char buf[BUF_LEN];

    va_start(args, nargs);
    vsprintf(buf, format, args);
    printf("%s\n", buf);
    va_end(args);

    fflush(stdout);
    fflush(stderr);
}

void flush_tsprintf(String format, int nargs, ...){
    va_list args;
    char buf[BUF_LEN];
    time_t now = time(NULL);

    va_start(args, nargs);
    vsprintf(buf, format, args);
    printf("[%s] %s\n", format_timestamp(&now), buf);
    va_end(args);

    fflush(stdout);
    fflush(stderr);
}

String format_timestamp(time_t* time){
    static char time_bf[BUF_LEN];
    struct tm* tm = localtime(time);
    sprintf(time_bf, "%d-%d-%d %dh %dm %ds", 
            tm -> tm_mday, 
            tm -> tm_mon + 1, 
            tm -> tm_year + 1900, 
            tm -> tm_hour, 
            tm -> tm_min, 
            tm -> tm_sec);

    return time_bf;
}

