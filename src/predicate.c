#include <stddef.h>

#include "predicate.h"

int is_negative(Object value){
    return (*((int*)value)) < 0;
}

int is_null(Object value){
    return (((char*)value)) == NULL;
}

