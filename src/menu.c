/* ********************************************************************/
/* menu.c -  See menu.h for copyright and info                              */
/* ********************************************************************/

/* System headers and application specific headers: */
#include "include/menu.h"
#include "include/login.h"
#include "include/database.h"

/* Private constants: */

/* Private types: */

/* Private global variables: */

/* Public global variables: */
extern unsigned short int loginOnce;
/* Implementation of the private functions: */

/* Implementation of the public functions: */

/* ****************************************************************************/
/* FUNCTION NAME: clear                                                                            */
/* DESCRIPTION: clears the console screen                                                  */
/* ARGUMENT LIST:                                                                                      */
/* RETURN VALUE: void                                                                                */
/* CHANGES: -                                                                                              */
/* ****************************************************************************/
void clear() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

/* ****************************************************************************/
/* FUNCTION NAME: printMessageCenter                                                   */
/* DESCRIPTION: prints a message in the middle of the console                 */
/* ARGUMENT LIST:                                                                                       */
/* Argument        Type       IO        Description                                              */
/* ------------- ----------- -------- ----------------------                                 */
/* const char*   message       I        message to be printed                            */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void printMessageCenter(const char* message) {
    int len     = 0;
    int pos    = 0;
    len = (78 - strlen(message)) / 2;
    printf("\t\t\t---------------------------------------------------------------------------\n");
    printf("\t\t\t");
    for(pos = 0; pos < len; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s", message);
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
}

/* ****************************************************************************/
/* FUNCTION NAME: headMessage                                                             */
/* DESCRIPTION: displays the interface                                                        */
/* ARGUMENT LIST:                                                                                      */
/* Argument        Type       IO        Description                                             */
/* ------------- ----------- -------- ----------------------                                */
/* const char*    message       I     message to be printed                             */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void headMessage(const char *message) {
    //clear();
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############            Library Database Management            ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################\n");
    printMessageCenter(message); // displays the current part of the menu in the center of the console
}

/* ****************************************************************************/
/* FUNCTION NAME: mainMenu                                                                  */
/* DESCRIPTION: displays the main menu and its options                           */
/* ARGUMENT LIST:                                                                                      */
/* Argument                    Type       IO        Description                                 */
/* ------------------     ----------- -------- ------------------------------         */
/* unsigned short int    status           I       handles the invalid options         */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void mainMenu(unsigned short int status) {
    char choice = '\0';

    headMessage("MAIN MENU");
    printf("\n\n\t\t\t1) VIEW - browse through the list of currently available books");
    printf("\n\t\t\t2) EDIT - add, modify or remove entries from the database (login required)");
    printf("\n\n\t\t\t0) EXIT\n\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tWhat do you want to do?: ");

    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            clear();
            viewMenu(1);
            break;
        case '2':
            clear();
            if (loginOnce == 1) /* this makes sure to open the login panel only once per run */
                editMenu(1);
            else
                passwordLogin(3);
            break;
        case '0':
            exit(1);
            break;
        default:
            clear();
            mainMenu(0);
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: viewMenu                                                                   */
/* DESCRIPTION: displays the part of the menu which contains the search/sort functions */
/* ARGUMENT LIST:                                                                                       */
/* Argument                    Type       IO        Description                                  */
/* ------------------     ----------- -------- ------------------------------          */
/* unsigned short int    status           I       handles the invalid options          */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void viewMenu(unsigned short int status) {
    char choice = '\0';

    headMessage("VIEW MENU");
    printf("\n\n\t\t\t1) SEARCH - look for a specific book");
    printf("\n\t\t\t2) SORT   - sort all of the books by a specific criterion");
    printf("\n\n\t\t\t0) BACK to MAIN MENU\n\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tWhat do you want to do?: ");

    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            clear();
            searchMenu(1);
            break;
        case '2':
            clear();
            sortMenu(1);
            break;
        case '0':
            clear();
            mainMenu(1);
            break;
        default:
            clear();
            viewMenu(0);
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: searchMenu                                                                */
/* DESCRIPTION: displays the part of the menu which contains the search function */
/* ARGUMENT LIST:                                                                                       */
/* Argument                    Type       IO        Description                                  */
/* ------------------     ----------- -------- ------------------------------          */
/* unsigned short int    status           I       handles the invalid options          */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void searchMenu(unsigned short int status) {
    char choice = '\0';

    headMessage("SEARCH MENU");
    printf("\n\n\t\t\t1) SEARCH by ID");
    printf("\n\t\t\t2) SEARCH by NAME");
    printf("\n\t\t\t3) SEARCH by AUTHOR");
    printf("\n\t\t\t4) SEARCH by GENRE");
    printf("\n\t\t\t5) SEARCH by YEAR PUBLISHED");
    printf("\n\n\t\t\t0) BACK to VIEW MENU\n\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tWhat do you want to do?: ");


    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            searchEntry(1);
            break;
        case '2':
            searchEntry(2);
            break;
        case '3':
            searchEntry(3);
            break;
        case '4':
            searchEntry(4);
            break;
        case '5':
            searchEntry(5);
            break;
        case '0':
            clear();
            viewMenu(1);
            break;
        default:
            clear();
            searchMenu(0);
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: sortMenu                                                                    */
/* DESCRIPTION: displays the part of the menu which contains the sorting functions */
/* ARGUMENT LIST:                                                                                       */
/* Argument                    Type       IO        Description                                  */
/* ------------------     ----------- -------- ------------------------------          */
/* unsigned short int    status           I       handles the invalid options          */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void sortMenu(unsigned short int status) {
    char choice = '\0';

    headMessage("SORT MENU");
    printf("\n\n\t\t\tYou can sort by the following criteria:");
    printf("\n\t\t\t1) By ID");
    printf("\n\t\t\t2) By BOOK NAME");
    printf("\n\t\t\t3) By AUTHOR NAME");
    printf("\n\t\t\t4) By GENRE");
    printf("\n\t\t\t5) By YEAR PUBLISHED");
    printf("\n\n\t\t\t0) BACK to VIEW MENU\n\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tHow would you like the books to be sorted?: ");

    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            clear();
            sortingType(1,1);
            break;
        case '2':
            clear();
            sortingType(1,2);
            break;
        case '3':
            clear();
            sortingType(1,3);
            break;
        case '4':
            clear();
            sortingType(1,4);
            break;
        case '5':
            clear();
            sortingType(1,5);
            break;
        case '0':
            clear();
            viewMenu(1);
            break;
        default:
            clear();
            sortMenu(0);
        }
}

/* ****************************************************************************/
/* FUNCTION NAME: sortingType                                                                 */
/* DESCRIPTION: displays the part of the menu which contains the sorting options */
/*                           ASCENDING/DESCENDING                                             */
/* ARGUMENT LIST:                                                                                       */
/* Argument                    Type       IO        Description                                  */
/* ------------------     ----------- -------- ------------------------------          */
/* unsigned short int    status           I       handles the invalid options          */
/* unsigned short int    method        I       retains the type of sorting applied */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void sortingType(unsigned short int status, unsigned short int method) {
    char choice = '\0';

    headMessage("SORTING TYPE");
    printf("\n\n\t\t\tASCENDING or DESCENDING?");
    printf("\n\t\t\t1) ASCENDING");
    printf("\n\t\t\t2) DESCENDING");
    printf("\n\n\t\t\t0) BACK to SORT MENU\n\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tWhich method?: ");

    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            clear();
            // displays which sorting type was chosen
            if(method == 1) {
                printMessageCenter("SORTED BY ID, ASCENDING");
            } else if(method == 2) {
                printMessageCenter("SORTED BY NAME, ASCENDING");
            } else if(method == 3) {
                printMessageCenter("SORTED BY AUTHOR, ASCENDING");
            } else if(method == 4) {
                printMessageCenter("SORTED BY GENRE, ASCENDING");
            } else {
                printMessageCenter("SORTED BY YEAR, ASCENDING");
            }
            controlFunction(1, method);

            printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
            fflush(stdin);
            getchar();
            fflush(stdin); //useful in case other characters are being pressed
            clear();
            sortMenu(1);
            break;
        case '2':
            clear();
            // displays which sorting type was chosen
            if(method == 1) {
                printMessageCenter("SORTED BY ID, DESCENDING");
            } else if(method == 2) {
                printMessageCenter("SORTED BY NAME, DESCENDING");
            } else if(method == 3) {
                printMessageCenter("SORTED BY AUTHOR, DESCENDING");
            } else if(method == 4) {
                printMessageCenter("SORTED BY GENRE, DESCENDING");
            } else {
                printMessageCenter("SORTED BY YEAR, DESCENDING");
            }
            controlFunction(2, method);

            printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
            fflush(stdin);
            getchar();
            fflush(stdin); //useful in case other characters are being pressed
            clear();
            sortMenu(1);
            break;
        case '0':
            clear();
            sortMenu(1);
            break;
        default:
            clear();
            sortingType(0, method);
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: editMenu                                                                    */
/* DESCRIPTION: displays the part of the menu which contains the control panel */
/* ARGUMENT LIST:                                                                                       */
/* Argument                    Type       IO        Description                                  */
/* ------------------     ----------- -------- ------------------------------          */
/* unsigned short int    status           I       handles the invalid options          */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void editMenu(unsigned short int status) {
    char choice = '\0';
    printMessageCenter("CONTROL PANEL");
    controlFunction(1, 1);
    printf("\n\n\t\t\t1) ADD    entry");
    printf("\n\t\t\t2) MODIFY entry");
    printf("\n\t\t\t3) REMOVE entry");
    printf("\n\n\t\t\t0) BACK to MAIN MENU");
    printf("\n\n\n\t\t\t4) CHANGE password\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tWhat do you want to do?: ");

    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            clear();
            printMessageCenter("ADD ENTRY");
            controlFunction(1, 1);
            addEntry(1);
            break;
        case '2':
            clear();
            printMessageCenter("MODIFY ENTRY");
            controlFunction(1, 1);
            modifyEntry(1);
            break;
        case '3':
            clear();
            printMessageCenter("REMOVE ENTRY");
            controlFunction(1, 1);
            removeEntry();
            break;
        case '4':
            clear();
            passwordChange();
            break;
        case '0':
            clear();
            mainMenu(1);
            break;
        default:
            clear();
            editMenu(0);
    }
}
/* ****************************************************************************/
/* FUNCTION NAME: modifyMenu                                                               */
/* DESCRIPTION: displays the menu which lets the user choose what to modify for each entry */
/* ARGUMENT LIST:                                                                                       */
/* Argument                    Type       IO        Description                                  */
/* ------------------     ----------- -------- ------------------------------          */
/* unsigned short int    status           I       handles the invalid options          */
/* Books*                       temp           I       stores the structure to be modified */
/* unsigned int               pos             I       stores the location of the id to be modified */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void modifyMenu(unsigned short int status, Books *temp, unsigned int pos) {
    char choice = '\0', buffer[MAX_NAME_LENGTH] = "\0";
    unsigned short int integer = 0;

    clear();
    printMessageCenter("MODIFY ENTRY");
    controlFunction(1, 1);

    printf("\n\n\t\t\t1) BOOK NAME");
    printf("\n\t\t\t2) BOOK AUTHOR");
    printf("\n\t\t\t3) BOOK GENRE");
    printf("\n\t\t\t4) YEAR PUBLISHED");
    printf("\n\n\t\t\t0) BACK to CONTROL PANEL\n\n");

    if(status == 0) {
        printf("\t\t\tINVALID INPUT! Try again.");
    }
    printf("\n\t\t\tWhat do you want to change?: ");

    scanf("%c", &choice);
    fflush(stdin);
    switch(choice) {
        case '1':
            printf("\n\t\t\tNew NAME: ");
            gets(buffer);
            strcpy((temp + pos) -> name, buffer);
            fflush(stdin);
            break;
        case '2':
            printf("\n\t\t\tNew AUTHOR: ");
            gets(buffer);
            strcpy((temp + pos) -> author, buffer);
            fflush(stdin);
            break;
        case '3':
            printf("\n\t\t\tNew GENRE: ");
            gets(buffer);
            strcpy((temp + pos) -> genre, buffer);
            fflush(stdin);
            break;
        case '4':
            printf("\n\t\t\tNew YEAR: ");
            scanf("%hu", &integer);
            (temp + pos) -> year = integer;
            fflush(stdin);
            break;
        case '0':
            free(temp);
            clear();
            editMenu(1);
            break;
        default:
            modifyMenu(0, temp, pos);
    }
}
