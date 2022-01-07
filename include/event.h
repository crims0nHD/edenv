#ifndef EVENT_H_
#define EVENT_H_

#include "util/ds.h"

// Platform specific event implementations
#ifdef __LINUX__
#include <sys/eventfd.h>
#endif

union eventHandle {
#ifdef __LINUX__
  eventfd_t *linux_eventfd;
#endif
};

struct event {
  // Name
  char *name;
  // List of functions to run
  llnode_t *functions_list;
  // Event trigger
  union eventHandle *handle;
};

struct event *ev_create(const char *name);
void ev_delete(struct event *e);

int ev_add_function(void (*fun)());
int ev_remove_function(void (*fun)());

int ev_call_event(struct event *e); // Returns ammount of functions run

#endif // EVENT_H_
