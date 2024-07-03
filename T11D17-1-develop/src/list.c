#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

struct node* init(struct door* door) {
    struct node* elem = (struct node*)malloc(sizeof(struct node));
    elem->doors = door;
    elem->next = NULL;
    return elem;
}

struct node* add_door(struct node* elem, struct door* door) {
    struct node* root = (struct node*)malloc(sizeof(struct node));
    root->doors = door;
    elem->next = root;
    root->next = NULL;

    return root;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* root_tmp = root;
    while (root_tmp) {
        if (root_tmp->doors->id == door_id)
            break;
        else
            root_tmp = root_tmp->next;
    }

    return root_tmp;
}

struct node* remove_door(struct node* elem, struct node* root) {
    struct node* root_tmp = root;
    if (root_tmp == elem) {
        root_tmp = root_tmp->next;
        free(elem);
    } else {
        struct node* root_prev = root;
        while (root_tmp != elem) {
            root_prev = root_tmp;
            root_tmp = root_tmp->next;
        }
        root_prev->next = root_tmp->next;
        free(root_tmp);
        root_tmp = root_prev->next;
    }
    return root_tmp;
}

void destroy(struct node* root) {
    while (root != NULL) root = remove_door(root, root);
}

void output(struct node* root) {
    while (root != NULL) {
        printf("%p %d %d\n", root->next, root->doors->id, root->doors->status);
        root = root->next;
    }
}