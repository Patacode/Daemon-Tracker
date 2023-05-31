#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "hashmap.h"

void hashmap_print(Hashmap hashmap, int size){
    int i = 0;
    while(i < size){
        printf("%d: Linked List at '%p' = ", i, *(hashmap + i));
        linkedlist_print(*(hashmap + i));
        i++;
    }
}

void hashmap_custom_print(CustomHashmap custom_hashmap, int size){
    int i = 0;
    while(i < size){
        printf("%d: Linked List at '%p' = ", i, *(custom_hashmap + i));
        linkedlist_custom_print(*(custom_hashmap + i));
        i++;
    }
}

Hashmap hashmap_create(int size){
    return malloc(sizeof(LinkedList) * size);
}

CustomHashmap hashmap_custom_create(int size){
    return malloc(sizeof(CustomLinkedList) * size);
}

void hashmap_init(Hashmap hashmap, int size){
    int i = 0;
    while(i < size){
        *(hashmap + i) = NULL;
        i++;
    }
}

void hashmap_custom_init(CustomHashmap custom_hashmap, int size){
    int i = 0;
    while(i < size){
        *(custom_hashmap + i) = NULL;
        i++;
    }
}

void hashmap_add(Hashmap hashmap, int size, String name, int key, int value){
    int index = hashmap_hashcode(key) % size;
    if(*(hashmap + index) == NULL){ // no element
        *(hashmap + index) = linkedlist_create();
    }
    
    linkedlist_add(*(hashmap + index), name, key, value);
}

void hashmap_custom_add(CustomHashmap custom_hashmap, int size, String name, int key, Object value){
    int index = hashmap_hashcode(key) % size;
    if(*(custom_hashmap + index) == NULL){ // no element
        *(custom_hashmap + index) = linkedlist_custom_create();
    }
    
    linkedlist_custom_add(*(custom_hashmap + index), name, key, value);
}

void hashmap_delete(Hashmap hashmap, int size, int key){
    int index = hashmap_hashcode(key) % size;
    LinkedList element = *(hashmap + index);
    if(element != NULL){ // element could exists
        linkedlist_delete(element, key);
        return;
    }

    errno = EINVAL;
}

void hashmap_custom_delete(CustomHashmap custom_hashmap, int size, int key){
    int index = hashmap_hashcode(key) % size;
    CustomLinkedList element = *(custom_hashmap + index);
    if(element != NULL){ // element could exists
        linkedlist_custom_delete(element, key);
        return;
    }

    errno = EINVAL;
}

Pair hashmap_get(Hashmap hashmap, int size, int key){
    int index = hashmap_hashcode(key) % size;
    LinkedList element = *(hashmap + index);
    if(element != NULL){ // element could exists
        return linkedlist_get(element, key);
    }
    
    errno = EINVAL;
    return NULL;
}

CustomPair hashmap_custom_get(CustomHashmap custom_hashmap, int size, int key){
    int index = hashmap_hashcode(key) % size;
    CustomLinkedList element = *(custom_hashmap + index);
    if(element != NULL){ // element could exists
        return linkedlist_custom_get(element, key);
    }
    
    errno = EINVAL;
    return NULL;
}

void hashmap_free(Hashmap hashmap, int size){
    int i = 0;
    while(i < size){
        if(*(hashmap + i) != NULL){
            linkedlist_free(*(hashmap + i));
        }

        i++;
    }

    free(hashmap);
}

void hashmap_custom_free(CustomHashmap custom_hashmap, int size){
    int i = 0;
    while(i < size){
        if(*(custom_hashmap + i) != NULL){
            linkedlist_custom_free(*(custom_hashmap + i));
        }

        i++;
    }

    free(custom_hashmap);
}

int hashmap_hashcode(int key){
    return abs(key);
}


