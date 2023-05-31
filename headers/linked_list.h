#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "env.h"

/**
 * A named single providing one value as well as
 * a name.
 */
typedef struct named_single{
    char name[NAME_LEN];
    int value;
} named_single;

/**
 * A named single providing one value as well as
 * a name.
 *
 * Custom version.
 */
typedef struct custom_named_single{
    char name[NAME_LEN];
    void* value;
} custom_named_single;

/**
 * A named pair providing two values (left and right) 
 * as well as a name.
 */
typedef struct named_pair{
    char* name;
    int left;
    int right;
} named_pair;

/**
 * A named pair providing two values (left and right) 
 * as well as a name.
 *
 * Custom version.
 */
typedef struct custom_named_pair{
    char* name;
    int left;
    void* right;
} custom_named_pair;

/**
 * Bidirectional node.
 */
typedef struct bidi_node{
    named_pair value;
    struct bidi_node* next_node;
    struct bidi_node* previous_node;
} bidi_node;

/**
 * Custom bidirectional node.
 */
typedef struct custom_bidi_node{
    custom_named_pair value;
    struct custom_bidi_node* next_node;
    struct custom_bidi_node* previous_node;
} custom_bidi_node;

/**
 * Non-circular linked list.
 */
typedef struct linked_list{
    bidi_node* head;
    bidi_node* queue;
} linked_list;

/**
 * Custom non-circular linked list.
 */
typedef struct custom_linked_list{
    custom_bidi_node* head;
    custom_bidi_node* queue;
} custom_linked_list;

// some useful aliases
typedef linked_list** Hashmap;
typedef custom_linked_list** CustomHashmap;
typedef linked_list* LinkedList;
typedef custom_linked_list* CustomLinkedList;
typedef bidi_node* Node;
typedef custom_bidi_node* CustomNode;
typedef named_pair* Pair;
typedef custom_named_pair* CustomPair;



// ============== INTEGER VERSION ===============

/**
 * Prints the given linked list to file descriptor 1 (stdout by default).
 */
void linkedlist_print(linked_list* list);

/**
 * Creates a linked list (must be freed afterwards).
 */
linked_list* linkedlist_create(void);

/**
 * Adds a named pair to the given linked list.
 */
void linkedlist_add(linked_list* list, const char* name, int key, int value);

/**
 * Deletes the first element found having a matching key from the 
 * given linked list.
 */
void linkedlist_delete(linked_list* list, int key);

/**
 * Gets the first element found having a matching key from the
 * given linked list.
 */
named_pair* linkedlist_get(linked_list* list, int key);

/**
 * Frees the given linked list.
 */
void linkedlist_free(linked_list* list);

/**
 * Creates a node wrapping a named pair (must be freed afterwards).
 */
bidi_node* node_create(const char* name, int key, int value);





// ============== CUSTOM VERSION ===============

/**
 * Prints the given linked list to file descriptor 1 (stdout by default).
 *
 * Custom version.
 */
void linkedlist_custom_print(custom_linked_list* custom_list);

/**
 * Creates a linked list (must be freed afterwards).
 *
 * Custom version.
 */
custom_linked_list* linkedlist_custom_create(void);

/**
 * Adds a named pair to the given linked list.
 *
 * Custom version.
 */
void linkedlist_custom_add(custom_linked_list* custom_list, const char* name, int key, void* value);

/**
 * Deletes the first element found having a matching key from the 
 * given linked list.
 *
 * Custom version.
 */
void linkedlist_custom_delete(custom_linked_list* custom_list, int key);

/**
 * Gets the first element found having a matching key from the
 * given linked list.
 *
 * Custom version.
 */
custom_named_pair* linkedlist_custom_get(custom_linked_list* custom_list, int key);

/**
 * Frees the given linked list.
 *
 * Custom version.
 */
void linkedlist_custom_free(custom_linked_list* custom_list);

/**
 * Creates a node wrapping a named pair (must be freed afterwards).
 *
 * Custom version.
 */
custom_bidi_node* node_custom_create(const char* name, int key, void* value);

#endif

