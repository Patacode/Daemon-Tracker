#include <sys/inotify.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "lifecycle.h"

const int INTS_SIGNALS[] = {SIGTERM};
const int INTS_SIGNAL_QTY = 1;
const named_single INTS_EVENTS[] = {
    {"IN_CREATE", IN_CREATE}, 
    {"IN_DELETE", IN_DELETE}, 
    {"IN_ATTRIB", IN_ATTRIB},
    {"IN_MODIFY", IN_MODIFY},
    {"IN_ACCESS", IN_ACCESS},
};
const int INTS_EVENT_QTY = 5;

Function signal_callbacks[SIGNAL_QTY];
Function signal_handlers[SIGNAL_QTY];

CustomHashmap event_map;



// ============== SIGNAL ===============

void setup_signals(void){
    struct sigaction action;
    
    /* action to be used */
    action.sa_handler = signal_handler; // action callback
    action.sa_flags = SA_RESTART; // action flag
    sigfillset(&action.sa_mask); // action mask

    /* register signal handler */
    for(int i = 0; i < INTS_SIGNAL_QTY; i++){
        sigaction(INTS_SIGNALS[i], &action, NULL);
    }
}

void setup_signal_callbacks_template(int nargs, ...){
    va_list args;

    va_start(args, nargs);
    for(int i = 0; i < nargs; i++){
        signal_callbacks[INTS_SIGNALS[i]] = (Function) va_arg(args, Object);
    }

    va_end(args);
}

void setup_signal_callbacks_factory(void){
    setup_signal_callbacks_template(INTS_SIGNAL_QTY, sigterm_handler_factory);
}

void setup_signal_callbacks_observer(void){
    setup_signal_callbacks_template(INTS_SIGNAL_QTY, sigterm_handler_observer);
}

void setup_signal_handlers(void){
    for(int i = 0; i < INTS_SIGNAL_QTY; i++){
        signal_handlers[INTS_SIGNALS[i]] = signal_callbacks[INTS_SIGNALS[i]];
    }
}

void sigterm_handler_template(int nargs, ...){
    va_list args;

    va_start(args, nargs);
    flush_printf("Cleaning up resources...", 0);
    hashmap_free(wd_graph, HASHMAP_LEN);
    flush_printf("Watch descriptor graph freed up...", 0);
    hashmap_custom_free(event_map, HASHMAP_LEN);
    flush_printf("Event map freed up...", 0);
    close(ifd);
    flush_printf("Inotify instance closed...", 0);

    for(int i = 0; i < nargs; i++){
        ((Function) va_arg(args, Object))();
    }

    va_end(args);
    exit(EXIT_SUCCESS);
}

void sigterm_handler_factory(void){
    sigterm_handler_template(0);
}

void sigterm_handler_observer(void){
    void wrapper(void){flush_tsprintf("Daemon ended", 0);}
    sigterm_handler_template(1, wrapper);
}

void signal_handler(int signal){
    signal_handlers[signal]();
}



// ============== EVENT ===============

void setup_mask(void){
    int mask = 0;
    for(int i = 0; i < INTS_EVENT_QTY; i++){
        mask |= INTS_EVENTS[i].value;
    }

    watch_mask = mask;
}

void setup_events(void){
    event_map = hashmap_custom_create(HASHMAP_LEN);
    hashmap_custom_init(event_map, HASHMAP_LEN);
}

void setup_event_callbacks_template(int nargs, ...){
    va_list args;

    va_start(args, nargs);
    for(int i = 0; i < nargs; i++){
        EventHandler callback = (EventHandler) va_arg(args, Object);
        hashmap_custom_add(event_map, HASHMAP_LEN, INTS_EVENTS[i].name, INTS_EVENTS[i].value, callback);
    }

    va_end(args);
}

void setup_event_callbacks_factory(void){
    setup_event_callbacks_template(INTS_EVENT_QTY, 
            increate_handler_factory, 
            indelete_handler_factory, 
            inattrib_handler_factory,
            inmodify_handler_factory,
            inaccess_handler_factory);
}

void setup_event_callbacks_observer(void){
    setup_event_callbacks_template(INTS_EVENT_QTY, 
            increate_handler_observer, 
            indelete_handler_observer,
            inattrib_handler_observer,
            inmodify_handler_observer,
            inaccess_handler_observer);
}

void increate_handler_factory(Event event){
    String path;
    
    if(event -> mask & IN_ISDIR){
        flush_printf("Directory '%s' created", 1, event -> name);
        setup_watch(ifd, event -> name, event -> wd);
        flush_printf("New watch placed on directory '%s'", 1, event -> name);
    } else{
        flush_printf("File '%s' created", 1, event -> name);
        path = to_path(event -> name);
        if(is_valid_path(path)){
            create_forking_daemon(event -> name, path, event -> wd);
        } else{
            flush_printf("The created file name denotes an invalid path name. No tracker created.", 0);
        }
    }
}

