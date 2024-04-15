/* ********************************************************************/
/* database.c -  See database.h for copyright and info                   */
/* ********************************************************************/

/* System headers and application specific headers: */
#include "menu.h"
#include "sorting.h"

/* Private constants: */
#define FILE_NAME "books.bin"

/* Private types: */

/* Private global variables: */

/* Public global variables: */

/* Implementation of the private functions: */

/* Implementation of the public functions: */

/* ****************************************************************************/
/* FUNCTION NAME: displayBooks                                                               */
/* DESCRIPTION: displays the structures in table format                              */
/* ARGUMENT LIST:                                                                                       */
/* Argument                   Type           IO        Description                               */
/* --------------         -------------  --------  ---------------------------------- */
/* Books*                       array               I        holds the array of structures   */
/* unsigned int              count              I        holds the size of array             */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void displayBooks(Books *array, unsigned int count) {
    int i = 0;
    showTable();
    for(i = 0; i < count; i++)
        printf ("\t\t%7hu |%30s |%23s |%15s |%5hu\n", (array + i) -> id, (array + i) -> name, (array + i) -> author, (array + i) -> genre, (array + i) -> year);
}

/* ****************************************************************************/
/* FUNCTION NAME: addEntry                                                                     */
/* DESCRIPTION: adds structures to the file                                                 */
/* ARGUMENT LIST:                                                                                      */
/* Argument                           Type           IO        Description                      */
/* --------------------         -------------  --------  ----------------------------*/
/* unsigned short int              status            I        checks for invalid inputs */
/* RETURN VALUE: void                                                                                */
/* CHANGES: -                                                                                              */
/* ****************************************************************************/
void addEntry(unsigned short int status) {
    FILE *fp = NULL;
    unsigned short int found = 0, success = 0;
    Books newBook = {0}, holdBook = {0};

    fp = fopen(FILE_NAME, "ab+");
    if (fp == NULL) {
        fprintf(stderr, "\nCouldn't access the database\n");
        exit (1);
    }

    printf("\n\n");
    if(status == 0) {
        printf("\t\t\tID already used! Try another one!\n");
    } else {
        printf("\t\t\tPlease make sure the ID isn't already used!\n");
    }
    printf("\t\t\tID: ");
    scanf("%hu", &newBook.id);
    fflush(stdin);

    while(fread(&holdBook, sizeof(Books), 1, fp) && found == 0) {
        if(holdBook.id == newBook.id)
            found = 1;
    }

    if(found == 1) {
        fclose(fp);
        clear();
        printMessageCenter("ADD ENTRY");
        controlFunction(1, 1);
        addEntry(0);
    } else {
        printf("\t\t\tNAME: ");
        gets(newBook.name);
        fflush(stdin);

        printf("\t\t\tAUTHOR: ");
        gets(newBook.author);
        fflush(stdin);

        printf("\t\t\tGENRE: ");
        gets(newBook.genre);
        fflush(stdin);

        printf("\t\t\tYEAR PUBLISHED: ");
        scanf("%hu", &newBook.year);
        fflush(stdin);

        if(fwrite(&newBook, sizeof(Books), 1, fp))
            success = 1;
        else
            success = 0;
        fclose(fp);

        clear();
        printMessageCenter("ADD ENTRY");
        controlFunction(1, 1);

        if(success) {
            printf("\n\n\t\t\tBook added successfully!");
        } else {
            printf("\n\n\t\t\tWhoops... we encountered an issue.");
        }
    }

    printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
    fflush(stdin);
    getchar();
    fflush(stdin); //useful in case other characters are being pressed by mistake
    clear();
    editMenu(1);
}

