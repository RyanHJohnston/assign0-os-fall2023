
/*
 * File: mylinkedlist.c
 * YOUR NAME ... 
 * YOU NEED TO IMPLEMENT THE FUNCTIONS  here
 * ....
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mylinkedlist.h"

/* typedef int32_t i32; */

/*
 * Function: NewStudentCell
 * Usage: student_cell_T *element;
 *        element = NewStudentCell(int32_t id, double gpa, char *name);
 * --------------------------
 * This function allocates space for a student cell and intilize its fileds
 */
student_cell_T 
*NewStudentCell(int32_t id, double gpa, char *name)
{
    student_cell_T *element;

    element = (student_cell_T *) malloc( sizeof(student_cell_T) );
    if( !element){
        fprintf(stderr,"NewStudentCell cannot allocate memory\n");
        return NULL;
    }
    element->id = id;
    element->gpa = gpa;
    element->name = name;

    return element;
}


/*
 * Function: NewLinkedList
 * Usage: linked_list_T *list;
 *        list = NewLinkedList();
 * --------------------------
 * This function allocates and returns an empty linked list.
 */
linked_list_T 
*NewLinkedList(void)
{
    linked_list_T *list;

    list = (linked_list_T *) malloc( sizeof(linked_list_T) );
    if( !list){
        fprintf(stderr,"NewLinkedList cannot allocate memory\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

/*
 * Function: FreeLinkedList
 * Usage: FreeLinkedList(list);
 * ------------------------
 * This function frees the storage associated with list.
 */
void 
FreeLinkedList(linked_list_T *list)
{
    student_cell_T *current = list->head;
    while (current != NULL) {
        student_cell_T *temp = current;
        current = current->next;
        /* free(temp->name); */
        free(temp);
    }

    fprintf(stdout, "FreeLinkedList was successfully completed!\n");
}

/*
 * Function: Enlist
 * Usage: Enlist(list, element);
 * -------------------------------
 * This function adds a student cell pointed by element to the end of the list.
 */
void 
Enlist(linked_list_T *list, student_cell_T *element)
{
    /* Assume that the memory and information for element is already allocated */

    /* If list is empty, insert element at head node */
    /* Note: student can concurrently be list->head and list->tail, if either are NULL, list is empty  */
    if (list->head == NULL) {
        list->head = element;
        list->tail = element;
        return;
    } else {
        list->tail->next = element;
        list->tail = element;
    }
}

/*
 * Function: Delist
 * Usage: element = Delist(list);
 * --------------------------------
 * This function removes the student cell at the head of the list
 * and returns its address to the caller (client).  If the list is empty, Delist
 * prints an Error with an appropriate message and returns NULL.
 */
void 
Delist(linked_list_T *list)
{
    if (list->head == NULL) {
        fprintf(stdout, "List is empty, head element is NULL\n");
    }
    
    
    student_cell_T *temp = list->head;
    void *address_space = &temp;

    list->head = list->head->next;

    free(temp);
    temp = NULL;
}

/*
 * Functions: LinkedListIsEmpty, LinkedListIsFull
 * Usage: if (LinkedListIsEmpty(list)) . . .
 *        if (LinkedListIsFull(list)) . . .
 * -------------------------------------
 * These functions test whether the list is empty or full.
 */
int32_t 
LinkedListIsEmpty(linked_list_T *list)
{
    return list == NULL;
}

int32_t LinkedListIsFull(linked_list_T *list)
{
    if (!LinkedListIsEmpty(list)) {
        fprintf(stdout, "Linked list is NOT full, returning 1\n");
        return 1;
    }

    return 0; // because we have linked list
}

/*
 * Function: LinkedListLength
 * Usage: n = LinkedListLength(list);
 * ------------------------------
 * This function returns the number of elements in the list.
 */
int32_t 
LinkedListLength(linked_list_T  *list)
{
    int32_t count = 0;

    if (LinkedListIsEmpty(list)) {
        fprintf(stdout, "Linked list is empty, returning zero\n");
        return count;
    }

    student_cell_T *current = list->head;
    count = 1;

    if (current->next == NULL) {
        return count;
    }

    while (current->next != NULL) {
        ++count;
        current = current->next;
    }

    return count;
}

/*
 * Function: GetLinkedListElement
 * Usage: element = GetLinkedListElement(list, index);
 * -----------------------------------------------
 * This function returns the element at the specified index in the
 * list, where the head of the list is defined as index 0. For
 * example, calling GetLinkedListElement(list, 0) returns the initial
 * element from the list without removing it.  If the caller tries
 * to select an element that is out of range, GetLinkedListElement prints
 * Error and returns NULL.  Note: This function is not a fundamental list operation
 * and is instead provided mainly to facilitate debugging.
 */
student_cell_T 
*GetLinkedListElement(linked_list_T *list, int32_t index)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: List is empty, no element could get retrieved, returning NULL\n");
        return NULL;
    }

    if (index < 0) {
        fprintf(stderr, "ERROR: Invalid index\nindex = %i\n", index);
        return NULL;
    }

    int32_t length;
    int32_t current_index;
    student_cell_T *current;

    length = LinkedListLength(list);
    current_index = 0;
    current = current->next;

    while (current->next != NULL) {
        if (current_index == index) {
            fprintf(stdout, "Element using index was found, returning\n");
            return current;
        }
        ++current_index;
        current = current->next;
    }

    fprintf(stderr, "ERROR: Index is out of bounds, this condition shouldn't have been reached\nindex = %i\n", index);
    return NULL;
}


student_cell_T 
*GetLinkedListElementTest(linked_list_T *list, int32_t index)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: List is empty, no element could be retrieved, returning NULL\n");
        return NULL;
    }

    int32_t length;
    int32_t current_index;
    student_cell_T *current;

    length = LinkedListLength(list);
    current_index = 0;
    current = list->head;
    
    while (current->next != NULL) {
        if (current_index == index) {
            fprintf(stdout, "Element using index was found, returning\n");
            return current;
        }
        ++current_index;
        current = current->next;
    }

    fprintf(stdout, "ERROR: Index is out of bounds\n");
    return NULL;
}

/* OTHER FUNCTIONS YOU WOULD NEED....
 * EXPORT THEM HERE, BUT IMPLMENT THEM in mylinkedlist.c 
 */


/**
 * @brief Prints the entire linked list
 *
 * @param A linked list of type linked_list_T
 */
void 
print_list(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: Linked list is empty, cannot print32_t elements\n");
        return;
    }

    student_cell_T *current = list->head;

    if (current->next == NULL) {
        fprintf(stdout, "\nOnly one element in linked list: %i %.2lf %s\n", 
                current->id, current->gpa, current->name);
        return;
    }
    
    while (current->next != NULL) {
        fprintf(stdout, "Student: %i %.2lf %s\n", 
                current->id, current->gpa, current->name);
       current = current->next;
    }
    
    /* Print out tail of linked list */
    fprintf(stdout, "Student: %i %.2lf %s\n",
            current->id, current->gpa, current->name);
}

