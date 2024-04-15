/* ***************************************************************/
/* sorting.h - Header file for module sorting                    */
/* Copyright: 2020                                               */
/* License: Tehnical University of Cluj-Napoca                   */
/* Author: Monika Imola Bokotey & Florin-Cosmin Iacobut          */
/* Version: 06-01-2021                                           */
/* Updates: ~~                                                   */
/* ***************************************************************/
#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

/*    Headers required by the following definitions/declarations:    */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"

/* Constants definitions:  */

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
void showTable();
void swapStruct(Books*, Books*);
void sortByID(Books*, unsigned int, unsigned short int);
void sortByName(Books*, unsigned int, unsigned short int);
void sortByAuthor(Books*, unsigned int, unsigned short int);
void sortByGenre(Books*, unsigned int, unsigned short int);
void sortByYear(Books*, unsigned int, unsigned short int);

#endif
