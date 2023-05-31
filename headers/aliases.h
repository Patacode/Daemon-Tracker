#ifndef ALIASES_H
#define ALIASES_H

#include <sys/inotify.h>

typedef const char* String;
typedef int(*Predicate)(void*);
typedef void(*Function)(void);
typedef void* Object;
typedef struct inotify_event* Event;
typedef void(*EventHandler)(Event);

#endif

