#include <stdlib.h>

#include "app.h"

int main(int argc, char** argv){
    setup_signals();
    setup_signal_callbacks_factory();
    setup_signal_handlers();
    setup_mask();
    setup_events();
    setup_event_callbacks_factory();
    setup_graph();
    setup_env(getenv(DPATH));
    setup_inotify();
    setup_watch(ifd, "log", -1);
    start_tracker();
}