/* ****************************************************************************/
/* FUNCTION NAME: removeBooks                                                             */
/* DESCRIPTION: removes structures from the file                                      */
/* ARGUMENT LIST:                                                                                     */
/* RETURN VALUE: void                                                                               */
/* CHANGES: -                                                                                             */
/* ***************************************************************************/
void removeEntry() {
    unsigned short int found = 0, deleteID = 0;
    FILE *fp = NULL, *tmp = NULL;
    Books holdBook = {0};

    fp = fopen(FILE_NAME, "rb");
    if(fp == NULL) {
        fprintf(stderr, "\nCouldn't access the database\n");
        exit (1);
    }

    tmp = fopen("tmp.bin", "wb");
    if(tmp == NULL) {
        fclose(fp);
        fprintf(stderr, "\nCouldn't access the database\n");
        exit (1);
    }

    printf("\n\n\t\t\tPlease enter the ID of the book you want to REMOVE: ");
    scanf("%hu",&deleteID);
    fflush(stdin);

    while (fread(&holdBook, sizeof(Books), 1, fp)) {
        if(holdBook.id != deleteID) {
            fwrite(&holdBook, sizeof(Books), 1, tmp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(tmp);
    remove(FILE_NAME);
    rename("tmp.bin", FILE_NAME);

    if (found == 1) {
        clear();
        printMessageCenter("REMOVE ENTRY");
        controlFunction(1, 1);
        printf("\n\n\t\t\tBook has been removed successfully!\n");
    } else {
        clear();
        printMessageCenter("REMOVE ENTRY");
        controlFunction(1, 1);
        printf("\n\n\t\t\tID doesn't exist.\n");
    }

    printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
    fflush(stdin);
    getchar();
    fflush(stdin); //useful in case other characters are being pressed by mistake
    clear();
    editMenu(1);
}

/* ****************************************************************************/
/* FUNCTION NAME: modifyEntry                                                                */
/* DESCRIPTION: modifies already existing structures                                 */
/* ARGUMENT LIST:                                                                                      */
/* Argument                            Type            IO        Description                    */
/* --------------------         -------------  --------  ----------------------------*/
/* unsigned short int              status            I         handles invalid inputs    */
/* RETURN VALUE: void                                                                                */
/* CHANGES: -                                                                                              */
/* ****************************************************************************/
void modifyEntry(unsigned short int status) {
    FILE *fp = NULL;
    unsigned short int bookID = 0;
    unsigned int i = 0, pos = 0, count = 0, found = 0;
    Books *entry = NULL;

    printf("\n");
    if(status==2) {
        printf("\t\t\tID not found! Try another one.");
    }
    printf("\n\t\t\tPlease enter the ID of the book you want to EDIT: ");
    scanf("%hu",&bookID);
    fflush(stdin);

    count = countBooks();  //computes number of structures present in file
    entry = allocStruct(count); //allocates memory for the array of structures
    readBooks(entry, count); //reads structures from file

    for(i = 0; i < count; i++) {
        if((entry + i) -> id == bookID) {
            pos = i;
            found = 1;
        }
    }

    if(found == 0) {
        free(entry);
        clear();
        printMessageCenter("MODIFY ENTRY");
        controlFunction(1, 1);
        modifyEntry(2);
    } else {
        modifyMenu(1, entry, pos);

        fp = fopen(FILE_NAME, "wb");
        if(fp == NULL) {
            fprintf(stderr, "\nCouldn't access the database\n");
            exit (1);
        }
        for(i = 0; i < count; i++) {
            fwrite(entry+i, sizeof(Books), 1, fp);
        }
        fclose(fp);
        free(entry);

        clear();
        printMessageCenter("MODIFY ENTRY");
        controlFunction(1, 1);
        printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
        fflush(stdin);
        getchar();
        fflush(stdin); //useful in case other characters are being pressed by mistake
        clear();
        editMenu(1);
    }
}



/* ****************************************************************************/
/* FUNCTION NAME: countBooks                                                                 */
/* DESCRIPTION: counts the total number of structures currently in the file */
/* ARGUMENT LIST:                                                                                       */
/*    Argument           Type            IO           Description                                */
/* ---------------   -------------  --------  --------------------------------------*/
/* unsigned int         count           O         contains total number of structures */
/* RETURN VALUE: number of structures currently in file                              */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
unsigned int countBooks() {
    FILE *fp = NULL;
    Books holdBook = {0};
    unsigned int count = 0;

    fp = fopen(FILE_NAME, "ab+");
    if (fp == NULL) {
        fprintf(stderr, "\nCouldn't access the database\n");
        exit (1);
    }

    while(fread(&holdBook, sizeof(Books), 1, fp))
        count++;
    fclose(fp);
    return count;
}

/* ****************************************************************************/
/* FUNCTION NAME: allocStruct                                                                   */
/* DESCRIPTION: dynamically allocates memory for array of structures      */
/* ARGUMENT LIST:                                                                                      */
/*    Argument           Type            IO           Description                               */
/* ---------------   -------------  --------  ------------------------------          */
/* unsigned int         count             I          size of type Books array             */
/* Books*                 structure        O         returns the pointer of malloc     */
/* RETURN VALUE: pointer to Books                                                            */
/* CHANGES: -                                                                                             */
/* ***************************************************************************/
Books *allocStruct(unsigned int count) {
    Books *structure = NULL;

    structure = (Books*) malloc(count * sizeof(Books));
    if (!structure) return NULL;

    return structure;
}

/* ****************************************************************************/
/* FUNCTION NAME: controlFunction                                                          */
/* DESCRIPTION: handles everything related to the array of structures       */
/* ARGUMENT LIST:                                                                                       */
/*    Argument                   Type            IO           Description                        */
/* ---------------           -------------  --------  --------------------------------*/
/* unsigned short int         order            I          handles ASCENDING/DESCENDING order */
/* unsigned short int        method         I       handles the type of sorting to be done */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void controlFunction(unsigned short int order, unsigned short int method) {
    unsigned int count = 0;
    Books *holdBooks = NULL;

    count = countBooks();  //computes number of structures present in file
    if (count > 0) {
        holdBooks = allocStruct(count); //allocates memory for the array of structures
        readBooks(holdBooks, count); //reads structures from file

        /* sort depending on choices */
        /* IF ASCENDING */
        if (order == 1) {
            if (method == 1) {             /* SORT BY ID */
                sortByID(holdBooks, count, order);
            } else if (method == 2) {   /* SORT BY NAME */
                sortByName(holdBooks, count, order);
            } else if (method == 3) {   /* SORT BY AUTHOR */
                sortByAuthor(holdBooks, count, order);
            } else if (method == 4) {   /* SORT BY GENRE */
                sortByGenre(holdBooks, count, order);
            } else if (method == 5) {   /* SORT BY YEAR */
                sortByYear(holdBooks, count, order);
            }
        /* IF DESCENDING */
        } else if (order == 2) {
            if (method == 1) {             /* SORT BY ID */
                sortByID(holdBooks, count, order);
            } else if (method == 2) {   /* SORT BY NAME */
                sortByName(holdBooks, count, order);
            } else if (method == 3) {   /* SORT BY AUTHOR */
                sortByAuthor(holdBooks, count, order);
            } else if (method == 4) {   /* SORT BY GENRE */
                sortByGenre(holdBooks, count, order);
            } else if (method == 5) {   /* SORT BY YEAR */
                sortByYear(holdBooks, count, order);
            }
        }
        displayBooks(holdBooks, count);
        free(holdBooks);
    } else {
        showTable();
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: searchEntry                                                 */
/* DESCRIPTION: searches and displays one or more entries                     */
/* ARGUMENT LIST:                                                             */
/* Argument                    Type       IO        Description               */
/* ------------------     ----------- -------- ------------------------------ */
/* unsigned short int     option        I        stores the search options from input */
/* RETURN VALUE: void                                                         */
/* CHANGES: -                                                                 */
/* *****************************************************************************/
void searchEntry(unsigned short int option) {
    unsigned int count = 0;
    unsigned short int integer = 0, found = 0;
    char string[MAX_NAME_LENGTH] = "\0";
    Books *array = NULL;

    //display
    clear();
    headMessage("SEARCH MENU");

    count = countBooks();  //computes number of structures present in file
    if (count > 0) {
        array = allocStruct(count); //allocates memory for the array of structures
        readBooks(array, count); //reads structures from file

        //search for specific entries dependent on user input
        if(option == 1) {
            printf("\n\t\t\tID to search for: ");
            scanf("%hu", &integer);
            fflush(stdin);
            clear();
            showTable();

            for(int i = 0; i < count; i++) {
                if((array + i) -> id == integer) {
                    printf("\t\t%7hu |%30s |%23s |%15s |%5hu\n", (array + i) -> id, (array + i) -> name, (array + i) -> author, (array + i) -> genre, (array + i) -> year);
                    found = 1;
                }
            }

            if(found == 0)
                printf("\n\n\t\t\tID not found.");

        } else if(option == 2) {
            sortByID(array, count, 1);
            printf("\n\t\t\tNAME to search for: ");
            gets(string);  // nonstandard, fgets is better but we need to strip the \n character for strstr to work
            fflush(stdin);
            clear();
            showTable();

            for(int i = 0; i < count; i++) {
                if(strstr((array + i) -> name, string) != NULL) {
                    printf("\t\t%7hu |%30s |%23s |%15s |%5hu\n", (array + i) -> id, (array + i) -> name, (array + i) -> author, (array + i) -> genre, (array + i) -> year);
                    found = 1;
                }
            }

            if(found == 0)
                printf("\n\n\t\t\tNAME not found.");

        } else if(option == 3) {
            sortByID(array, count, 1);
            printf("\n\t\t\tAUTHOR to search for: ");
            gets(string); // nonstandard, fgets is better but we need to strip the \n character for strstr to work
            fflush(stdin);
            clear();
            showTable();

            for(int i = 0; i < count; i++) {
                if(strstr((array + i) -> author, string) != NULL) {
                    printf("\t\t%7hu |%30s |%23s |%15s |%5hu\n", (array + i) -> id, (array + i) -> name, (array + i) -> author, (array + i) -> genre, (array + i) -> year);
                    found = 1;
                }
            }

            if(found == 0)
                printf("\n\n\t\t\tAUTHOR not found.");

        } else if(option == 4) {
            sortByID(array, count, 1);
            printf("\n\t\t\tGENRE to search for: ");
            gets(string); // nonstandard, fgets is better but we need to strip the \n character for strstr to work
            fflush(stdin);
            clear();
            showTable();

            for(int i = 0; i < count; i++) {
                if(strstr((array + i) -> genre, string) != NULL) {
                    printf("\t\t%7hu |%30s |%23s |%15s |%5hu\n", (array + i) -> id, (array + i) -> name, (array + i) -> author, (array + i) -> genre, (array + i) -> year);
                    found = 1;
                }
            }

            if(found == 0)
                printf("\n\n\t\t\tGENRE not found.");


        } else if(option == 5) {
            sortByID(array, count, 1);
            printf("\n\t\t\tYEAR to search for: ");
            scanf("%hu", &integer);
            fflush(stdin);
            clear();
            showTable();

            for(int i = 0; i < count; i++) {
                if((array + i) -> year == integer) {
                    printf("\t\t%7hu |%30s |%23s |%15s |%5hu\n", (array + i) -> id, (array + i) -> name, (array + i) -> author, (array + i) -> genre, (array + i) -> year);
                    found = 1;
                }
            }
            if(found == 0)
                printf("\n\n\t\t\tYEAR not found.");
        }

        printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
        fflush(stdin);
        getchar();
        fflush(stdin); //useful in case other characters are being pressed by mistake
        clear();
        searchMenu(1);
    } else {
        showTable();
        printf("\n\t\t\tDatabase is EMPTY.");
        printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
        fflush(stdin);
        getchar();
        fflush(stdin); //useful in case other characters are being pressed by mistake
        clear();
        searchMenu(1);
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: readBooks                                                   */
/* DESCRIPTION: reads the structures from the file                            */
/* ARGUMENT LIST:                                                             */
/*    Argument               Type             IO           Description        */
/* --------------        -------------   --------  -----------------------------------*/
/* Books*                       array              I         stores the structures read from file */
/* unsigned int              count             I         stores the size of array  */
/* RETURN VALUE: void                                                              */
/* CHANGES: -                                                                      */
/* *****************************************************************************/
void readBooks(Books *array, unsigned int count) {
    int i = 0;
    FILE *fp = NULL;
    fp = fopen(FILE_NAME, "rb");

    for (i = 0; i < count; i++)
        fread(array+i, sizeof(Books), 1, fp);
    fclose(fp);
}
