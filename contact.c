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

// Access global variables from main.c
extern int arr[MAX_CONTACTS];
extern int arr_count;

// Function to create a new contact
void create_contact(Contact list[], int max_cont)
{
    int *ptr = &list->con_count;
    int res = 0, num_res = 0, mail_res = 0;
    char confirm;

    // Check if the contact limit is reached
    if (list->con_count > max_cont)
    {
        printf(RED"!!! The limit to store contacts is reached !!!"RESET);
    }

    // Name validation
    res = name_val(list, ptr);
    if (res == 0)
    {
        list[*ptr].name[0] = '\0';
        list[*ptr].mobile_num[0] = '\0';
        list[*ptr].mail_id[0] = '\0';
        return;
    }
    if (res != 0)
    {
        // Confirm if user wants to continue after name validation
        printf(GREEN"Are you sure you want to Continue ? (Y/N) : "RESET);
        scanf("%c", &confirm);
        while ((getchar()) != '\n');
        if (confirm == 'y' || confirm == 'Y')
        {
            printf(GREEN"Continuing...\n"RESET);
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            printf(RED"Exiting....\n"RESET);
            return;
        }
        else
        {
            printf(YELLOW"Enter Valid input\n"RESET);
            return;
        }
    }

    // Mobile number validation
    num_res = mobileNumVal(list, ptr);
    if (num_res == 0)
    {
        list[*ptr].name[0] = '\0';
        list[*ptr].mobile_num[0] = '\0';
        list[*ptr].mail_id[0] = '\0';
        return;
    }
    if (num_res != 0)
    {
        // Confirm if user wants to continue after phone validation
        printf(GREEN"Are you sure you want to Continue ? (Y/N) : "RESET);
        scanf("%c", &confirm);
        while ((getchar()) != '\n');
        if (confirm == 'y' || confirm == 'Y')
        {
            printf(GREEN"Continuing...\n"RESET);
        }
        else if (confirm == 'n' || confirm == 'N')
        {
            printf(RED"Exiting....\n"RESET);
            return;
        }
        else
        {
            printf(YELLOW"Enter Valid input\n"RESET);
            return;
        }
    }

    // Mail validation
    mail_res = mail_val(list, ptr);
    if (mail_res == 0)
    {
        list[*ptr].name[0] = '\0';
        list[*ptr].mobile_num[0] = '\0';
        list[*ptr].mail_id[0] = '\0';
        return;
    }

    // All validations passed, increase count
    list->con_count++;
    printf(GREEN"Contact %d created\n"RESET, list->con_count);
}

// Function for name validation (gives 3 attempts)
int name_val(Contact list[], int* z)
{
    for (int i = 1; i < 4; i++)
    {
        int count = 3 - i;
        int non_alpha = 0, ucount = 0, pcount = 0;
        int valid = 0;

        printf(BLUE"Enter your name : "RESET);
        fgets(list[*z].name, 50, stdin);
        list[*z].name[strcspn(list[*z].name, "\n")] = '\0'; // Remove newline character

        int size = strlen(list[*z].name);
        non_alpha = non_alphabets(list[*z].name, &ucount);

        if (non_alpha == 1)
        {
            if (size > 3)
            {
                printf(RED"!!! Enter 'only' Alphabets.... %d attempts remaining !!!\n"RESET, count);
                valid = 0;
            }
            else
            {
                printf(RED"!!! Name should contain 'minimum' 3 letters and 'only' alphabets... %d attempts remaining !!!\n"RESET, count);
                valid = 0;
            }
        }
        else if (non_alpha == 0)
        {
            if (size < 3 && ucount < 3)
            {
                printf(RED"!!! Name should contain 'minimum' 3 letters... %d attempts remaining !!!\n"RESET, count);
                valid = 0;
            }
            else if (size < 4 && ucount >= 1)
            {
                printf(RED"!!! Enter alphabets and name should contain minimum 3 letters...%d attempts remaining !!!\n"RESET, count);
                valid = 0;
            }
            else if (ucount > 2)
            {
                printf(RED"!!! Only two underscores are valid...%d attempts remaining !!!\n"RESET, count);
                valid = 0;
            }
            else
            {
                break; // Valid name input
            }
        }

        if (count == 0 && valid == 0)
        {
            return 0; // Out of attempts
        }
    }
    return 1;
}

