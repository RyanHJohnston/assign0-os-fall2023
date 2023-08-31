
/*
 * File: driver1.c
 * YOUR NAME ... YOU NEED TO IMPLEMENT THE main() + additional functions if needed
 *
 * ....
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "mylinkedlist.h"

#define MAX_ID_BUFFER 6
#define MAX_GPA_BUFFER 3
#define MAX_NAME_BUFFER 100

/* 
 * Function: ReadLine
 * Usage: s = ReadLine();
 * ---------------------
 * ReadLine reads a line of text from standard input and returns
 * the line as a string.  The newline '\n' character that terminates
 * the input is not stored as part of the string.
 */
char *ReadLine(void);


/*
 * Driver'
 */
int
main(int argc, char *arvg[])
{
    // YOU NEED TO IMPLEMENT THIS driver1.c USING FUNCTIONS FROM mylinkedlist.h
    // But before that, implement your ReadLine() function, and test it as shown below. 
    // IF NEEDED, YOU CAN ALSO IMLEMENT YOUR OWN FUNCTIONS HERE

    unsigned int choice;
    unsigned int index_choice;
    const size_t id_buff_size = MAX_ID_BUFFER;
    const size_t gpa_buff_size = MAX_GPA_BUFFER;
    const size_t name_buff_size = MAX_NAME_BUFFER;
    linked_list_T *list = NewLinkedList();
    

    do {

        print_options();
        scanf("%i", &choice);

        switch (choice) {
            case 1:
                fprintf(stdout, "\n\nCREATING STUDENT\n\n");
                fprintf(stdout, "Enter student ID: ");
                char *id_str = read_line(id_buff_size);
                fprintf(stdout, "Enter student GPA: ");
                char *gpa_str = read_line(gpa_buff_size);
                fprintf(stdout, "Enter student name: ");
                char *name = read_name(name_buff_size);
                char *endptr;  // Pointer to the next character after the number
                int id = (int) strtol(id_str, &endptr, 10);
                double gpa = (double) strtold(gpa_str, &endptr);
                check_for_str_to_type_error(id, endptr);
                check_for_str_to_type_error((int) gpa, endptr);

                student_cell_T *student = NewStudentCell(id, gpa, name);
                Enlist(list, student);
                fprintf(stdout, "Student added: ");
                print_student_attributes(student);
                break;
            case 2:
                fprintf(stdout, "\n\nDELISTING STUDENT\n\n");
                student_cell_T *removed_student = list->head;
                fprintf(stdout, "\nRemoving: \n");
                print_student_attributes(removed_student);
                Delist(list);
                /* free(removed_student->name); */
                /* free(removed_student); */
                break;
            case 3:
                fprintf(stdout, "\n\nPRINTING LENGTH OF LINKED LIST\n\n");
                fprintf(stdout, "\nNumber of students: %i\n\n", LinkedListLength(list));
                break;
            case 4:
                /* RIGHT HERE: YOU'RE GETTING AN ADDRESS BOUNDARY ERROR */
                fprintf(stdout, "\n\nFETCHING STUDENT BY INDEX\n\n");
                fprintf(stdout, "\nEnter index: ");
                scanf("%i", &index_choice);
                student_cell_T *chosen_student = GetLinkedListElement(list, index_choice);
                
                if (chosen_student == NULL) {
                    fprintf(stderr, "\nERROR: Invalid index %i\n", 
                            index_choice);
                    break;
                } else {
                    print_student_attributes(chosen_student);
                }
                break;
            case 5:
                fprintf(stdout, "\n\nPRINTING LIST OF ALL STUDENTS\n\n");
                print_list(list);
                break;
            case 6:
                /* PRINT THE MIN, AVG, MAX GPAS IN LINKED LIST */
                fprintf(stdout, "\n\nPRINTING MINIMUM, AVERAGE, AND MAXIMUM GPA\n\n");
                print_gpa_min_avg_max(list); // Initialize minimum value to a large valuein_avg_max(list);                
                break;
            case 7:
                /* REMOVE THE STUDENT WITH THE HIGHEST GPA AND PRINT HIS/HER INFO */
                fprintf(stdout, "\n\nREMOVING STUDENT WITH HIGHEST GPA\n\n");
                remove_highest_gpa_student(list);
                break;
            case 8:
                fprintf(stdout, "\n\nEXITING PROGRAM\n\n");
                break;
            default:
                fprintf(stdout, "Invalid choice\n");
                break;
        }

    } while (choice != 8);

    FreeLinkedList(list);

    fprintf(stdout, "\nEnd of program, thank you for using assignment 0. I love working with pointers /s\n");
    

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

