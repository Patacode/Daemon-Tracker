#include <sys/inotify.h>
#include <stdio.h>

#include "notify.h"

int watch_mask;
int ifd;

void setup_inotify(void){
    ifd = inotify_init();
    handle_error_errno(&ifd, is_negative, "inotify_init");
}

int setup_watch(int ifd, String arg, int parent_wd){
    int wd;

    String path = create_path(arg, parent_wd);
    wd = inotify_add_watch(ifd, path, watch_mask);
    if(wd < 0){
        flush_printf("Cannot place watch on '%s'", 1, path);
        return -1;
    }

    hashmap_add(wd_graph, HASHMAP_LEN, arg, wd, parent_wd);
    return 0;
}

