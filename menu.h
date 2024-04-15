/* ***************************************************************/
/* menu.h - Header file for module menu                          */
/* Copyright: 2020                                               */
/* License: Tehnical University of Cluj-Napoca                   */
/* Author: Monika Imola Bokotey & Florin-Cosmin Iacobut          */
/* Version: 06-01-2021                                           */
/* Updates: ~~                                                   */
/* ***************************************************************/
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

/*    Headers required by the following definitions/declarations:    */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "database.h"

/* Constants definitions:  */

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
void clear();
void printMessageCenter(const char*);
void headMessage(const char*);
void mainMenu(unsigned short int);
void viewMenu(unsigned short int);
void searchMenu(unsigned short int);
void editMenu(unsigned short int);
void sortMenu(unsigned short int);
void sortingType(unsigned short int, unsigned short int);
void modifyMenu(unsigned short int, Books*, unsigned int);

#endif
