#pragma once

#include "dfa/dfa/dfa.h"
#include <pthread.h>

#define MAX_DICT_NAME_LENGTH 64

typedef struct _dict {
    char name[MAX_DICT_NAME_LENGTH];
    dfa_trie_t *trie;
    int count;
    pthread_rwlock_t rwlock;
    struct _dict *next;
} dict_t;

#define felis_dict_rlock(dict) pthread_rwlock_rdlock(&dict->rwlock)
#define felis_dict_wlock(dict) pthread_rwlock_wrlock(&dict->rwlock)
#define felis_dict_unlock(dict) pthread_rwlock_unlock(&dict->rwlock)

#define FOREACH_DICTS(head, dict) \
    for ((dict) = (head); (dict) != NULL; (dict) = ((dict)->next))

dict_t *dict_new(char *name);
dict_t *dict_find(dict_t *head, char *name);
void dict_destroy(dict_t *dict);
