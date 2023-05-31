#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include <sys/inotify.h>

#include "notify.h"

extern const int INTS_SIGNALS[];
extern const int INTS_SIGNAL_QTY;
extern const named_single INTS_EVENTS[];
extern const int INTS_EVENT_QTY;

extern void (*signal_handlers[SIGNAL_QTY])(void);
extern void (*signal_callbacks[SIGNAL_QTY])(void);

extern custom_linked_list** event_map;



// =============== SIGNAL =================

/**
 * Setups action callbacks to desired signals 
 * for the calling process.
 */
void setup_signals(void);

/**
 * Template for the 'setup_signal_callbacks_*' functions.
 */
void setup_signal_callbacks_template(int nargs, ...);

/**
 * Setups factory signal callbacks.
 */
void setup_signal_callbacks_factory(void);

/**
 * Setups observer signal callbacks.
 */
void setup_signal_callbacks_observer(void);

/**
 * Setups signal handlers by linking each callback to 
 * its corresponding signal handler.
 */
void setup_signal_handlers(void);

/**
 * Template for the 'sigterm_handler_*' functions. 
 */
void sigterm_handler_template(int nargs, ...);

/**
 * Handler function for the sigterm signal received by
 * a factory.
 */
void sigterm_handler_factory(void);

/**
 * Handler function for the sigterm signal received
 * by an observer.
 */
void sigterm_handler_observer(void);

/**
 * Global handler function receiving the signal value.
 */
void signal_handler(int signal);





// =============== EVENT =================

/**
 * Setups event mask to be used on watch file/dir.
 */
void setup_mask(void);

/**
 * Setups event map by assigning a callback to each
 * corresponding inotify event type.
 */
void setup_events(void);

/**
 * Template for 'setup_event_callbacks_*' functions.
 */
void setup_event_callbacks_template(int nargs, ...);

/**
 * Setups factory event callbacks.
 */
void setup_event_callbacks_factory(void);

/**
 * Setups observer event callbacks.
 */
void setup_event_callbacks_observer(void);

/**
 * Event handler for the IN_CREATE event (factory version).
 */
void increate_handler_factory(struct inotify_event* event);

/**
 * Event handler for the IN_CREATE event (observer version).
 */
void increate_handler_observer(struct inotify_event* event);

/**
 * Event handler for the IN_DELETE event (factory version).
 */
void indelete_handler_factory(struct inotify_event* event);

/**
 * Event handler for the IN_DELETE event (observer version).
 */
void indelete_handler_observer(struct inotify_event* event);

/**
 * Event handler for the IN_ATTRIB event (factory version).
 */
void inattrib_handler_factory(struct inotify_event* event);

/**
 * Event handler for the IN_ATTRIB event (observer version).
 */
void inattrib_handler_observer(struct inotify_event* event);

/**
 * Event handler for the IN_MODIFY event (factory version).
 */
void inmodify_handler_factory(struct inotify_event* event);

/**
 * Event handler for the IN_MODIFY event (observer version).
 */
void inmodify_handler_observer(struct inotify_event* event);

/**
 * Event handler for the IN_ACCESS event (factory version).
 */
void inaccess_handler_factory(struct inotify_event* event);

/**
 * Event handler for the IN_ACCESS event (observer version).
 */
void inaccess_handler_observer(struct inotify_event* event);

/**
 * Consumes the given inotify event.
 */
void consume_event(struct inotify_event* event);





// =============== DAEMON =================

/**
 * Starts the tracker daemon work.
 */
void start_tracker(void);

/**
 * Creates a tracker daemon using the double-forking technique. This daemon will track
 * the file/directory denoted by the given watch_path.
 */
void create_forking_daemon(const char* dot_name, const char* watched_path, int parent_wd);

/**
 * Initializes a previously created forking daemon to track the given watched path.
 */
void init_forking_daemon(const char* dot_name, const char* watched_path, int parent_wd);

/**
 * Kills all the existing tracker daemons.
 */
void kill_sub_daemons(void);

#endif

