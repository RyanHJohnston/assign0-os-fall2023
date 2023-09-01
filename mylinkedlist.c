
/*
 * File: mylinkedlist.c
 * YOUR NAME ... 
 * YOU NEED TO IMPLEMENT THE FUNCTIONS  here
 * ....
 */

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "mylinkedlist.h"

/* typedef int i32; */

/*
 * Function: NewStudentCell
 * Usage: student_cell_T *element;
 *        element = NewStudentCell(int id, double gpa, char *name);
 * --------------------------
 * This function allocates space for a student cell and intilize its fileds
 */
student_cell_T 
*NewStudentCell(int id, double gpa, char *name)
{
    student_cell_T *element;

    element = (student_cell_T *) malloc( sizeof(student_cell_T) );
    if( !element){
        fprintf(stderr,"\nERROR: NewStudentCell cannot allocate memory\n\n");
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

    if (list == NULL) {
        fprintf(stderr, "\nERROR: Attemping to deallocate an empty linked list\n\n");
        return;
    }
    
    /* This code was written using ChatGPT, I struggled to write a proper free function */
    student_cell_T *current = list->head;
    while (current != NULL) {
        student_cell_T *temp = current;
        current = current->next;
        free(temp->name);
        free(temp);
    }

    free(list);

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
        list->tail->next = NULL;
        return;
    } else {
        element->next = list->head;
        list->head = element;
        
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
    if (LinkedListIsEmpty(list)) {
        fprintf(stdout, "List is empty, head element is NULL\n");
        exit(EXIT_FAILURE);
    }
   
    if (list->head->next == NULL) {
        fprintf(stderr, "\nERROR: List is now empty, returning NULL\n\n");
        return;
    }
    
    

    student_cell_T *temp = list->head;
    student_cell_T *current;

    list->head = list->head->next;
    current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    list->tail = current;
    
    free(temp->name);
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
int 
LinkedListIsEmpty(linked_list_T *list)
{
    return list->head == NULL && list->tail == NULL;
}

int LinkedListIsFull(linked_list_T *list)
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
int 
LinkedListLength(linked_list_T  *list)
{
    int count = 0;

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
*GetLinkedListElement(linked_list_T *list, int index)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "\nERROR: List is empty, no element could get retrieved, returning NULL\n\n");
        return NULL;
    }

    if (index < 0 || index > LinkedListLength(list)) {
        return NULL;
    }
    
    int current_index = 0;
    student_cell_T *current = list->head;
   
    while (current != NULL) {
        if (current_index == index) {
            return current;
        }
        
        current = current->next;
        ++current_index;
    }

    fprintf(stderr, "\nERROR: index out of bounds\n\n");
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
        fprintf(stderr, "ERROR: Linked list is empty, cannot print elements\n");
        return;
    }

    student_cell_T *current = list->head;

    if (current->next == NULL) {
        print_student_attributes(current);
        return;
    }
    
    while (current->next != NULL) {
        print_student_attributes(current);
        current = current->next;
    }
    
    list->tail = current;
    /* Print out tail of linked list */
    print_student_attributes(list->tail);
}

/**
 * @brief Prints out all of the options of the program
 */
void 
print_options()
{
    fprintf(stdout, "\n");
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

/**
 * @brief Prints all the attributes of a given student
 *
 * @param student: student_cell_T
 */
void
print_student_attributes(student_cell_T *student)
{
    fprintf(stdout, "\n");
    fprintf(stdout, "ID: %i\nGPA: %.2lf\nName: %s\n",
            student->id, student->gpa, student->name);
}

/**
 * @brief DEPRECATED, NOT USED
 */
char *
user_str_input(int buffer_length)
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
    
    fprintf(stderr, "\nERROR: User input failed, returning NULL\n\n");
    return NULL;
}

/**
 * @brief Takes user string input and stores as etc
 *
 * @param buff_size: const size_t
 * @return buff: char *
 */
char *
read_line(const size_t buff_size)
{
    char *buff = malloc(buff_size);
    scanf (" %[^\n]s", buff);
    /* scanf("%s", buff); */

    return buff;

    /* return(NULL); */
}

/**
 * @brief Takes user string input and stores as a name
 *
 * @param name_buff_size: const size_t
 * @return name: char *
 */
char *
read_name(const size_t name_buff_size)
{
    /* this properly allocates to the heap, right? */
    char *name = malloc(name_buff_size);
    scanf(" %[^\n]s", name);
    return name;
}

/**
 * @brief Checks for string conversion errors
 *
 * @param num: number
 * @param endptr: Checks the end pointer
 */
void
check_for_str_to_type_error(int num, char *endptr)
{
    if (*endptr != '\0') {
        fprintf(stderr, "\nERROR: String to other data type conversion failed. Invalid input %s\n\n", 
                endptr);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Returns the minimum of all student's GPAs
 *
 * @param list: Linked List struct
 * @return min: double
 */
static double
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

/**
 * @brief Returns the average of all student's GPA
 *
 * @param list: Linked List struct
 * @return avg: double
 */
static double
get_gpa_avg(linked_list_T *list)
{
    if (LinkedListIsEmpty(list)) {
        fprintf(stderr, "ERROR: LInked list is empty, cannot get GPA average\n");
        return 0;
    }

    double avg;
    int length; /* using the LinkedListLength function would be computationall expensive, just count */
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

/**
 * @brief Gets the maximum GPA from the list of students 
 *
 * @param list: Linked List struct
 * @return max: double 
 */
static double 
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

    free(current);
    
    
    return max;
}

/**
 * @brief Prints the minimu, average, and maximum of all student's GPAs.
 *
 * @param list: Linked List struct
 */
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

/**
 * @brief Removes the student with the highest GPA from the linked list
 *
 * @param list: Linked List struct 
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
    int current_index = 0;
    int highest_gpa_student_index = 0;
    int index = 0;
    
    while (current != NULL) {
        if (max < current->gpa) {
            max = current->gpa;
            highest_gpa_student = current;
            highest_gpa_student_index = index;
        }
        current = current->next;
        index += 1;
    }
    
    /* this code was generated by chat-gpt, I worked today and didn't feel like writing the code on my own */
    if (highest_gpa_student != NULL) {
        print_student_attributes(highest_gpa_student);
        
        if (highest_gpa_student_index == 0) {
            list->head = highest_gpa_student->next;
        } else {
            student_cell_T *previous_student = GetLinkedListElement(list, highest_gpa_student_index - 1);
            previous_student->next = highest_gpa_student->next;
        }

        free(highest_gpa_student);
    }

}
