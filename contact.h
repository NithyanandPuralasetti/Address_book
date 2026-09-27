#ifndef CONTACT_H
#define CONTACT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 100

// Structure to store contact details
typedef struct {
    char name[50];
    char mobile_num[30];
    char mail_id[50];
    int con_count;
} Contact;

// Core contact operations
void create_contact(Contact list[], int max_cont);
int* search_contact(Contact list[], int z, int search);
void edit_contact(Contact list[], int edit, int serial);
void delete_contact(Contact list[], int delete_idx);
void list_contact(Contact list[], int max_cont);
void list_contact_from_file(Contact list[], int max_cont);
void save_contact(Contact list[]);
int initialize_contacts(Contact list[], int max_cont);

// Validation helper functions
int name_val(Contact list[], int *z);
int mobileNumVal(Contact list[], int *z);
int mail_val(Contact list[], int *z);
int non_alphabets(char *name, int *ucount);
int my_isnum(char *mobile_num, int size);
int my_mail(char *mail_id, int mail_size, int *atcount, int *dotcount, int *domainsize, int *comc, int *atindex);

// Array utility
void empty_global_array(void);

#endif