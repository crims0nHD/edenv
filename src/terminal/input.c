#include "terminal/input.h"
#include "util/ds.h"
#include <stdlib.h>

llnode_t *input_queue;

struct term_input_seq t_get_input() {
  struct term_input_seq s;
  memcpy(&s, input_queue->content, sizeof(struct term_input_seq));
  llnode_t *n = input_queue->next;
  llist_node_delete(input_queue);
  input_queue = n;
  return s;
}

static void update_inputs() {}
