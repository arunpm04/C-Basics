#include <stdio.h>
#include <stdlib.h>

/* Uncomment to enable debug */
//#define ENABLE_DEBUG

typedef struct node_t {
	int value;
	struct node_t *next;
	struct node_t *prev;
} node_t;

/*
 * brief		: Traverse through the linked list and dumps the content.
 * param1[in]	: Pointer to the list root.
 * return		: 0 if Success; else -1.
 */
int print_list(node_t *base)
{
	if (base == NULL)
		return -1;
	while (base != NULL) {
		printf("%08X [%03d] [%08X <--> %08X]\n", base, base->value, base->prev, base->next);
		if (print_list(base->next) == 0)
			break;
	}
	return 0;
}

/*
 * brief		: Add new node at the beginning of the list.
 * return		: Pointer to the new List root.
 */
node_t* list_add(node_t *base, int data)
{
	node_t *temp = (node_t *)calloc(1, sizeof(node_t));
	temp->value = data;
	if (base != NULL) {
		temp->next = base;
		base->prev = temp;
	}
#ifdef ENABLE_DEBUG
	printf("temp = %x [%03d] [%x <--> %x]\n", temp, temp->value, temp->prev, temp->next);
#endif
	return temp;
}

/*
 * brief		: Checks for double-linklist flaw.
 * return		: 0 if Success; else -1.
 */
int check_to_n_fro(node_t *base)
{
	node_t *root_backup = base, *old_base = NULL;
	if (base == NULL) {
		printf("Root NULL\n");
		return -1;
	}
	printf("FWD ---->\n");
	while (base != NULL) {
		printf("%08X [%03d] [%08X <--> %08X]\n", base, base->value, base->prev, base->next);
		old_base = base;
		base = base->next;
	}
	printf("REV ---->\n");
	base = old_base;
	while (base != NULL) {
		printf("%08X [%03d] [%08X <--> %08X]\n", base, base->value, base->prev, base->next);
		base = base->prev;
	}
	return 0;
}

/*
 * brief		: Appends a new node to the List.
 * return		: Pointer to the List root.
 */
node_t* list_append(node_t *base, int data)
{
	node_t *root_backup = base, *temp = (node_t *)calloc(1, sizeof(node_t));
	temp->value = data;
	while (base->next != NULL)
		base = base->next;
	base->next = temp;
	temp->prev = base;
#ifdef ENABLE_DEBUG
	printf("temp = %x [%03d] [%x <--> %x]\n", temp, temp->value, temp->prev, temp->next);
#endif
	return root_backup;
}

int main(void)
{
	node_t *root = list_add(NULL, 0);
	int i;

	printf("Adding 10 to 15...\n");
	for (i=0; i<=5; i++)
		root = list_add(root, (i+10));

	printf("Appending 100 to 105...\n");
	for (i=0; i<=5; i++)
		root = list_append(root, (i+100));

	printf("check_to_n_fro ...\n");
	check_to_n_fro(root);
	return 0;
}
