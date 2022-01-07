#include "util/ds.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  ret->entries = calloc(sizeof(llnode_t *), length);
  return ret;
}

void lhtable_delete(lht_t *table) {
  // Delete entries
  for (unsigned int i = 0; i < table->length; i++) {
    llnode_t *n = table->entries[i], *next;
    if (n == NULL)
      continue;
    // Iterate over linked list of an entry
    while (next = n->next) {
      lht_kvpair_t *kvpair = n->content;
      free(kvpair->key);
      free(kvpair);
      free(n);
      n = next;
    }
  }
  // Delete table
  free(table->entries);
  free(table);
}

void *lhtable_get_entry(const char *str, lht_t *lht) {
  unsigned int index = lht_hash_function(str, lht->length);
  llnode_t *entry = lht->entries[index];
  if (entry->next == NULL)
    return ((lht_kvpair_t *)entry->content)->value;
  else {
    do {
      lht_kvpair_t *kpair = entry->content;
      if (strcmp(kpair->key, str))
        return kpair->value;
    } while (entry = entry->next);
  }
  // NULL is default value for anything not found in the table
  return NULL;
}

void lhtable_set_entry(const char *str, void *val, lht_t *lht) {
  unsigned int index = lht_hash_function(str, lht->length);
  llnode_t **newentry = &(lht->entries[index]);
  if (*newentry != NULL) {
    while ((*newentry)->next != NULL)
      newentry = &((*newentry)->next);
  }

  (*newentry) = llist_node_add_after(NULL);
  (*newentry)->content = malloc(sizeof(lht_kvpair_t));
  lht_kvpair_t *kpair = (*newentry)->content;
  kpair->key = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(kpair->key, str);
  kpair->value = val;
}

int lhtable_delete_entry(const char *str, lht_t *lht) {
  unsigned int index = lht_hash_function(str, lht->length);
  llnode_t *entry = lht->entries[index];
  if (entry->next == NULL)
    return 1;
  else {
    do {
      lht_kvpair_t *kpair = entry->content;
      if (strcmp(kpair->key, str)) {
        free(kpair->key);
        free(kpair);
        if (entry->next == NULL) {
          if (entry->prev == NULL) {
            lht->entries[index] = NULL;
          } else {
            lht->entries[index] = entry->prev;
          }
        } else {
          lht->entries[index] = entry->next;
        }
        llist_node_delete(entry);
        return 0;
      }
    } while (entry = entry->next);
  }
  return 1;
}
