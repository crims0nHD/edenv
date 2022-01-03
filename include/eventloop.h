#ifndef EVENTLOOP_H_
#define EVENTLOOP_H_

#include "util/ds.h"
#include <pthread.h>

struct evl_state {
  // Main event loop properties
  // Thread of event loop
  pthread_t evl_thread;

  // Event List
  // Lock for event list
  pthread_mutex_t evl_evlist_lock;
  // Linked Hash table of events
};

struct event {
  // Name
  char *name;
  // List of functions to run
  llnode_t *functions_list;
  // Event trigger
  // TODO
};

struct evl_state evl_create();
int evl_delete(struct evl_state *evl);

int evl_register_event(struct event *event);
int evl_unregister_event(char *name);
struct event *evl_get_event(char *name);

#endif // EVENTLOOP_H_
