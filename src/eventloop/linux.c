#ifdef __LINUX__
#include "ds.h"
#include "eventloop.h"
#include <stdlib.h>
#include <sys/eventfd.h>

struct event *ev_create(const char *name) {
  struct event *ev = malloc(sizeof(struct event));
  ev->name = malloc(sizeof(char) * (strlen(name) + 1));
  ev->functions_list = NULL;
  ev->handle = malloc(sizeof(union eventHandle));
  ev->handle->linux_eventfd = eventfd(0, 0); // TODO
  return ev;
}

#endif
