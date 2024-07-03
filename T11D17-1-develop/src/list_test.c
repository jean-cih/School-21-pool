#include "list.h"

#include <stdio.h>

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);

    struct node *elem = init(&doors[0]);
    struct node *first_elem = elem;
    for (int i = 1; i < DOORS_COUNT; i++) elem = add_door(elem, &doors[i]);

    elem = first_elem;
    output(elem);

    if (doors[DOORS_COUNT - 1].id < 15)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    struct node *root = find_door(10, first_elem);
    if (root != NULL)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    root = remove_door(root, first_elem);

    int i = 0;
    root = first_elem;
    while (root != NULL) {
        root = root->next;
        i++;
    }
    if (i == DOORS_COUNT - 1)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");

    destroy(first_elem);

    return 0;
}