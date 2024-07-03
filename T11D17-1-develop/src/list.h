#ifndef LIST_H
#define LIST_H

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

struct door {
    int id;
    int status;
};

struct node {
    struct door* doors;
    struct node* next;
};

void initialize_doors(struct door* doors);
struct node* init(struct door* door);
struct node* add_door(struct node* elem, struct door* door);
struct node* find_door(int door_id, struct node* root);
struct node* remove_door(struct node* elem, struct node* root);
void destroy(struct node* root);
void output(struct node* root);

#endif