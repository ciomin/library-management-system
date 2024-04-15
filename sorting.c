/* ********************************************************************/
/* sorting.c -  See sorting.h for copyright and info                          */
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
/* FUNCTION NAME: swapStruct                                                                  */
/* DESCRIPTION: function that swaps two structures                                   */
/* ARGUMENT LIST:                                                                                       */
/* Argument      Type       IO        Description                                                */
/* -------     ----------- -------- ------------------------------                          */
/* Books*        struct1        I        gets swapped with struct2                          */
/* Books*        struct2        I        gets swapped with struct1                          */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void swapStruct(Books *struct1, Books *struct2) {
    Books temp = {0};
    temp = *struct1;
    *struct1 = *struct2;
    *struct2 = temp;
}

/* ****************************************************************************/
/* FUNCTION NAME: showTable                                                                   */
/* DESCRIPTION: displays the frame of the table                                          */
/* ARGUMENT LIST:                                                                                       */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void showTable() {
    const char *id = "ID";
    const char *name = "NAME";
    const char *author = "AUTHOR";
    const char *genre = "GENRE";
    const char *year = "YEAR";
    printf ("\t\t%7s |%30s |%23s |%15s |%5s\n", id, name, author, genre, year);
    printf ("\t\t    ----|-------------------------------|------------------------|----------------|-----\n");
}

/* ****************************************************************************/
/* FUNCTION NAME: sortByID                                                                      */
/* DESCRIPTION: sorts the structures by their ID                                          */
/* ARGUMENT LIST:                                                                                       */
/* Argument                   Type           IO        Description                               */
/* --------------         -------------  --------  -----------------------------------*/
/* Books*                     holdBooks        I        holds the array of structures    */
/* unsigned int              count              I        holds the size of holdBooks     */
/* unsigned short int     order              I        handles ASCENDING/DESCENDING order */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void sortByID(Books *holdBooks, unsigned int count, unsigned short int order) {
    unsigned int i = 0, j = 0;

    //BubbleSort in ascending and descending order of ID
    if (order == 1) {
        for(i = 0; i < count - 1; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if((holdBooks + j) -> id > (holdBooks + j + 1) -> id) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    } else if (order == 2) {
        for(i = 0; i < count - 1; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if((holdBooks + j) -> id < (holdBooks + j + 1) -> id) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: sortByName                                                                */
/* DESCRIPTION: sorts the structures by their book names                          */
/* ARGUMENT LIST:                                                                                       */
/* Argument                   Type           IO        Description                               */
/* --------------         -------------  --------  -----------------------------------*/
/* Books*                     holdBooks        I        holds the array of structures   */
/*  unsigned int              count              I        holds the size of holdBooks   */
/* unsigned short int     order              I        handles ASCENDING/DESCENDING order */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void sortByName(Books *holdBooks, unsigned int count, unsigned short int order) {
    unsigned int i = 0, j = 0;

    //BubbleSort in ascending and descending order of NAME
    if (order == 1) {
        for(i = 0; i < count; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if(strcmp((holdBooks + j) -> name, (holdBooks + j + 1) -> name) > 0) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    } else if (order == 2) {
        for(i = 0; i < count; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if(strcmp((holdBooks + j) -> name, (holdBooks + j + 1) -> name) < 0) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: sortByAuthor                                                              */
/* DESCRIPTION: sorts the structures by their book author                         */
/* ARGUMENT LIST:                                                                                      */
/* Argument                   Type           IO        Description                              */
/* --------------         -------------  --------  ----------------------------------*/
/* Books*                     holdBooks        I        holds the array of structures   */
/* unsigned int              count              I        holds the size of holdBooks    */
/* unsigned short int     order              I        handles ASCENDING/DESCENDING order */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void sortByAuthor(Books *holdBooks, unsigned int count, unsigned short int order) {
    unsigned int i = 0, j = 0;

    //BubbleSort in ascending and descending order of AUTHOR
    if (order == 1) {
        for(i = 0; i < count; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if(strcmp((holdBooks + j) -> author, (holdBooks + j + 1) -> author) > 0) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    } else if (order == 2) {
        for(i = 0; i < count; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if(strcmp((holdBooks + j) -> author, (holdBooks + j + 1) -> author) < 0) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: sortByGenre                                                                */
/* DESCRIPTION: sorts the structures by their book genre                           */
/* ARGUMENT LIST:                                                                                       */
/* Argument                   Type           IO        Description                               */
/* --------------         -------------  --------  -----------------------------------*/
/* Books*                     holdBooks        I        holds the array of structures    */
/* unsigned int              count              I        holds the size of holdBooks     */
/* unsigned short int     order              I        handles ASCENDING/DESCENDING order */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* *****************************************************************************/
void sortByGenre(Books *holdBooks, unsigned int count, unsigned short int order) {
    unsigned int i = 0, j = 0;

    //BubbleSort in ascending and descending order of GENRE
    if (order == 1) {
        for(i = 0; i < count; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if(strcmp((holdBooks + j) -> genre, (holdBooks + j + 1) -> genre) > 0) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    } else if (order == 2) {
        for(i = 0; i < count; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if(strcmp((holdBooks + j) -> genre, (holdBooks + j + 1) -> genre) < 0) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    }
}

/* ****************************************************************************/
/* FUNCTION NAME: sortByYear                                                                   */
/* DESCRIPTION: sorts the structures by the year the books have been published */
/* ARGUMENT LIST:                                                                                       */
/* Argument                   Type           IO        Description                               */
/* --------------         -------------  --------  -----------------------------------*/
/* Books*                     holdBooks        I        holds the array of structures    */
/* unsigned int              count              I        holds the size of holdBooks     */
/* unsigned short int     order              I        handles ASCENDING/DESCENDING order */
/* RETURN VALUE: void                                                                                  */
/* CHANGES: -                                                                                                */
/* ************************************************************************** **/
void sortByYear(Books *holdBooks, unsigned int count, unsigned short int order) {
    unsigned int i = 0, j = 0;

    //BubbleSort in ascending and descending order of YEAR
    if (order == 1) {
        for(i = 0; i < count - 1; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if((holdBooks + j) -> year > (holdBooks + j + 1) -> year) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    } else if (order == 2) {
        for(i = 0; i < count - 1; i++) {
            for(j = 0; j < count - i - 1; j++) {
                if((holdBooks + j) -> year < (holdBooks + j + 1) -> year) {
                    swapStruct(holdBooks + j, holdBooks + j + 1);
                }
            }
        }
    }
}
