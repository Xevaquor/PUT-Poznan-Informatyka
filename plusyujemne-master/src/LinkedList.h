#ifndef _LLIST_H_
#define _LLIST_H_
#include <stddef.h>

typedef void * item_t;

struct LinkedListNode
{
	item_t val;
	struct LinkedListNode *next;
};

struct LinkedList
{
	struct LinkedListNode *head;
};
//utwóz pustą listę
struct LinkedList *CreateLinkedList(void);
/*zwolnij całą listę, callFree - czy zwalniać poszczególne elementy
 * pożądane jeśli znajdują się tylko na tej liście
 * niepożądane jeżeli są współdzielone w innym miejscu
 */
void ReleaseLinkedList(struct LinkedList *list, int callFree);

//dopisz na początek listy
void PrependLL(struct LinkedList *list, item_t item);
//usuń z listy
void RemoveLL(struct LinkedList *list, item_t item);

#endif			
