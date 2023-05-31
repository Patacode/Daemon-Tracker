#ifndef ENV_H
#define ENV_H

#include "sconst.h"
#include "error.h"
#include "predicate.h"

extern const char* pdt;

/**
 * Setups environment path.
 */
void setup_env(const char* env_path);

#endif

