#include "util/ds.h"
#include <stddef.h>
#include <stdlib.h>

llnode_t *llist_node_add_after(llnode_t *node_prev) {
  llnode_t *nnew = calloc(sizeof(llnode_t), 1);
  // in case of node_prev being NULL, return a empty node
  if (node_prev == NULL)
    return nnew;
  // set properties of new node
  nnew->prev = node_prev;
  nnew->next = node_prev->next;
  // set properties of existing node before and after the new node
  if (node_prev->next != NULL)
    node_prev->next->prev = nnew;
  node_prev->next = nnew;
  return nnew;
}

llnode_t *llist_node_add_before(llnode_t *node_next) {
  llnode_t *nnew = calloc(sizeof(llnode_t), 1);
  // in case of node_prev being NULL, return a empty node
  if (node_next == NULL)
    return nnew;
  // set properties of new node
  nnew->next = node_next;
  nnew->prev = node_next->prev;
  // set properties of existing node before and after the new node
  if (node_next->prev != NULL)
    node_next->prev->next = nnew;
  node_next->prev = nnew;
  return nnew;
}

void llist_node_delete(llnode_t *node) {
  llnode_t *next, *prev;
  next = node->next;
  prev = node->prev;
  free(node);
  next->prev = prev;
  prev->next = next;
}

unsigned int lht_hash_function(const char *str, const unsigned int length) {
  // djb2
  unsigned int result = 5381;
  int c;
  while (c = (int)(*str++))
    result = ((result << 5) + result) + c;
  return result % length;
}

lht_t *lhtable_create(unsigned int length) {
  lht_t *ret = malloc(sizeof(lht_t));
  ret->length = length;
  ret->entries = calloc(sizeof(lht_entry_t *), length);
  return ret;
}

void lhtable_delete(lht_t *table) {
  // Delete entries
  for (unsigned int i = 0; i < table->length; i++) {
  }
  // Delete table
}
