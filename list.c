#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
    return lista;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev; 
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node * nuevoNodo = createNode(data);
    if (list->head == NULL) {
        list->head = nuevoNodo;
        list->tail = nuevoNodo;
    } else {
        nuevoNodo->next = list->head;
        list->head->prev = nuevoNodo;
        list->head = nuevoNodo;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->current == NULL) return;

    Node * nuevoNodo = createNode(data);
    nuevoNodo->prev = list->current;
    nuevoNodo->next = list->current->next;
    if (list->current->next != NULL) {
        list->current->next->prev = nuevoNodo;
    } else {
        list->tail = nuevoNodo;
    }
    
    list->current->next = nuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if (list->current == NULL) return NULL;
    
    void * eliminar = list->current->data;

    if (list->current->prev != NULL) {
        list->current->prev->next = list->current->next;
    } else {
        list->head = list->current->next;
    }

    if (list->current->next != NULL) {
        list->current->next->prev = list->current->prev;
    } else {
        list->tail = list->current->prev;
    }

    Node * auxiliar = list->current;
    list->current = list->current->next;

    free(auxiliar);
    return eliminar;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}