void increate_handler_observer(Event event){
    if(event -> mask & IN_ISDIR){
        flush_tsprintf("Directory '%s' created", 1, event -> name);
        if(!setup_watch(ifd, event -> name, event -> wd))
            flush_tsprintf("New watch placed on directory '%s'", 1, event -> name);
    } else{
        flush_tsprintf("File '%s' created", 1, event -> name);
    }
}

void indelete_handler_factory(Event event){
    if(event -> mask & IN_ISDIR){
        flush_printf("Directory '%s' deleted", 1, event -> name);
    } else{
        flush_printf("File '%s' deleted", 1, event -> name);
    }
}

void indelete_handler_observer(Event event){
    if(event -> mask & IN_ISDIR){
        flush_tsprintf("Directory '%s' deleted", 1, event -> name);
    } else{
        flush_tsprintf("File '%s' deleted", 1, event -> name);
    }
}

void inattrib_handler_factory(Event event){
    if(event -> mask & IN_ISDIR){
        flush_printf("Directory's metadata '%s' changed", 1, event -> name);
    } else{
        flush_printf("File's metadata '%s' changed", 1, event -> name);
    }
}

void inattrib_handler_observer(Event event){
    if(event -> mask & IN_ISDIR){
        flush_tsprintf("Directory's metadata '%s' changed", 1, event -> name);
    } else{
        flush_tsprintf("File's metadata '%s' changed", 1, event -> name);
    }
}

void inmodify_handler_factory(Event event){
    flush_printf("File '%s' modified", 1, event -> name);
}

void inmodify_handler_observer(Event event){
    flush_tsprintf("File '%s' modified", 1, event -> name);
}

void inaccess_handler_factory(Event event){
    if(event -> mask & IN_ISDIR){
        flush_printf("Directory '%s' accessed", 1, event -> name);
    } else{
        flush_printf("File '%s' accessed", 1, event -> name);
    }
}

void inaccess_handler_observer(Event event){
    if(event -> mask & IN_ISDIR){
        flush_tsprintf("Directory '%s' accessed", 1, event -> name);
    } else{
        flush_tsprintf("File '%s' accessed", 1, event -> name);
    }
}

void consume_event(Event event){
    for(int i = 0; i < INTS_EVENT_QTY; i++){
        if(event -> mask & INTS_EVENTS[i].value && event -> len > 0){
            CustomPair event_value = hashmap_custom_get(event_map, HASHMAP_LEN, INTS_EVENTS[i].value);
            ((EventHandler) event_value -> right)(event);
        }
    }
}




// ============== DAEMON ===============

void start_tracker(void){
    int readed_bytes; // number of bytes readed from ifd
    int buf_pointer; // pointer to current inotify event
    char buf[BUF_LEN] __attribute__((aligned(4))); // buffer of inotify events

    for(;;){
        buf_pointer = 0;
        readed_bytes = read(ifd, buf, BUF_LEN);
        while(buf_pointer < readed_bytes){
            Event event = (Event) &buf[buf_pointer];
            consume_event(event);
            buf_pointer += sizeof(struct inotify_event) + event -> len;
        }
    }
}

void create_forking_daemon(String dot_name, String watched_path, int parent_wd){
    int pid;

    pid = fork();
    handle_error_errno(&pid, is_negative, "fork controller");
    if(pid == 0){ // process to create sub-daemon (the controller)
        init_forking_daemon(dot_name, watched_path, parent_wd);
    }
}

void init_forking_daemon(String dot_name, String watched_path, int parent_wd){
    String log_file;
    String path;

    log_file = create_path(dot_name, parent_wd);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    open(NULL_FILE, O_RDONLY); /* 0 = stdin */
    open(log_file, O_WRONLY); /* 1 = stdout */
    open(log_file, O_RDWR); /* 2 = stderr */

    hashmap_free(wd_graph, HASHMAP_LEN);
    hashmap_custom_free(event_map, HASHMAP_LEN);

    setup_events();
    setup_event_callbacks_observer();
    setup_signal_callbacks_observer();
    setup_signal_handlers();
    setup_graph();
    setup_env(extract_pdt(watched_path));
    setup_inotify();
    setup_watch(ifd, extract_watched_dir(watched_path), -1);
    
    flush_tsprintf("Daemon tracker started on '%s' !\n", 1, watched_path);
    start_tracker();
}

void kill_sub_daemons(void){
    FILE* handle;
    char* line;
    size_t len;

    handle = fopen(getenv(PID_FILE), "r");
    handle_error_errno(handle, is_null, "fopen pid file");
    while(getline(&line, &len, handle) != -1){
        long pid = strtol(line, NULL, 10);
        kill(pid, SIGTERM);
    }

    fclose(handle);
}

