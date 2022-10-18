#include <stdio.h>
#include <assert.h>
#include "list.h"

List heads[LIST_MAX_NUM_HEADS];
int track_heads[LIST_MAX_NUM_HEADS];
int heads_index = 0;

Node nodes[LIST_MAX_NUM_NODES];
int track_nodes[LIST_MAX_NUM_NODES];
int nodes_index = 0;

bool first_time = true;

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create() {
    // if user called List_create() the very first time, then allow a one-time
    // non-constant set up of heads and nodes arrays
    if (first_time) {
        for (int i=0; i<LIST_MAX_NUM_NODES; i++) {
            Node n = {NULL,NULL,NULL,-1,1};
            nodes[i] = n;
        }

        for (int i=0; i<LIST_MAX_NUM_HEADS; i++) {
            List l = {NULL,NULL,NULL,-1,0,0,1};
            heads[i] = l;
        }

        for (int i=0; i<LIST_MAX_NUM_NODES; i++) {
            track_nodes[i] = i;
        }

        for (int i=0; i<LIST_MAX_NUM_HEADS; i++) {
            track_heads[i] = i;
        }
        first_time = false;
    }
    
    // if heads are exausted, then tring to create a new list fails
    if (!heads[track_heads[heads_index]].avai) {
        return NULL;
    }

    // creates a empty list
    List* lst = &heads[heads_index];
    lst->index_of_head = heads_index;
    lst->avai = false;
    heads_index++;

    return lst;
}

