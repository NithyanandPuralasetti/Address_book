# Address Book System in C

A simple and reliable command-line Address Book application built in C. It lets users add, search, edit, delete, and view contact details with strict input validation and CSV file storage.

---

## Features

- **Manage Contacts (CRUD):** Easily create, search, edit, delete, and list all your contacts.
- **Smart Input Validation:**
  - **Name:** Checks that names contain only letters and spaces, have at least 3 characters, and allow at most two underscores.
  - **Phone Number:** Checks that the phone number is exactly 10 digits, starts with 6, 7, 8, or 9, contains only numbers, and does not already exist.
  - **Email ID:** Checks for a valid format with a single `@`, a domain name, a `.com` ending, and at least 6 characters before the `@` symbol. It also rejects duplicate emails.
  - **Attempt Limit:** Gives the user 3 chances to enter valid details before safely canceling the action.
- **Fast Search:** Find contacts quickly by typing any part of a name, phone number, or email address.
- **CSV File Storage:** Automatically loads contacts from a file (`new.csv`) when the program starts and saves changes back to the file so data is never lost.
- **Cross-Platform Friendly:** Cleanly handles both Windows (`\r\n`) and Linux (`\n`) line endings so the terminal text formats properly without alignment bugs.
- **Color-Coded Terminal:** Uses ANSI colors (green for success, red for alerts, blue for data tables) to make the menu easy to read.

---

## Project Structure

```text
├── addressbook.c   # Main menu loop and user choices
├── contact.c       # Functions for adding, validating, searching, and saving contacts
├── contact.h       # Structure definition and function declarations
├── new.csv         # CSV file where contacts are saved
└── README.md       # Project documentation
```

---

## Contact Structure

Each contact record stores the following details:

```c
typedef struct {
    char name[50];
    char mobile_num[30];
    char mail_id[50];
    int con_count;
} Contact;
```

---

## How to Build and Run

### Requirements
- GCC compiler
- Any terminal (Linux, macOS, or WSL on Windows)

### 1. Compile the Code
Run this command in your terminal:

```bash
gcc addressbook.c contact.c -o addressbook
```

### 2. Run the Application
Start the program with:

```bash
./addressbook
```

---

## Output Examples

### Main Menu
```text
+-------------------------------+
|       Address book menu       |
+-------------------------------+
|1.Create contact               |
|2.Edit contact                 |
|3.Search contact               |
|4.Delete contact               |
|5.Save the contact             |
|6.List all contacts            |
|7.Exit                         |
+-------------------------------+
Enter the option : 
```

### Contact List Display
```text
---------------------------------------------------------------------------------------------------
S.NO       NAME                           MOBILE NUMBER                MAIL ID                                 
---------------------------------------------------------------------------------------------------
1          nithya                         9876543210                   nithyanand@gmail.com                    
2          srinu                          8765432322                   srinivas@gmail.com                      
3          nithyanand                     9876543218                   nithya@gmail.com                        
---------------------------------------------------------------------------------------------------
```

### Error Validation Alerts
```text
Enter your Mobile num : 98765
!!! Mobile number should be 10 digits.... 1 attempts remaining !!!
Enter your Mobile num : 98765432@
!!! Mobile number should only contain digits... 0 attempts remaining !!!
```

---

## Author

- **P. Nithyanand**
- GitHub: [@NithyanandPuralasetti](https://github.com/NithyanandPuralasetti)
