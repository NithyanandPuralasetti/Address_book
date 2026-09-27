/*
    DOCUMENTATION:
    
    A command-line based Address Book application implemented in C that enables users to create, search, edit, delete, list, and persist 
    contact records using CSV storage.
    IF ANY CONTACTS ARE PRESENT IN FILE THEN IT WILL BE LOADED TO STRUCTURE...
    Firstly we will save the contacts in the array of structures.
    To save the contact first we need to create it and then save it to the structure.

    The contact details contain : Name 
                                  Mobile Number
                                  Mail id
    If all the validations are validated then the contact will be saved to structure. Then the structure contents will be saved to file when save contact is clicked.

    [Address Book Menu]

 ├── [1] Create contact      --> Name, Phone, Email Input & Validation
 ├── [2] Edit contact        --> Search by field -> Edit field -> Select result index  
 ├── [3] Search contact      --> Substring search by Name / Phone / Mail
 ├── [4] Delete contact      --> Search by field -> Select result index -> Confirm delete (Y/N)
 ├── [5] Save the contact    --> save to new.csv file
 ├── [6] List all contacts   --> [1] From file / [2] From memory / [3] Back
 └── [7] Exit                --> Save prompt -> Application termination

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "contact.h"

// Terminal color codes
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define RESET   "\033[0m"

// Global array to store search result indices
int arr[MAX_CONTACTS];
int arr_count;

int main()
{   
    Contact list[100];
    int max_cont = 100;
    int option;
    int edit = 0;
    int search = 0;
    int serial = 0, choice;
    int delete, total_contacts, found = 0;
    int* valid = NULL;
    char confirm;
    
    // Load existing contacts from CSV on program start
    total_contacts = initialize_contacts(list, max_cont);
    printf(GREEN"Successfully loaded %d contacts.\n\n"RESET, total_contacts);
    list->con_count = total_contacts;

    do
    {
        if (option != 0)
        {
            switch (option)
            {
                case 1:
                    create_contact(list, max_cont);
                    break;

                case 2:
                    printf(GREEN"+-------------------------------+\n");
                    printf("|\tSearch Contact \t\t|\n");
                    printf("+-------------------------------+\n");
                    printf("|1.Name\t\t\t\t|\n""|2.Mobile number\t\t|\n""|3.Mail ID\t\t\t|\n""|4.Exit\t\t\t\t|\n");
                    printf("+-------------------------------+\n"RESET);
                    printf(YELLOW"Search by : "RESET);
                    scanf("%d", &search);
                    while ((getchar()) != '\n');

                    if (search > 0 && search < 4)
                    {
                        valid = search_contact(list, list->con_count, search);
                    }
                    else if (search == 4)
                    {
                        printf(RED"!!! Exiting !!!\n"RESET);
                        break;
                    }
                    else
                    {
                        printf(RED"!!! Invalid Input !!!\n"RESET);
                        valid = NULL;
                        break;
                    }

                    if (valid != NULL && valid[0] != 0)
                    {
                        printf(GREEN"+-------------------------------+\n");
                        printf("|\t Edit Contact\t\t|\n");
                        printf("+-------------------------------+\n");
                        printf("|1.Name\t\t\t\t|\n""|2.Mobile number\t\t|\n""|3.Mail ID\t\t\t|\n""|4.ALL\t\t\t\t|\n""|5.Exit\t\t\t\t|\n");
                        printf("+-------------------------------+\n"RESET);
                        printf(YELLOW"Enter the Option : "RESET);
                        scanf("%d", &edit);
                        while ((getchar()) != '\n');

                        if (edit < 1 || edit > 4)
                        {
                            printf(RED"!!! Invalid Input !!!\n"RESET);
                        }
                        else if (edit == 5)
                        {
                            printf(RED"Exiting\n"RESET);
                            break;
                        }

                        if (edit > 0 && edit < 5)
                        {
                            printf(GREEN"Enter the Index that you want to edit:\n"RESET);
                            scanf("%d", &serial);
                            while ((getchar()) != '\n');

                            for (int i = 0; i <= arr_count; i++)
                            {
                                if (serial < list->con_count && serial == valid[i])
                                {
                                    found = 1;
                                }
                            }

                            if (found == 1)
                            {
                                edit_contact(list, edit, serial);
                                found = 0;
                            }
                            else
                            {
                                printf(RED"!!! Invalid Input !!!\n"RESET);
                            }
                            empty_global_array();
                        }
                    }
                    empty_global_array();
                    break;

                case 3:
                    printf(GREEN"+-------------------------------+\n");
                    printf("|\tSearch Contact\t\t|\n");
                    printf("+-------------------------------+\n");
                    printf("|1.Name\t\t\t\t|\n""|2.Mobile number\t\t|\n""|3. Mail ID\t\t\t|\n""|4. Exit\t\t\t|\n");
                    printf("+-------------------------------+\n"RESET);
                    printf(YELLOW"Search by : "RESET);
                    scanf("%d", &search);
                    while ((getchar()) != '\n');

                    if (search > 0 && search < 4)
                    {
                        search_contact(list, list->con_count, search);
                    }
                    else if (search == 4)
                    {
                        printf(RED"Exiting\n"RESET);
                        break;
                    }
                    else
                    {
                        printf(RED"!!! Invalid Input !!!\n"RESET);
                    }
                    break;

                case 4:
                    printf(GREEN"+-------------------------------+\n");
                    printf("|\tSearch Contact\t\t|\n");
                    printf("+-------------------------------+\n");
                    printf("|1.Name\t\t\t\t|\n""|2.Mobile number\t\t|\n""|3.Mail ID\t\t\t|\n""|4.Exit\t\t\t\t|\n");
                    printf("+-------------------------------+\n"RESET);
                    printf(YELLOW"Search by : "RESET);
                    scanf("%d", &search);
                    while ((getchar()) != '\n');

                    if (search > 0 && search < 4)
                    {
                        valid = search_contact(list, list->con_count, search);
                    }
                    else if (search == 4)
                    {
                        printf(RED"Exiting\n"RESET);
                        break;
                    }
                    else
                    {
                        printf(RED"!!! Invalid Input !!!\n"RESET);
                        valid = NULL;
                    }

                    if (valid != NULL && valid[0] != 0)
                    {
                        printf(RED"+-------------------------------+\n");
                        printf("|\tDelete Contact\t\t|\n");
                        printf("+-------------------------------+\n"RESET);
                        printf(YELLOW"Enter the Index number : \n"RESET);
                        scanf("%d", &delete);
                        found = 0;
                        while ((getchar()) != '\n');

                        for (int i = 0; i <= arr_count; i++)
                        {
                            if (delete < list->con_count && delete == valid[i])
                            {
                                found = 1;
                            }
                        }
                        empty_global_array();

                        if (found == 0)
                        {
                            printf(RED"!!! Invalid Input !!!\n"RESET);
                            break;
                        }

                        printf(RED"Are you sure you want to delete the contact ? (Y/N) : "RESET);
                        scanf("%c", &confirm);
                        if (confirm == 'y' || confirm == 'Y')
                        {
                            delete_contact(list, delete);
                            printf(RED"Deleting ...\n"RESET);
                            printf(RED"Contact %d is deleted ...\n"RESET, delete);
                        }
                        else if (confirm == 'n' || confirm == 'N')
                        {
                            printf(GREEN"Contact %d is not deleted...\n"RESET, delete);
                        }
                        else
                        {
                            printf(YELLOW"!!! Enter Valid input !!! \n"RESET);
                        }
                    }
                    empty_global_array();
                    break;

                case 5:
                    printf(GREEN"Are you sure you want to save ? (Y/N) : "RESET);
                    scanf("%c", &confirm);
                    while ((getchar()) != '\n');
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        save_contact(list);
                        printf(GREEN"Contacts saved .....\n"RESET);
                    }
                    else if (confirm == 'n' || confirm == 'N')
                    {
                        printf(RED"Not Saved \n"RESET);
                    }
                    else
                    {
                        printf(YELLOW"!!! Enter Valid input !!!\n"RESET);
                    }
                    break;

                case 6:
                    printf(GREEN"1.List contacts from file\n""2.List contacts from the terminal\n""3.Exit\n"RESET);
                    printf(YELLOW"Enter your choice\n"RESET);
                    scanf("%d", &choice);
                    switch (choice)
                    {
                        case 1:
                            list_contact_from_file(list, max_cont);
                            break;
                        case 2:
                            list_contact(list, max_cont);
                            break;
                        case 3:
                            printf(RED"Exiting\n"RESET);
                            break;
                    }
                    break;

                case 7:
                    printf(RED"Do you want to save before exiting ? (Y/N) : "RESET);
                    scanf("%c", &confirm);
                    while ((getchar()) != '\n');
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        save_contact(list);
                        printf(RED"Contacts saved .....\n"RESET);
                    }
                    else if (confirm == 'n' || confirm == 'N')
                    {
                        printf(GREEN"Not Saved \n"RESET);
                    }
                    else
                    {
                        printf(YELLOW"Enter Valid input\n"RESET);
                    }

                    printf(RED"Are you sure you want to exit ? (Y/N) : "RESET);
                    scanf("%c", &confirm);
                    while ((getchar()) != '\n');
                    if (confirm == 'y' || confirm == 'Y')
                    {
                        printf(RED"Exiting .....\n"RESET);
                        exit(0);
                    }
                    else if (confirm == 'n' || confirm == 'N')
                    {
                        printf(GREEN"Not Exiting\n"RESET);
                    }
                    else
                    {
                        printf(YELLOW"Enter Valid input\n"RESET);
                    }
                    break;

                default:
                    printf(RED"!!! Invalid choice !!!\n"RESET);
                    break;
            }
        }    

        // Main address book menu display
        printf(GREEN"+-------------------------------+\n");
        printf("|\tAddress book menu\t|\n");
        printf("+-------------------------------+\n");
        printf("|1.Create contact\t\t|\n""|2.Edit contact\t\t\t|\n""|3.Search contact\t\t|\n""|4.Delete contact\t\t|\n""|5.Save the contact\t\t|\n""|6.List all contacts\t\t|\n""|7.Exit\t\t\t\t|\n");
        printf("+-------------------------------+\n"RESET);
        printf(YELLOW"Enter the option : "RESET);

        // Safe integer input handling
        if (scanf("%d", &option) != 1) 
        {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            option = -1; 
        } 
        else 
        {
            while ((getchar()) != '\n'); 
        }
    } while (option != 0);

    return 0;
}