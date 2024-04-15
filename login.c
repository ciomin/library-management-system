/* ********************************************************************/
/* login.c -  See login.h for copyright and info                              */
/* ********************************************************************/

/* System headers and application specific headers: */
#include "login.h"
#include "menu.h"

/* Private constants: */
#define FILE_NAME "login.bin"

/* Private types: */

/* Private global variables: */

/* Public global variables: */
unsigned short int loginOnce = 0;

/* Implementation of the private functions: */

/* Implementation of the public functions: */
/* ****************************************************************************/
/* FUNCTION NAME: passwordReset                                                           */
/* DESCRIPTION: resets the password in case it is forgotten                       */
/* ARGUMENT LIST:                                                                                      */
/* RETURN VALUE: void                                                                                */
/* CHANGES: -                                                                                              */
/* ****************************************************************************/
void passwordReset() {
    FILE *fp = NULL;
    const char defaultPassword[] = "admin";

    fp = fopen(FILE_NAME, "wb");
    if (fp == NULL) {
        fprintf(stderr, "\nCouldn't access the database\n");
        exit (1);
    }
    fwrite(defaultPassword, sizeof(defaultPassword), 1, fp);
    fclose(fp);
}
/* ****************************************************************************/
/* FUNCTION NAME: passwordChange                                                        */
/* DESCRIPTION: changes the password to one input by the user               */
/* ARGUMENT LIST:                                                                                       */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void passwordChange() {
    FILE *fp = NULL;
    char password[MAX_SIZE_PASSWORD] = "\0", pwd[MAX_SIZE_PASSWORD] = "\0";

    headMessage("CHANGE PASSWORD");

    printf("\n\n\n");
    printf("\t\t\tTo change your password, you must first type your current password.\n");

    fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        fprintf(stderr, "\nCouldn't access the database\n");
        exit (1);
    }

    fread(pwd, sizeof(pwd), 1, fp);
    rewind(fp);
    printf("\n\t\t\tOld password: ");
    scanf("%s", password);
    fflush(stdin);

    if (strcmp(password, pwd) == 0) {
        printf("\n\t\t\tNew password: ");
        scanf("%s", password);
        fflush(stdin);
        fwrite(password, sizeof(password), 1, fp);
        fclose(fp);
        loginOnce = 0;
        clear();
        mainMenu(1);
    } else {
        printf("\n\t\t\tIncorrect password!");
        printf("\n\t\t\tPress ENTER to go back.\n\t\t\t");
        fflush(stdin);
        getchar();
        fflush(stdin); //useful in case other characters are being pressed
        clear();
        editMenu(1);
    }
}
/* ****************************************************************************/
/* FUNCTION NAME: passwordLogin                                                           */
/* DESCRIPTION: allows the user to access the control panel by password login */
/* ARGUMENT LIST:                                                                                      */
/* Argument                    Type       IO        Description                                 */
/* ------------------     ----------- -------- ------------------------------         */
/* unsigned short int      tries           I        handles failed login attempts     */
/* RETURN VALUE: void                                                                                 */
/* CHANGES: -                                                                                               */
/* ****************************************************************************/
void passwordLogin(unsigned short int tries) {
    FILE *fp = NULL;
    char password[MAX_SIZE_PASSWORD] = "\0", pwd[MAX_SIZE_PASSWORD] = "\0";

    headMessage("LOGIN SCREEN");

    printf("\n\n\n");
    if (tries > 0) {
        printf("\t\t\tWelcome to the most pointless security system.\n");
        printf("\n\t\t\tLOGIN is required only ONCE.\n\n");
        printf("\t\t\tLogin attempts left: %u\n", tries);
        printf("\t\t\tInput your password: ");

        fp = fopen(FILE_NAME, "ab+");
        if (fp == NULL) {
            fprintf(stderr, "\nCouldn't access the database\n");
            exit (1);
        }

        fread(pwd, sizeof(pwd), 1, fp);
        scanf("%s", password);
        fflush(stdin);
        if (strcmp(password, pwd) == 0) {
            fclose(fp);
            clear();
            loginOnce = 1;
            editMenu(1);
        } else {
            clear();
            passwordLogin(tries-1);
        }

    } else {
        printf("\t\t\tSorry, seems you forgot your password!\n\n");
        printf("\t\t\tJust kidding. We're gonna reset it for you. [default password: admin]\n");
        printf("\t\t\tMake sure you remember it next time.\n\n");
        passwordReset();
        printf("\t\t\tPress ENTER to go back.\n\t\t\t");
        fflush(stdin);
        getchar();
        fflush(stdin); //useful in case other characters are being pressed
        clear();
        mainMenu(1);
    }
}
