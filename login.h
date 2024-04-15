/* ***************************************************************/
/* login.h - Header file for module login                        */
/* Copyright: 2020                                               */
/* License: Tehnical University of Cluj-Napoca                   */
/* Author: Monika Imola Bokotey & Florin-Cosmin Iacobut          */
/* Version: 06-01-2021                                           */
/* Updates: ~~                                                   */
/* ***************************************************************/
#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

/*    Headers required by the following definitions/declarations:    */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Constants definitions:  */
#define MAX_SIZE_PASSWORD 15

/* Types definitions: */

/* Global variables declarations: */

/* Function prototypes: */
void passwordReset();
void passwordChange();
void passwordLogin(unsigned short int);

#endif
