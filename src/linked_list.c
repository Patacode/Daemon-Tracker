#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "linked_list.h"

void linkedlist_print(LinkedList list){
    if(list == NULL){
        printf("NULL\n");
        return;
    }

    Node current_node = list -> head;
    if(current_node == NULL)
        printf("empty\n");

    while(current_node != NULL){
        printf(current_node -> next_node != NULL ? "{%s, %d, %d} -> " : "{%s, %d, %d}\n",
                current_node -> value.name,
                current_node -> value.left, 
                current_node -> value.right);

        current_node = current_node -> next_node;
    }
}

void linkedlist_custom_print(CustomLinkedList custom_list){
    if(custom_list == NULL){
        printf("NULL\n");
        return;
    }

    CustomNode current_node = custom_list -> head;
    if(current_node == NULL)
        printf("empty\n");

    while(current_node != NULL){
        printf(current_node -> next_node != NULL ? "{%s, %d, %p} -> " : "{%s, %d, %p}\n",
                current_node -> value.name,
                current_node -> value.left, 
                current_node -> value.right);

        current_node = current_node -> next_node;
    }
}

LinkedList linkedlist_create(void){
    LinkedList list = malloc(sizeof(linked_list));
    list -> head = NULL;
    list -> queue = NULL;
    return list;
}

CustomLinkedList linkedlist_custom_create(void){
    CustomLinkedList custom_list = malloc(sizeof(custom_linked_list));
    custom_list -> head = NULL;
    custom_list -> queue = NULL;
    return custom_list;
}

void linkedlist_add(LinkedList list, String name, int key, int value){
    if(list -> head == NULL){ // no element yet
        list -> head = list -> queue = node_create(name, key, value);
        return;
    }

    list -> queue -> next_node = node_create(name, key, value);
    list -> queue -> next_node -> previous_node = list -> queue;
    list -> queue = list -> queue -> next_node;
}

void linkedlist_custom_add(CustomLinkedList custom_list, String name, int key, Object value){
    if(custom_list -> head == NULL){ // no element yet
        custom_list -> head = custom_list -> queue = node_custom_create(name, key, value);
        return;
    }

    custom_list -> queue -> next_node = node_custom_create(name, key, value);
    custom_list -> queue -> next_node -> previous_node = custom_list -> queue;
    custom_list -> queue = custom_list -> queue -> next_node;
}

void linkedlist_delete(LinkedList list, int key){
    Node current_node = list -> head;
    if(current_node == NULL){ // list is empty
        errno = EINVAL;
        return;
    }

    // first node
    if(current_node -> value.left == key){
        list -> head = current_node -> next_node;
        if(current_node == list -> queue){ // list has one element
            list -> queue = NULL;
        } else{ // list has more than one element
            list -> head -> previous_node = NULL;
        }

        free(current_node);
        return;
    }

    current_node = current_node -> next_node;
    while(current_node != NULL){
        if(current_node -> value.left == key){
            current_node -> previous_node -> next_node = current_node -> next_node;
            if(current_node -> next_node != NULL) // found node is not the last
                current_node -> next_node -> previous_node = current_node -> previous_node;

            free(current_node);
            return;
        }

        current_node = current_node -> next_node;
    }

    errno = EINVAL;
}

void linkedlist_custom_delete(CustomLinkedList custom_list, int key){
    CustomNode current_node = custom_list -> head;
    if(current_node == NULL){ // list is empty
        errno = EINVAL;
        return;
    }

    // first node
    if(current_node -> value.left == key){
        custom_list -> head = current_node -> next_node;
        if(current_node == custom_list -> queue){ // list has one element
            custom_list -> queue = NULL;
        } else{ // list has more than one element
            custom_list -> head -> previous_node = NULL;
        }

        free(current_node);
        return;
    }

    current_node = current_node -> next_node;
    while(current_node != NULL){
        if(current_node -> value.left == key){
            current_node -> previous_node -> next_node = current_node -> next_node;
            if(current_node -> next_node != NULL) // found node is not the last
                current_node -> next_node -> previous_node = current_node -> previous_node;

            free(current_node);
            return;
        }

        current_node = current_node -> next_node;
    }

    errno = EINVAL;
}

Pair linkedlist_get(LinkedList list, int key){
    Node current_node = list -> head;
    while(current_node != NULL){
        if(current_node -> value.left == key)
            return &current_node -> value;

        current_node = current_node -> next_node;
    }

    errno = EINVAL;
    return NULL;
}

CustomPair linkedlist_custom_get(CustomLinkedList custom_list, int key){
    CustomNode current_node = custom_list -> head;
    while(current_node != NULL){
        if(current_node -> value.left == key)
            return &current_node -> value;

        current_node = current_node -> next_node;
    }

    errno = EINVAL;
    return NULL;
}

void linkedlist_free(LinkedList list){
    Node current_node = list -> head;
    while(current_node != NULL){
        Node next_node = current_node -> next_node;
        free(current_node -> value.name);
        free(current_node);
        current_node = next_node;
    }

    free(list);
}

void linkedlist_custom_free(CustomLinkedList custom_list){
    CustomNode current_node = custom_list -> head;
    while(current_node != NULL){
        CustomNode next_node = current_node -> next_node;
        free(current_node -> value.name);
        free(current_node);
        current_node = next_node;
    }

    free(custom_list);
}

Node node_create(String name, int key, int value){
    Node new_node = malloc(sizeof(bidi_node));
    char* new_node_name = malloc(sizeof(char) * strlen(name) + sizeof(char));
    strcpy(new_node_name, name);

    new_node -> next_node = NULL;
    new_node -> previous_node = NULL;
    new_node -> value.name = new_node_name;
    new_node -> value.left = key;
    new_node -> value.right = value;

    return new_node;
}

CustomNode node_custom_create(String name, int key, Object value){
    CustomNode new_node = malloc(sizeof(custom_bidi_node));
    char* new_node_name = malloc(sizeof(char) * strlen(name) + sizeof(char));
    strcpy(new_node_name, name);

    new_node -> next_node = NULL;
    new_node -> previous_node = NULL;
    new_node -> value.name = new_node_name;
    new_node -> value.left = key;
    new_node -> value.right = value;

    return new_node;
}

