#include "LinkedList.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct LinkedList *CreateLinkedList(void)
{
	struct LinkedList *list = malloc(sizeof(struct LinkedList));
	list->head = NULL;
	return list;
}

void PrependLL(struct LinkedList *list, item_t item)
{
	assert(list != NULL);
	struct LinkedListNode *node = malloc(sizeof(struct LinkedListNode));
	node->val = item;
	node->next = list->head;
	list->head = node;
}


void RemoveLL(struct LinkedList *list, item_t item)
{
	assert(list != NULL);
	assert(item != NULL);
	struct LinkedListNode *todel;

	if(list->head == NULL)
		return;

	if(list->head->next == NULL)
	{
		//list contains single element
		free(list->head->next);
		list->head = NULL;
		return;
	}

	//really don't like it but its late and i have no better idea
	if (list->head->val == item)
	{
		todel = list->head;
		list->head = list->head->next;
		free(todel);
		return;
	}

	struct LinkedListNode *iter = list->head;
	while(iter->next != NULL)
	{
		if(iter->next->val == item)
		{
			todel = iter->next;
			iter->next = iter->next->next;
			free(todel);
			return;
		}
		iter = iter->next;
	}
#ifndef NDEBUG
	puts("NO LIST ITEM DELETED");
#endif
}

void ReleaseLinkedList(struct LinkedList *list, int callFree)
{
	struct LinkedListNode *next;
	assert(list != NULL);

	if (list->head == NULL)
		return;


	next = list->head->next;
	if(callFree)
		free(list->head);
	list->head = next;
	ReleaseLinkedList(list, callFree);
}
