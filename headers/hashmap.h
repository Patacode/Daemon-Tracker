#ifndef HASHMAP_H
#define HASHMAP_H

#include "linked_list.h"


// ============= INTEGER HASHMAP ===============

/**
 * Prints the given hashmap of size elements to file 
 * descriptor 1 (stdout by default)
 */
void hashmap_print(linked_list** hashmap, int size);

/**
 * Creates a hashmap of size elements (the returned hashmap 
 * must be freed afterwards).
 */
linked_list** hashmap_create(int size);

/**
 * Initializes the given hashmap of size 
 * elements (clear the hashmap).
 */
void hashmap_init(linked_list** list, int size);

/**
 * Adds a named pair to the given hashmap of size elements.
 */
void hashmap_add(linked_list** hashmap, int size, const char* name, int key, int value);

/**
 * Deletes the first element found having a matching key 
 * from the given hashmap of size elements.
 */
void hashmap_delete(linked_list** hashmap, int size, int key);

/**
 * Gets the first element found having a matching key
 * from the given hashamp of size elements.
 */
named_pair* hashmap_get(linked_list** hashmap, int size, int key);

/**
 * Frees the given hashmap of size elements properly.
 */
void hashmap_free(linked_list** hashmap, int size);





// ============= CUSTOM HASHMAP ===============

/**
 * Prints the given hashmap of size elements to file 
 * descriptor 1 (stdout by default).
 *
 * Custom version.
 */
void hashmap_custom_print(custom_linked_list** hashmap, int size);

/**
 * Creates a hashmap of size elements (the returned hashmap 
 * must be freed afterwards).
 *
 * Custom version.
 */
custom_linked_list** hashmap_custom_create(int size);

/**
 * Initializes the given hashmap of size 
 * elements (clear the hashmap).
 *
 * Custom version.
 */
void hashmap_custom_init(custom_linked_list** list, int size);

/**
 * Adds a named pair to the given hashmap of size elements.
 *
 * Custom version.
 */
void hashmap_custom_add(custom_linked_list** hashmap, int size, const char* name, int key, void* value);

/**
 * Deletes the first element found having a matching key 
 * from the given hashmap of size elements.
 *
 * Custom version.
 */
void hashmap_custom_delete(custom_linked_list** hashmap, int size, int key);

/**
 * Gets the first element found having a matching key
 * from the given hashamp of size elements.
 *
 * Custom version.
 */
custom_named_pair* hashmap_custom_get(custom_linked_list** hashmap, int size, int key);

/**
 * Frees the given hashmap of size elements properly.
 *
 * Custom version.
 */
void hashmap_custom_free(custom_linked_list** hashmap, int size);


// ============= COMMON FUNCTIONS ===============

/**
 * Gets hashcode value for the given key.
 */
int hashmap_hashcode(int key);

#endif

