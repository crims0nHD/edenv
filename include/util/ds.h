#ifndef DS_H_
#define DS_H_

// Linked list
struct linked_list_node {
  void *content;
  struct linked_list_node *next;
  struct linked_list_node *prev;
};
typedef struct linked_list_node llnode_t;

void llist_node_delete(llnode_t *node);
llnode_t *llist_node_add_after(llnode_t *node_prev);
llnode_t *llist_node_add_before(llnode_t *node_next);

// Linked Hash table
typedef struct linked_hash_table_key_value_pair {
  char *key;
  void *value;
} lht_kvpair_t;

typedef struct linked_hash_table {
  unsigned int length;
  llnode_t **entries;
} lht_t;

unsigned int lht_hash_function(const char *str, const unsigned int length);

lht_t *lhtable_create(unsigned int length);
void lhtable_delete(lht_t *table);

void *lhtable_get_entry(const char *str, lht_t *lht);
void lhtable_set_entry(const char *str, void *val, lht_t *lht);
int lhtable_delete_entry(const char *str, lht_t *lht);

#endif // DS_H_
