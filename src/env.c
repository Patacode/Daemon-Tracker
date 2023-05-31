#include <stdlib.h>

#include "env.h"

String pdt;

void setup_env(const char* env_path){
    handle_error_custom((Object)env_path, is_null, "Envrionment path isn't set");
    pdt = env_path;
}

