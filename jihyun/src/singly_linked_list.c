#include <stdlib.h>
#include <assert.h>
#include <printf.h>

typedef struct Node
{
	int val;
	struct Node* next;
} Node;

typedef struct
{
	int len;
	Node* head;
} SinglyLinkedList;

SinglyLinkedList new()
{
	SinglyLinkedList s = { .len = 0, .head = NULL };
	return s;
}

Node* create_node(int val)
{
	Node* new_node = malloc(sizeof(Node));
	new_node->next = NULL;
	new_node->val = val;
	return new_node;
}

Node* get(SinglyLinkedList* s, int index)
{
	assert(index < s->len);
	if (index < 0) return NULL;
	Node* cursor = s->head;
	for (int i = 0; i < index; i++)
	{
		cursor = cursor->next;
	}
	return cursor;
}

void push(SinglyLinkedList* s, int val)
{
	Node* new_node = create_node(val);
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
	Node* new_node = create_node(val);
	Node* prev_node = get(s, index - 1);
	if (prev_node == NULL)
	{
		new_node->next = s->head;
		s->head = new_node;
	}
	else
	{
		new_node->next = prev_node->next;
		prev_node->next = new_node;
	}
	s->len++;
}

void remove_at(SinglyLinkedList* s, int index)
{
	assert(index >= 0 && index < s->len);
	Node* prev_node = get(s, index - 1);
	Node* removal_node;
	if (prev_node == NULL) // or index == 0
	{
		removal_node = s->head;
		s->head = removal_node->next;
	}
	else
	{
		removal_node = prev_node->next;
		prev_node->next = removal_node->next;
	}
	free(removal_node);
	s->len--;
}

void drop_node(Node* p_node)
{
	if (p_node == NULL) return;

	drop_node(p_node->next);
	free(p_node); // question - free를 먼저하게되면 p_node의 next에 접근불가하므로 먼저 이동해준다?
}

void drop_node2(Node* p_node)
{
	if (p_node == NULL) return;
	Node* next_node = p_node->next;
	free(p_node);
	drop_node(next_node);
}

void drop(SinglyLinkedList* s) //clear list
{
	drop_node(s->head);
}

void print_node(Node* p_node, int index)
{
	if (p_node == NULL) return;

	printf("[%d]: %d\n", index, p_node->val);
	print_node(p_node->next, index + 1);
}

void print_all_nodes(SinglyLinkedList* s)
{
	print_node(s->head, 0);
}

int main()
{
	SinglyLinkedList s = new();
	push(&s, 1);
	push(&s, 2);
//	remove_at(&s, 1);
//	drop(&s);
	print_all_nodes(&s);

	return 0;
}