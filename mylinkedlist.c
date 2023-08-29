
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
#include <strings.h>
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
    student_cell_T *current;

    list->head = list->head->next;
    current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    list->tail = current;

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
    
    int32_t current_index = 0;
    student_cell_T *current = list->head;
   
    while (current->next != NULL) {
        if (current_index == index) {
            return current;
        }
        
        current = current->next;
        ++current_index;
    }

    fprintf(stderr, "ERROR: index out of bounds\n");
    return NULL;


# if 0
    while (current != NULL) {
        if (currentPosition == index) {
            return current; // Return the node at the given index
        }

        current = current->next;
        currentPosition++;
    }

#endif
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

/* Prints the options for the user to take input */
void 
print_options()
{
    fprintf(stdout, "1 - Create a new student cell with given id, gpa, name info, and add (Enlist) it to the end of the linked list.\n");  
    fprintf(stdout, "2 - Remove (Delist) the first student from linked list and print his/her id, gpa, name info\n");
    fprintf(stdout, "3 - Print the number of students in the linked list (Length)\n");
    fprintf(stdout, "4 - Print (id, gpa, name) of a student at a specific index (head of the list is defined as index 0)\n");
    fprintf(stdout, "5 - Print the list of all students in the linked list. Print (id, gpa, name) of every student\n");
    fprintf(stdout, "6 - Print the min, average, max GPAs in the linked list\n");
    fprintf(stdout, "7 - Remove the student with highest GPA and print his/her info (if there are ties, just take the first one you found)\n");
    fprintf(stdout, "8 - Exit\n");
    fprintf(stdout, "Enter your choice: ");
}

void
print_student_attributes(student_cell_T *student)
{
    fprintf(stdout, "\n%i %.2lf %s\n",
            student->id, student->gpa, student->name);
}

char *
user_str_input(int32_t buffer_length)
{
    char buffer[buffer_length];

    // Read a string from the user using fgets
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Remove the newline character if present
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        printf("You entered: %s\n", buffer);
        return buffer;
    }
    
    fprintf(stderr, "ERROR: User input failed, returning NULL\n");
    return NULL;
}

char *
read_line(int32_t buffer_size)
{
    char *buff = malloc(buffer_size);
    scanf("%s", buff);
    return buff;

    return(NULL);
}

void
check_for_str_to_type_error(int32_t num, char *endptr)
{
    if (*endptr != '\0') {
        fprintf(stderr, "ERROR: String to other data type conversion failed. Invalid input %s\n", 
                endptr);
        exit(EXIT_FAILURE);
    }
}

double
get_gpa_min(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: LInked list is empty, cannot get GPA minimum\n");
        return 0;
    }

    student_cell_T *current = list->head;
    double min = current->gpa;
    
    while (current != NULL) {
        if (current->gpa < min) {
            min = current->gpa;
        }
        current = current->next;
    }
    
    return min;
}

double
get_gpa_avg(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: LInked list is empty, cannot get GPA average\n");
        return 0;
    }

    double avg;
    int32_t length; /* using the LinkedListLength function would be computationall expensive, just count */
    double sum;
    student_cell_T *current = list->head;
    
    length = 0; /* b/c linked list is not empty */
    while (current != NULL) {
        sum += current->gpa;
        length += 1;
        current = current->next;
    }
    
    avg = sum / length;
    
    return avg;
}

double 
get_gpa_max(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: LInked list is empty, cannot get GPA minimum\n");
        return 0;
    }

    double max = 0.0;
    student_cell_T *current = list->head;

    while (current != NULL) {
        if (max < current->gpa) {
            max = current->gpa;
        }
        current = current->next;
    }
    
    return max;
}

void
print_gpa_min_avg_max(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: Linked list is empty, cannot get gpa stats\n");
        return;
    }
    
    double min;
    double avg;
    double max;
    
    min = get_gpa_min(list);
    avg = get_gpa_avg(list);
    max = get_gpa_max(list);

    fprintf(stdout, "\nMinimum GPA: %.2lf\nAverage GPA: %.2lf\nMaximum GPA: %.2lf\n\n",
            min, avg, max);
}

/*
 * ISSUE: Removing the specified element is causing issues
 */
void
remove_highest_gpa_student(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: Linked list is empty, cannot get gpa stats\n");
        return;
    }
    
    double max = 0.0;
    student_cell_T *current = list->head;
    student_cell_T *highest_gpa_student;
    int32_t current_index = 0;
    int32_t highest_gpa_student_index = 0;
    int32_t index = 0;

    fprintf(stdout, "\nDelisting student with highest GPA\n\n");
    
    while (current != NULL) {
        if (max < current->gpa) {
            max = current->gpa;
            highest_gpa_student = current;
            highest_gpa_student_index = index;
        }
        current = current->next;
        index += 1;
    }
    
    fprintf(stdout, "\nRemoving student with highest GPA");
    print_student_attributes(highest_gpa_student);
   
    highest_gpa_student = GetLinkedListElement(list, highest_gpa_student_index);
    student_cell_T *temp = highest_gpa_student;
    highest_gpa_student = highest_gpa_student->next;
    free(temp);

    fprintf(stdout, "\nSuccessfully removed student with highest GPA\n\n");
}
