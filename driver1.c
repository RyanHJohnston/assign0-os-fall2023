
/*
 * File: driver1.c
 * YOUR NAME ... YOU NEED TO IMPLEMENT THE main() + additional functions if needed
 *
 * ....
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "mylinkedlist.h"

#define MAX_BUFFER 100
#define MAX_ID_BUFFER 4
#define MAX_GPA_BUFFER 4
#define MAX_NAME_BUFFER 49

/* 
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 */
char *ReadLine(void);


void 
print_options();

char *
user_str_input(int32_t buffer_length);

char *
read_line(int32_t buffer_size);

void
check_for_str_to_type_error(int32_t num, char *endptr);

int main(int argc, char *arvg[])
{
    // YOU NEED TO IMPLEMENT THIS driver1.c USING FUNCTIONS FROM mylinkedlist.h
    // But before that, implement your ReadLine() function, and test it as shown below. 
    // IF NEEDED, YOU CAN ALSO IMLEMENT YOUR OWN FUNCTIONS HERE

    uint32_t choice;
    uint32_t index_choice;
    linked_list_T *list = NewLinkedList();
    
    do {

        print_options();
        scanf("%i", &choice);

        switch (choice) {
            case 1:
                fprintf(stdout, "\nChoice entered: %d\n", choice);
                fprintf(stdout, "Enter student ID: ");
                char *id_str = read_line(MAX_ID_BUFFER);
                fprintf(stdout, "Enter student GPA: ");
                char *gpa_str = read_line(MAX_GPA_BUFFER);
                fprintf(stdout, "Enter student name: ");
                char *name = read_line(MAX_NAME_BUFFER);
                char *endptr;  // Pointer to the next character after the number
                int32_t id = (int32_t) strtol(id_str, &endptr, 10);
                double gpa = (double) strtold(gpa_str, &endptr);
                check_for_str_to_type_error(id, endptr);
                check_for_str_to_type_error((int32_t) gpa, endptr);

                student_cell_T *student = NewStudentCell(id, gpa, name);
                Enlist(list, student);
                break;
            case 2:
                fprintf(stdout, "%c\n", choice);
                student_cell_T *removed_student = list->head;
                Delist(list);
                if (removed_student->name == NULL) {
                    break;
                } else {
                    fprintf(stdout, "\n\nREMOVED STUDENT: %s\n\n", removed_student->name);
                }
                break;
            case 3:
                fprintf(stdout, "%c\n", choice);
                fprintf(stdout, "\nNumber of students: %i\n\n", LinkedListLength(list));
                break;
            case 4:
                /* RIGHT HERE: YOU'RE GETTING AN ADDRESS BOUNDARY ERROR */
                fprintf(stdout, "%c\n", choice);
                fprintf(stdout, "\nEnter index: ");
                scanf("%i", &index_choice);
                student_cell_T *chosen_student = GetLinkedListElement(list, index_choice);
                fprintf(stdout, "\nChosen student: %i %.2lf %s\n\n", 
                        chosen_student->id, chosen_student->gpa, chosen_student->name);
                break;
            case 5:
                fprintf(stdout, "%cn", choice);
                print_list(list);
                break;
            case 6:
                /* PRINT THE MIN, AVG, MAX GPAS IN LINKED LIST */
                fprintf(stdout, "%c\n", choice);
                break;
            case 7:
                /* REMOVE THE STUDENT WITH THE HIGHEST GPA AND PRINT HIS/HER INFO */
                fprintf(stdout, "%c\n", choice);
                break;
            case 8:
                fprintf(stdout, "%c\n", choice);
                break;
            default:
                fprintf(stdout, "Invalid choice\n");
                break;
        }

    } while (choice != 8);

    fprintf(stdout, "\nExiting Program.\n\n");

    return 0;
}

/* 
 * IMPLEMENTATION of ReadLine();
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 *
 * In contrast to standard I/O functions (e.g., scanf with "%s", fgets) 
 * that can read strings into a given static size buffer, ReadLine function 
 * should read the given input line of characters terminated by a newline 
 * character ('\n') into a dynamically allocated and resized buffer based on 
 * the length of the given input line. 
 *
 * When implementing this function you can use standard I/O functions. 
 * We just want you to make sure you allocate enough space for the entered data. 
 * So don't simply allocate 100 or 1000 bytes every time. 
 * If the given input has 5 characters, you need to allocate space for 6 characters.
 *
 * Hint: initially dynamically allocate an array of char with size 10. 
 * Then, read data into that array character by charecter (e.g, you can use getchar()). 
 * If you see '\n' char before reading 10th character, you are done. And you know the 
 * exact length of the input string. So, accordingly allocate enough space and copy the 
 * data into new char array, insert '\0' instead of '\n' and free the original array. 
 * Then return the new string. However, if you DO NOT see '\n' char after 10th character, 
 * then you need larger space. Accordingly, resize your original array and double its size 
 * and continue reading data character by character as in the first step... 
 * Hope you got the idea! 
 *
 * Also please check for possible errors (e.g., no memory etc.) and appropriately handle 
 * them. For example, if malloc returns NULL, free partially allocated space and return 
 * NULL from this function. The program calling this function may take other actions, 
 * e.g., stop the program!
 */
char *ReadLine()
{
    // A SIMPLE WAY TO IMPLEMENT JUST TO TEST FOR NOW, BUT THIS IS NOT WHAT WE WANT!!!
    char *buff = malloc(100);
    scanf("%s", buff);
    return buff;


    // YOU NEED TO DELETE ABOVE 3 LINES, and IMPLEMENT THSI as described above


    return(NULL);   // if there is any error!
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
