// gcc -g -I ../includes -o io io.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Hidden for simplicity
#include "wargames.h"
#include "io.h" 

void demo_data() 
{
    print_data_banner();
    
    // Allocate 32 bytes of memory to store user input to   
    char buffer[32] = {};
    
    // Write a message (14 bytes) to the user over standard-out
    write(STDOUT_FILENO, "Enter data: ", 12);
    
    // Read input data from the user over standard-in
    int n = read(STDIN_FILENO, buffer, sizeof(buffer));
 
    // Echo the user's input data back to them
    write(STDOUT_FILENO, "The program read in:\n", 21);
    write(STDOUT_FILENO, buffer, n);

    // User quiz
    quiz_data();
}

void demo_strings()
{  
    print_string_banner();
    
    // Allocate 32 bytes of memory to store user input to   
    char buffer[32] = {};
 
    // Read a string from the user over standard-in
    printf("Enter text: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Trim the trailing newline off the user input (if present)
    buffer[strcspn(buffer, "\n")] = 0;
 
    // Echo the user's input back to them as a string
    printf("You entered '%s'\n", buffer);

    // User quiz
    quiz_string();
}

void print_menu()
{
    printf("-- IO Playground --------------------\n"
           " 1. Low Level IO                     \n"
           " 2. String IO                        \n"
           " 3. Quit                             \n"
           "-------------------------------------\n"
           "Enter Choice: ");
}

void main()
{
    init_wargame();

    printf("------------------------------------------------------------\n");
    printf("--[ C Fundamentals - IO                                     \n");
    printf("------------------------------------------------------------\n");

    unsigned int choice = 0;

    while(1)
    {
        print_menu();
        if((choice = get_number()) == EOF)
            break;

        if(choice == 1)
            demo_data();
        else if(choice == 2)
            demo_strings();
        else if(choice == 3)
            break;
        else
            puts("Invalid choice!");

        choice = 0;
    }
}

