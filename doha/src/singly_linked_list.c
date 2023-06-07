#include <stdlib.h>
#include <assert.h>
#include <printf.h>

typedef struct
{
	int val;
	struct Node* next;
} Node;

typedef struct
{
	Node* head;
	int len;
} SinglyLinkedList;

Node* newNode(int val)
{
	Node* node = malloc(sizeof(Node));
	node->val = val;
	node->next = NULL;

	return node;
}

SinglyLinkedList newSinglyLinkedList()
{
	SinglyLinkedList singlyLinkedList = { .head=NULL, .len = 0 };
	return singlyLinkedList;
}

Node* get(SinglyLinkedList* s, int index)
{
	assert(index < s->len);

	if (index < 0) return NULL;

	Node* cursor = s->head;
	for (int i = 0; i < index; ++i)
	{
		cursor = cursor->next;
	}
	return cursor;
}

void push(SinglyLinkedList* s, int val)
{
	Node* new_node = newNode(val);

	Node* last_node = get(s, s->len - 1);

	s->len++;

	if (last_node == NULL)
	{
		s->head = new_node;
		return;
	}

	last_node->next = new_node;

}

void insert(SinglyLinkedList* s, int index, int val)
{
	assert(index >= 0 && index <= s->len);

	Node* new_node = newNode(val);

	Node* prev_node = get(s, index - 1);

	s->len++;


	if (prev_node == NULL)
	{
		new_node->next = s->head;
		s->head = new_node;
		return;
	}

	new_node->next = prev_node->next;
	prev_node->next = new_node;

}

void remove_at(SinglyLinkedList* s, int index)
{
	assert(index >= 0 && index < s->len);

	Node* trarget_node;

	if (index == 0)
	{
		trarget_node = s->head;
		s->head = trarget_node->next;
	}
	else
	{
		Node* prev_node = get(s, index - 1);
		trarget_node = prev_node->next;
		prev_node->next = trarget_node->next;
	}

	free(trarget_node);
	s->len--;
}

void drop_node(Node* node)
{
	if (node == NULL) return;

	drop_node(node->next);
	free(node);
}

void drop(SinglyLinkedList* s)
{
	drop_node(s->head);
}

void print_all_nodes(SinglyLinkedList* s)
{
	Node* cursor = s->head;

	for (int i = 0; i < s->len; ++i)
	{
		printf("[%d]: %d\n", i, cursor->val);
		cursor = cursor->next;
	}
}

int main()
{
	SinglyLinkedList s = newSinglyLinkedList();
	push(&s, 1);
	insert(&s, 1, 2);
	push(&s, 3);
	push(&s, 4);
	push(&s, 5);
	print_all_nodes(&s);
	printf("\n");

	insert(&s, 0, 100);
	print_all_nodes(&s);
	printf("\n");

	remove_at(&s, 0);
	print_all_nodes(&s);
	printf("\n");

	drop(&s);
	print_all_nodes(&s);
}