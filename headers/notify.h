#ifndef NOTIFY_H
#define NOTIFY_H

#include "util.h"

extern int watch_mask;
extern int ifd;

/**
 * Setups inotify instance.
 */
void setup_inotify(void);

/**
 * Setups a watch on the file denoted by arg and adds it to the watch list
 * of inotify instance described by the given ifd.
 *
 * The path to the given file is constructed using the watch descriptor graph
 * starting at parent_wd.
 */
int setup_watch(int ifd, const char* arg, int parent_wd);

#endif

