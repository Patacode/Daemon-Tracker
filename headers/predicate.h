#ifndef PREDICATE_H
#define PREDICATE_H

#include "aliases.h"

/**
 * Checks if the value pointed to by value
 * is negative.
 */
int is_negative(void* value);

/**
 * Checks if value points to nothing.
 */
int is_null(void* value);

#endif

