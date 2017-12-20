#include <stdio.h>
#include <stdlib.h>
#include "app_debug.h"

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
		ERR("%p [%03d] [%p <--> %p]\n", base, base->value, base->prev, base->next);
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
//	DBG("temp = %08p [%03d] [%08p <--> %08p]\n", temp, temp->value, temp->prev, temp->next);
	return temp;
}

/*
 * brief		: Checks for double-linklist flaw.
 * return		: 0 if Success; else -1.
 */
int check_to_n_fro(node_t *base)
{
	node_t *old_base = NULL;
	if (base == NULL) {
		printf("Root NULL\n");
		return -1;
	}
	ERR("FWD ---->\n");
	while (base != NULL) {
		ERR("%p [%03d] [%p <--> %p]\n", base, base->value, base->prev, base->next);
		old_base = base;
		base = base->next;
	}
	ERR("REV ---->\n");
	base = old_base;
	while (base != NULL) {
		ERR("%p [%03d] [%p <--> %p]\n", base, base->value, base->prev, base->next);
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
//	DBG("temp = %p [%03d] [%p <--> %p]\n", temp, temp->value, temp->prev, temp->next);
	return root_backup;
}

/*
 * brief		: Delete the all nodes with matching data.
 * return		: Pointer to the List root.
 */
node_t* list_delete(node_t *base, int data)
{
	int rerun = 1;
	node_t *root_backup = base;

	if (base == NULL)
		return base;

	while (rerun) {
		rerun = 0;
		while (base != NULL) {
			if (base->value == data) {
				DBG("Matched at %p\n", base);
				if (base->prev == NULL) {
					rerun = 1;
					DBG("Root node...\n");
					root_backup = base->next;
					base->next->prev = NULL;
					free(base);
					break;
				} else if (base->next == NULL) {
					DBG("Apex node...\n");
					base->prev->next = NULL;
					free (base);
					rerun = 0;
					break;
				} else {
					rerun = 1;
					node_t *temp = base->prev;
					temp->next = base->next;
					if (base->next)
						base->next->prev = temp;
					free(base);
					break;
				}
			}
			base = base->next;
		}
	}
	return root_backup;
}

/*
 * brief		: Insert node with data after index.
 * param1[in]	: Pointer to List root.
 * param2[in]	: Index to skip.
 * param3[in]	: Data.
 * return		: Pointer to the List root.
 */
node_t* list_insert(node_t *base, int index, int data)
{
	int i;
	node_t *root_backup = base;
	if (index == 0) {
		/* Insert node at Head. */
		return list_add(base, data);
	}
	for (i = 1; (i <= index) && (base != NULL); i++)
		base = base->next;
	if ((base == NULL) && (i != index)) {
		/* Not enough nodes, hence do append. */
		return list_append(root_backup, data);
	} else {
		node_t *new = (node_t *)calloc(1, sizeof(node_t));
		new->value = data;
		if (new != NULL) {
			base->next->prev = new;
			new->next = base->next;
			base->next = new;
			new->prev = base;
		} else
			DBG("Alloc failed....\n");
	}
	return root_backup;
}

int main(void)
{
	node_t *root = list_add(NULL, 0);
	int i;

	DBG("Adding 10 to 15...\n");
	for (i=0; i<=5; i++)
		root = list_add(root, (i+10));
	DBG("Appending 100 to 105...\n");
	for (i=0; i<=5; i++)
		root = list_append(root, (i+100));
	DBG("check_to_n_fro ...\n");
	check_to_n_fro(root);
	DBG("Deleting 10...\n");
	root = list_delete(root, 10);
	check_to_n_fro(root);
	DBG("Deleting 105...\n");
	root = list_delete(root, 105);
	check_to_n_fro(root);
	DBG("Deleting 15...\n");
	root = list_delete(root, 15);
	check_to_n_fro(root);
	DBG("Insert 200 at 0\n");
	root = list_insert(root, 0, 200);
	check_to_n_fro(root);
	DBG("Insert 201 at 5\n");
	root = list_insert(root, 5, 201);
	check_to_n_fro(root);
	DBG("Insert 202 at 50\n");
	root = list_insert(root, 50, 202);
	check_to_n_fro(root);
	return 0;
}
