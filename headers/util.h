#ifndef UTIL_H
#define UTIL_H

#include <time.h>

#include "collections.h"

/**
 * Converts the name dot separators from the given name to slashes
 * and returns the result.
 */
const char* to_path(const char* dot_name);

/**
 * Extracts the daemon tracker sub-path from the given path and returns
 * the result.
 */
const char* extract_pdt(const char* path);

/**
 * Extracts the watched dir sub-path from the given path and returns the
 * result.
 */
const char* extract_watched_dir(const char* path);

/**
 * Reconstitutes and creates the path to arg starting at parent_wd.
 */
const char* create_path(const char* arg, int parent_wd);

/**
 * Checks if the given absolute path is valid and denotes an existing 
 * resource on the filesystem.
 */
int is_valid_path(const char* path);

/**
 * Acts as printf but systematically flush the buffer afterwards.
 */
void flush_printf(const char* format, int nargs, ...);

/**
 * Acts as flush_printf but always add a readable timestamp in front of the content
 * before outputting.
 */
void flush_tsprintf(const char* format, int nargs, ...);

/**
 * Transforms the given unix epoch timestamp in a human-readable format.
 */
const char* format_timestamp(time_t* time);

#endif