// Returns the number of items in pList.
int List_count(List* pList) {
    assert(pList != NULL);

    return pList->size;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList) {
    if (pList == NULL) {
        return NULL;
    }

    // if list is empty
    if (pList->size == 0) {
        pList->current = NULL;
        return NULL;
    }

    pList->current = pList->head; // set current to head
    pList->OutOfBounds = 0;
    return pList->head->element;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList) {
    if (pList == NULL) {
        return NULL;
    }

    // if list is empty
    if (pList->size == 0) {
        pList->current = NULL;
        return NULL;
    }

    pList->current = pList->tail; // set current to tail
    pList->OutOfBounds = 0;
    return pList->tail->element;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList) {
    if (pList == NULL || pList->size == 0) {
        return NULL;
    }

    // if current item is the last item, then advancing current by one will result in out of bound
    if (pList->current == pList->tail) {
        pList->current = NULL;
        pList->OutOfBounds = 2;
        return NULL;
    }

    pList->current = pList->current->next;

    return pList->current->element;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList) {
    if (pList == NULL || pList->size == 0) {
        return NULL;
    }

    // if current item is the first item, then back up current by one will result in out of bound
    if (pList->current == pList->head) {
        pList->current = pList->current->prev;
        pList->OutOfBounds = 1;
        return NULL;
    }

    pList->current = pList->current->prev;

    return pList->current->element;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList) {
    //                                       if current is out of bound
    if (pList == NULL || pList->size == 0 || pList->current == NULL) {
        return NULL;
    }

    return pList->current->element;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem) {
    if (pList == NULL) {
        return -1;
    }

    // if nodes are exhausted, then adding an item to a list fails
    if (!nodes[track_nodes[nodes_index]].avai) {
        return -1;
    }

    Node* nd = &nodes[nodes_index];
    nd->element = pItem;
    nd->index_of_node = nodes_index;
    nd->avai = false;
    nodes_index++;

    // if list is empty
    if (pList->size == 0) {
        pList->head = nd;
        pList->tail = nd;
    } else {
        switch(pList->OutOfBounds) {
        case 0: // case where current is not out of bound
            nd->next = pList->current->next;
            nd->prev = pList->current;
            if (pList->current != pList->tail) {
              pList->current->next->prev = nd;
            } else {
                pList->tail = nd;
            }
            pList->current->next = nd;
            break;
        
        case 1: // case where current is out of bound at the start
            nd->next = pList->head;
            nd->prev = NULL;
            pList->head->prev = nd;
            pList->head = nd;
            break;

        case 2: // case where current is out of bound at the end
            nd->next = NULL;
            nd->prev = pList->tail;
            pList->tail->next = nd;
            pList->tail = nd;
            break;

        default:
            return -1;

        }
    }

    pList->current = nd;
    pList->size++;
    pList->OutOfBounds = 0;

    return 0;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem) {
    if (pList == NULL) {
        return -1;
    }

    // if nodes are exhausted, then adding an item to a list fails
    if (!nodes[track_nodes[nodes_index]].avai) {
        return -1;
    }

    Node* nd = &nodes[nodes_index];
    nd->element = pItem;
    nd->index_of_node = nodes_index;
    nd->avai = false;
    nodes_index++;

    // if list is empty
    if (pList->size == 0) {
        pList->head = nd;
        pList->tail = nd;
    } else {
        switch(pList->OutOfBounds) {
        case 0: // case where current is not out of bound
            nd->next = pList->current;
            nd->prev = pList->current->prev;
            if (pList->current != pList->head) {
              pList->current->prev->next = nd;
            } else {
                pList->head = nd;
            }
            pList->current->prev = nd;
            break;
        
        case 1: // case where current is out of bound at the start
            nd->next = pList->head;
            nd->prev = NULL;
            pList->head->prev = nd;
            pList->head = nd;
            break;

        case 2: // case where current is out of bound the the end
            nd->next = NULL;
            nd->prev = pList->tail;
            pList->tail->next = nd;
            pList->tail = nd;
            break;

        default:
            return -1;

        }
    }

    pList->current = nd;
    pList->size++;
    pList->OutOfBounds = 0;
    
    return (long) pList->current->element;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem) {
    if (pList == NULL) {
        return -1;
    }

    // if nodes are exhausted, then adding an item to a list fails
    if (!nodes[track_nodes[nodes_index]].avai) {
        return -1;
    }

    Node* nd = &nodes[nodes_index];
    nd->element = pItem;
    nd->index_of_node = nodes_index;
    nd->avai = false;
    nodes_index++;

    // if list is empty
    if (pList->size == 0) {
        pList->head = nd;
        pList->tail = nd;
    } else {
        nd->prev = pList->tail;
        nd->next = NULL;
        pList->tail->next = nd;
        pList->tail = nd;
    }

    pList->current = nd;
    pList->size++;
    pList->OutOfBounds = 0;

    return 0;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem) {
    if (pList == NULL) {
        return -1;
    }

    // if nodes are exhausted, then adding an item to a list fails
    if (!nodes[track_nodes[nodes_index]].avai) {
        return -1;
    }

    Node* nd = &nodes[nodes_index];
    nd->element = pItem;
    nd->index_of_node = nodes_index;
    nd->avai = false;
    nodes_index++;

    // if list is empty
    if (pList->size == 0) {
        pList->head = nd;
        pList->tail = nd;
    } else {
        nd->prev = NULL;
        nd->next = pList->head;
        pList->head->prev = nd;
        pList->head = nd;
    }

    pList->current = nd;
    pList->size++;
    pList->OutOfBounds = 0;

    return 0;
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList) {
    if (pList == NULL) {
        return NULL;
    }

    // if current is out of bound or the list is empty
    if (pList->OutOfBounds != 0 || pList->size == 0) {
        return NULL;
    }

    Node* nd = pList->current;
    // if removing the head
    if (pList->current == pList->head) {
        pList->current->next->prev = NULL;
        pList->head = pList->current->next;
        pList->current = pList->current->next;
    } 
    
    // if removing the tail
    else if (pList->current == pList->tail) {
        pList->OutOfBounds = 2;
        pList->tail = nd->prev;
        pList->current = NULL;
    } 
    
    else {
        pList->current->prev->next = pList->current->next;
        pList->current->next->prev = pList->current->prev;
        pList->current = pList->current->next;
    }

    nd->next = NULL;
    nd->prev = NULL;
    nd->avai = 1;


    // freeing the node, make it available for future use
    nodes_index--;
    track_nodes[nodes_index] = nd->index_of_node;
    
    pList->size--;
    return nd->element;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList) {
    if (pList == NULL) {
        return NULL;
    }

    if (pList->size == 0) {
        return NULL;
    }

    Node* nd = pList->tail;
    pList->tail->prev->next = NULL;
    pList->current = pList->tail->prev;
    pList->tail = pList->current;
    nd->prev = NULL;
    nd->avai = 1;

    // freeing the node, make it available for future use
    nodes_index--;
    track_nodes[nodes_index] = nd->index_of_node;

    pList->size--;
    return nd->element;
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its first is available
// for future operations.
void List_concat(List* pList1, List* pList2) {
    if (pList1 == NULL || pList2 == NULL) {
        return;
    }

    // if both list is empty
    if (pList1->size == 0 && pList2->size == 0) {
        ;
    } else if (pList1->size == 0) { // if List 1 is empty
        pList1 = pList2;
    } else if (pList2->size == 0) { // if List 2 is empty
        ;
    } else {
        pList1->tail->next = pList2->head;
        pList2->head->prev = pList1->tail;
        pList1->tail = pList2->tail;
    }

    pList1->size = pList1->size + pList2->size;


    // freeing the head, make it available for future use
    pList2->head = NULL;
    pList2->tail = NULL;
    pList2->current = NULL;
    pList2->avai = 1;
    heads_index--;
    track_heads[heads_index] = pList2->index_of_head;
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its first and nodes are 
// available for future operations.
typedef void (*FREE_FN)(void* pItem);
void List_free(List* pList, FREE_FN pItemFreeFn) {
    if (pList == NULL) {
        return;
    }

    // traver through the list from the tail to the head
    while (pList->tail != NULL) {
        Node* current = pList->tail;
        (*pItemFreeFn) (current->element);
        // freeing the node, make it available for future use
        nodes_index--;
        track_nodes[nodes_index] = current->index_of_node;

        pList->tail = pList->tail->prev;
        current->next = NULL;
        current->prev = NULL;
        current->avai = 1;
    }

    pList->head = NULL;
    pList->current = NULL;
    pList->OutOfBounds = 0;
    pList->size = 0;

    // freeing the head, make it available for future use
    heads_index--;
    track_heads[heads_index] = pList->index_of_head;
    pList->avai = 1;
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
typedef bool (*COMPARATOR_FN)(void* pItem, void* pComparisonArg);
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg) {
    if (pList == NULL) {
        return NULL;
    }

    // if current is out of bound at the end of the list
    if (pList->OutOfBounds == 2) {
        return NULL;
    } else if  (pList->OutOfBounds == 1) { // if current is out of bound at the start of the list
        pList->current = pList->head;
    }

    // traverse through the list to find a match
    while (pList->current != NULL) {
        // compare the item of current to pComparisonArg
        if ((*pComparator) (pList->current->element, pComparisonArg)) {
            return pList->current->element;
        }
        
        pList->current = pList->current->next;
    }

    // if not found, the current pointer if left beyond the end of the list
    pList->OutOfBounds = 2;

    return NULL;
}