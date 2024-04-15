/* ***************************************************************/
/* database.h - Header file for module database                  */
/* Copyright: 2020                                               */
/* License: Tehnical University of Cluj-Napoca                   */
/* Author: Monika Imola Bokotey & Florin-Cosmin Iacobut          */
/* Version: 06-01-2021                                           */
/* Updates: ~~                                                   */
/* ***************************************************************/
#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

/*    Headers required by the following definitions/declarations:    */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Constants definitions:  */
#define MAX_NAME_LENGTH 30

/* Types definitions: */
typedef struct {
    unsigned short int id;
    char name[MAX_NAME_LENGTH];
    char author[MAX_NAME_LENGTH];
    char genre[MAX_NAME_LENGTH];
    unsigned short int year;
} Books;

/* Global variables declarations: */

/* Function prototypes: */
void displayBooks(Books*, unsigned int);
void addEntry(unsigned short int);
void removeEntry();
unsigned int countBooks();
Books *allocStruct(unsigned int);
void controlFunction(unsigned short int, unsigned short int);
void readBooks(Books*, unsigned int);
void modifyEntry(unsigned short int);
void searchEntry(unsigned short int);

#endif
