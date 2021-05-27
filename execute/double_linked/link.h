#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100

typedef int Element;

Element data[MAX_LIST_SIZE];

// NodePointer head, tail;//노드의 head와 tail 새로운 노드
// NodePointer new;

typedef struct  t_node{
    Element data;
    struct t_node *prev;
    struct t_node *next;

}       s_node;