// Function for mobile number validation (gives 3 attempts)
int mobileNumVal(Contact list[], int* z)
{
    for (int i = 1; i < 4; i++)
    {
        int num_size = 0;
        int valid = 0;
        int num_count = 3 - i;
        int repeat = 1;

        printf(BLUE"Enter your Mobile num : "RESET);
        fgets(list[*z].mobile_num, 30, stdin);
        list[*z].mobile_num[strcspn(list[*z].mobile_num, "\n")] = '\0';

        num_size = strlen(list[*z].mobile_num);
        int digits = my_isnum(list[*z].mobile_num, num_size);

        // Check if number already exists
        for (int j = 0; j < *z; j++)
        {
            if (strcmp(list[*z].mobile_num, list[j].mobile_num) == 0)
            {
                printf(RED"!!! Number already exists...Enter another number...%d attempts remianing !!!\n"RESET, num_count);
                repeat = 0;
                if (num_count == 0 && repeat == 0)
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
        }

        if (num_size != 10)
        {
            printf(RED"!!! Mobile number should be 10 digits.... %d attempts remaining !!!\n"RESET, num_count);
            valid = 0;
        }
        else if (!(list[*z].mobile_num[0] >= '6' && list[*z].mobile_num[0] <= '9'))
        {
            printf(RED"!!! Mobile number should only start with 6 to 9 %d attempts remaining !!!\n"RESET, num_count);
            valid = 0;
        }
        else if (digits)
        {
            printf(RED"!!! Mobile number should only contain digits... %d attempts remaining !!!\n"RESET, num_count);
            valid = 0;
        }
        else if (repeat == 0)
        {
            continue;
        }
        else
        {
            break; // Number is valid
        }

        if (num_count == 0 && valid == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Function for mail ID validation (gives 3 attempts)
int mail_val(Contact list[], int* z)
{
    for (int i = 1; i < 4; i++)
    {
        int mail_size = 0, comc = 0;
        int atcount = 0, dotcount = 0;
        int rep = 1;
        int atindex = 0;
        int domainsize = 0;
        int mail_count = 3 - i;
        int valid = 0;

        printf(BLUE"Enter your mail id : "RESET);
        fgets(list[*z].mail_id, 50, stdin);
        list[*z].mail_id[strcspn(list[*z].mail_id, "\r\n")] = '\0';

        mail_size = strlen(list[*z].mail_id);
        int stop = my_mail(list[*z].mail_id, mail_size, &atcount, &dotcount, &domainsize, &comc, &atindex);

        // Check if email already exists
        for (int j = 0; j < *z; j++)
        {
            if (strcmp(list[j].mail_id, list[*z].mail_id) == 0)
            {
                printf(RED"!!! Mail already exists...Enter another mail..%d attempts remaining !!!\n"RESET, mail_count);
                rep = 0;
                if (mail_count == 0 && rep == 0)
                {
                    return 0;
                }
                else
                {
                    break;
                }
            }
        }

        if (atcount == 0)
        {
            printf(RED"!!! Atleast one '@' should be present .... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (atindex < 6)
        {
            printf(RED"!!! Atleast 6 characters should be present before '@' .... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (atcount != 1)
        {
            printf(RED"!!! Only one '@' is allowed .... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (dotcount == 0)
        {
            printf(RED"!!! Atleast one '.' should be present .... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (dotcount != 1)
        {
            printf(RED"!!! Only one '.' is allowed.... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (domainsize < 1)
        {
            printf(RED"!!! Atleast one character should be present in between \"@\" and ,\".com\" ... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (comc != 1)
        {
            printf(RED"!!! \".com\" should be present ... %d attempts remaining\n"RESET, mail_count);
            valid = 0;
        }
        else if (stop != 1)
        {
            printf(RED"!!! No character is allowed after \".com\" ... %d attempts remaining !!!\n"RESET, mail_count);
            valid = 0;
        }
        else if (rep == 0)
        {
            continue;
        }
        else
        {
            break; // Email is valid
        }

        if (mail_count == 0 && valid == 0)
        {
            return 0;
        }
    }
    return 1;
}

// Helper: Checks for non-alphabet characters and counts underscores
int non_alphabets(char* name, int* ucount)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == '_')
        {
            *ucount += 1;
        }
        char ch = name[i];
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\n' || ch == '_' || ch == '.' || ch == ' '))
        {
            return 1;
        }
    }
    return 0;
}

// Helper: Checks if the phone number contains non-numeric characters
int my_isnum(char* mobile_num, int size)
{
    for (int i = 0; i < size; i++)
    {
        char ch = mobile_num[i];
        if (ch < '0' || ch > '9')
        {
            return 1;
        }
    }
    return 0;
}

// Helper: Inspects structure of the email address
int my_mail(char* mail_id, int mail_size, int* atcount, int* dotcount, int* domainsize, int* comc, int* atindex)
{
    int dotindex = 0;
    for (int i = 0; i < mail_size; i++)
    {
        char ch = mail_id[i];
        if (ch == '@')
        {
            *atcount = *atcount + 1;
            *atindex = i;
        }
        else if (ch == '.')
        {
            *dotcount = *dotcount + 1;
            dotindex = i;
        }
    }

    if (*atcount == 1)
    {
        *domainsize = dotindex - *atindex - 1;
    }
    if (*dotcount == 1)
    {
        if (strncmp(&mail_id[dotindex], ".com", 4) == 0)
        {
            *comc = 1;
        }
    }
    if (mail_id[dotindex + 4] == '\0')
    {
        return 1;
    }
    return 0;
}

// Search contacts by name, mobile, or email
int* search_contact(Contact list[], int z, int search)
{
    char name[50], num[20], mail[50];
    int found = 0;
    int flag = 0;
    int index = 0;

    switch (search)
    {
        case 1:
            printf(BLUE"Enter Name : "RESET);
            fgets(name, 30, stdin);
            name[strcspn(name, "\n")] = '\0';
            printf(GREEN"---------------------------------------------------------------------------------------------------\n");
            printf("%-10s %-30s %-28s %-40s\n", "S.NO", "NAME", "MOBILE NUMBER", "MAIL ID");
            printf("---------------------------------------------------------------------------------------------------\n"RESET);
            for (int i = 0; i < z; i++)
            {
                list[i].name[strcspn(list[i].name, "\n")] = '\0';
                char* nameptr = strstr(list[i].name, name);
                if (nameptr != NULL)
                {
                    found = 1;
                    list[i].name[strcspn(list[i].name, "\n")] = '\0';
                    list[i].mobile_num[strcspn(list[i].mobile_num, "\n")] = '\0';
                    list[i].mail_id[strcspn(list[i].mail_id, "\n")] = '\0';
                    printf(BLUE"%-10d %-30s %-28s %-40s\n"RESET, i + 1, list[i].name, list[i].mobile_num, list[i].mail_id);
                    arr[arr_count] = i + 1;
                    arr_count++;
                    flag++;
                }
            }
            printf(GREEN"%d Contact(s) found\n"RESET, flag);
            flag = 0;
            if (found == 0)
            {
                printf(RED"Contact not found\n"RESET);
                arr[0] = 0;
            }
            return arr;
            break;

        case 2:
            printf(BLUE"Enter Mobile number : "RESET);
            fgets(num, 20, stdin);
            num[strcspn(num, "\n")] = '\0';
            printf(GREEN"---------------------------------------------------------------------------------------------------\n");
            printf("%-10s %-30s %-28s %-40s\n", "S.NO", "NAME", "MOBILE NUMBER", "MAIL ID");
            printf("---------------------------------------------------------------------------------------------------\n"RESET);
            for (int i = 0; i < z; i++)
            {
                list[i].mobile_num[strcspn(list[i].mobile_num, "\n")] = '\0';
                char* numptr = strstr(list[i].mobile_num, num);
                if (numptr != NULL)
                {
                    found = 1;
                    list[i].name[strcspn(list[i].name, "\n")] = '\0';
                    list[i].mobile_num[strcspn(list[i].mobile_num, "\n")] = '\0';
                    list[i].mail_id[strcspn(list[i].mail_id, "\n")] = '\0';
                    printf(BLUE"%-10d %-30s %-28s %-40s\n"RESET, i + 1, list[i].name, list[i].mobile_num, list[i].mail_id);
                    arr[arr_count] = i + 1;
                    arr_count++;
                    flag++;
                }
            }
            printf(GREEN"%d Contact(s) found\n"RESET, flag);
            flag = 0;
            if (found == 0)
            {
                printf(RED"Contact not found\n"RESET);
                arr[0] = 0;
            }
            return arr;
            break;

        case 3:
            printf(BLUE"Enter Mail ID : "RESET);
            fgets(mail, 50, stdin);
            mail[strcspn(mail, "\n")] = '\0';
            printf(GREEN"---------------------------------------------------------------------------------------------------\n");
            printf("%-10s %-30s %-28s %-40s\n", "S.NO", "NAME", "MOBILE NUMBER", "MAIL ID");
            printf("---------------------------------------------------------------------------------------------------\n"RESET);
            for (int i = 0; i < z; i++)
            {
                list[i].mail_id[strcspn(list[i].mail_id, "\n")] = '\0';
                char* mailptr = strstr(list[i].mail_id, mail);
                if (mailptr != NULL)
                {
                    found = 1;
                    list[i].name[strcspn(list[i].name, "\n")] = '\0';
                    list[i].mobile_num[strcspn(list[i].mobile_num, "\n")] = '\0';
                    list[i].mail_id[strcspn(list[i].mail_id, "\n")] = '\0';
                    printf(BLUE"%-10d %-30s %-28s %-40s\n"RESET, i + 1, list[i].name, list[i].mobile_num, list[i].mail_id);
                    arr[arr_count] = i + 1;
                    arr_count++;
                    flag++;
                }
            }
            printf(GREEN"%d Contact(s) found\n"RESET, flag);
            flag = 0;
            if (found == 0)
            {
                printf(RED"!!! Contact not found !!!\n"RESET);
                arr[0] = 0;
            }
            return arr;
            break;

        default:
            found = 0;
            printf(RED"!!! Enter Valid Input !!!\n"RESET);
            break;
    }
}

// Function to edit contact fields
void edit_contact(Contact list[], int edit, int serial)
{
    int k = serial - 1;
    int edit_non_alpha = 0, edit_ucount = 0, edit_pcount = 0, edit_valid = 0;

    switch (edit)
    {
        case 1:
            name_val(list, &k);
            break;
        case 2:
            mobileNumVal(list, &k);
            break;
        case 3:
            mail_val(list, &k);
            break;
        case 4:
            name_val(list, &k);
            mobileNumVal(list, &k);
            mail_val(list, &k);
            break;
        default:
            printf(RED"!!! Enter Valid Input !!!\n"RESET);
            break;
    }
}

// Function to delete contact by shifting remaining contacts
void delete_contact(Contact list[], int delete)
{
    int total = list->con_count;
    for (int i = delete - 1; i < total - 1; i++)
    {
        list[i] = list[i + 1];
    }
    list->con_count = total - 1;
}

// Function to display contacts directly from CSV file
void list_contact_from_file(Contact list[], int max_cont)
{
    FILE *file = fopen("new.csv", "r");
    if (file == NULL) {
        printf(RED"The list is Empty!\n"RESET);
        return;
    }

    char name[50], phone[15], email[50];
    char buffer[200];

    // Read and skip header lines
    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);

    int i = 0;
    printf(GREEN"---------------------------------------------------------------------------------------------------\n");
    printf("%-10s %-30s %-28s %-40s\n", "S.NO", "NAME", "MOBILE NUMBER", "MAIL ID");
    printf("---------------------------------------------------------------------------------------------------\n"RESET);

    while (fgets(buffer, sizeof(buffer), file) != NULL && list->con_count < max_cont) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        int parsed = sscanf(buffer, "%49[^,],%14[^,],%49[^,]", name, phone, email);

        if (parsed == 3)
        {
            printf(BLUE"%-10d %-30s %-28s %-40s\n"RESET, i + 1, name, phone, email);
            i++;
        }
    }
    fclose(file);
}

// Function to display contacts stored in memory
void list_contact(Contact list[], int max_cont)
{
    printf(GREEN"---------------------------------------------------------------------------------------------------\n");
    printf("%-10s %-30s %-28s %-40s\n", "S.NO", "NAME", "MOBILE NUMBER", "MAIL ID");
    printf("---------------------------------------------------------------------------------------------------\n"RESET);

    for (int i = 0; i < list->con_count; i++)
    {
        list[i].name[strcspn(list[i].name, "\n")] = '\0';
        list[i].mobile_num[strcspn(list[i].mobile_num, "\n")] = '\0';
        list[i].mail_id[strcspn(list[i].mail_id, "\n")] = '\0';
        printf(BLUE"%-10d %-30s %-28s %-40s\n"RESET, i + 1, list[i].name, list[i].mobile_num, list[i].mail_id);
    }

    if (list->con_count == 0)
    {
        printf(RED"!!! The list is empty !!!\n"RESET);
        printf("\n");
    }
}

// Function to save contacts to CSV file
void save_contact(Contact list[])
{
    FILE *file = fopen("new.csv", "w");
    if (file == NULL) {
        printf(RED"The file is empty!\n"RESET);
        return;
    }

    fprintf(file, "Total Contacts,%d\n", list->con_count);
    fprintf(file, "Name,Mobileno,Mail\n");

    for (int i = 0; i < list->con_count; i++)
    {
        fprintf(file, "%s,%s,%s\n", list[i].name, list[i].mobile_num, list[i].mail_id);
    }

    fclose(file);
    printf(GREEN"Contact(s) is Saved to the file.\n"RESET);
}

// Function to load saved contacts from CSV on startup
int initialize_contacts(Contact list[], int max_cont)
{
    FILE *file = fopen("new.csv", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    char buffer[200];
    fgets(buffer, sizeof(buffer), file);
    fgets(buffer, sizeof(buffer), file);

    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && list->con_count < max_cont) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        int parsed = sscanf(buffer, "%49[^,],%14[^,],%49[^,]",
                            list[count].name,
                            list[count].mobile_num,
                            list[count].mail_id);
        if (parsed == 3) {
            count++;
        }
    }

    fclose(file);
    return count;
}

// Reset the global search indices array
void empty_global_array()
{
    arr_count = 0;
    memset(arr, 0, sizeof(arr));
}