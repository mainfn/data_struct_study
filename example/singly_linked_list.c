#include <assert.h>
#include <printf.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    int val;
} Node;

typedef struct {
    Node* head;
    int len;
} SinglyLinkedList;

SinglyLinkedList new_singly_linked_list();
Node* new_node(int);
Node* get(SinglyLinkedList*, int);
void push(SinglyLinkedList*, int);
void insert(SinglyLinkedList*, int, int);
void remove_at(SinglyLinkedList*, int);
void drop_node(Node*);
void print_node(Node*, int);
void print_all_nodes(SinglyLinkedList*);

SinglyLinkedList new_singly_linked_list() {
    SinglyLinkedList s = {
        .len = 0,
        .head = NULL,
    };

    return s;
}

Node* new_node(int val) {
    Node* p_node = malloc(sizeof(Node));

    p_node->val = val;
    p_node->next = NULL;

    return p_node;
}

Node* get(SinglyLinkedList* s, int index) {
    assert(index < s->len);

    if (index < 0)
        return NULL;

    Node* cursor = s->head;

    for (int i = 0; i < index; i++) {
        cursor = cursor->next;
    }

    return cursor;
}

void push(SinglyLinkedList* s, int val) {
    Node* p_node = new_node(val);
    Node* p_last_node = get(s, s->len - 1);

    if (p_last_node == NULL)
        s->head = p_node;
    else
        p_last_node->next = p_node;

    s->len++;
}

void insert(SinglyLinkedList* s, int index, int val) {
    assert(index >= 0 && index <= s->len);

    Node* p_node = new_node(val);
    Node* p_prev_node = get(s, index - 1);

    if (p_prev_node == NULL) {
        p_node->next = s->head;
        s->head = p_node;
    }
    else {
        p_node->next = p_prev_node->next;
        p_prev_node->next = p_node;
    }

    s->len++;
}

void remove_at(SinglyLinkedList* s, int index) {
    assert(index >= 0 && index < s->len);

    Node* p_target_node;

    if (index == 0) {
        p_target_node = s->head;

        s->head = p_target_node->next;
    }
    else {
        Node* p_prev_node = get(s, index - 1);

        p_target_node = p_prev_node->next;

        p_prev_node->next = p_target_node->next;
    }

    free(p_target_node);
    s->len--;
}

void drop_node(Node* p_node) {
    if (p_node == NULL)
        return;

    drop_node(p_node->next);
    free(p_node);
}

void drop(SinglyLinkedList* s) { drop_node(s->head); }

void print_node(Node* node, int index) {
    if (node == NULL)
        return;

    printf("[%d]: %d\n", index, node->val);
    print_node(node->next, index + 1);
}

void print_all_nodes(SinglyLinkedList* s) { print_node(s->head, 0); }

int main() {
    SinglyLinkedList s = new_singly_linked_list();

    insert(&s, 0, 1);
    push(&s, 2);
    push(&s, 3);
    push(&s, 4);
    push(&s, 5);
    get(&s, 0);
    remove_at(&s, 4);
    print_all_nodes(&s);

    return 0;
}