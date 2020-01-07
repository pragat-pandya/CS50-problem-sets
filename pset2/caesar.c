#include <cs50.h>
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Taking only one command-line argument as a valid input.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        exit(1);
    }

    //Making a copy of argv[1]'s copy '.
    string CPargv = argv[1];

    //Taking only positive integers as correct command-line argument.
    for (int a = 0, b = strlen(CPargv); a < b; a++)
    {
        if (CPargv[a] < '0' || CPargv[a] > '9')
        {
            printf("Usage: ./caesar key\n");
            exit(1);
        }
    }

    //Converting the CPargv to integer data type and storing it as KEY.
    int key = atoi(argv[1]); //atoi converts strings to ints. defined in header file "stdlib.h"

    int no_of_alphas = 26;  //total number of letters in English alphabet.

    //Handling the case where the user gives command-line argument greater than 26(i.e.,Greater than the total letters in alphabet.)
    while (key > no_of_alphas)
    {
        key = key - no_of_alphas;
    }

    //After Varifying the command-line argument and succesfully storing it as an INT . Prompting user for plaintext
    string text = get_string("plaintext: ");

    //Printing the LHS placeholder for ciphertext for the output terminal.
    printf("ciphertext: ");

    //Helping variables of the following FOR LOOP.
    int printer, ascii;

    //LOOP that actually generates the ciphertext.
    for (int i = 0, n = strlen(text); i < n; i++)
    {

        //for UPPERCASE letters.
        if (isupper(text[i]))
        {
            ascii = (int) text[i];
            printer = (ascii + key);

            //In case the ascci value exceed the last alphabet letter Z!
            if (printer > 'Z')
            {
                //Redirecting the ascii value stored into var:printer in the range of AtoZ i.e., making rotation!
                printer = printer - 'Z' + 'A' - 1;
                printf("%c", printer);
            }
            else
            {
                printf("%c", printer);
            }
        }

        //for LOWERCASE letters
        else if (islower(text[i]))
        {
            ascii = (int) text[i];
            printer = (ascii + key);
            if (printer > 'z')
            {
                printer = printer - 'z' + 'a' - 1;
                printf("%c", printer);
            }
            else
            {
                printf("%c", printer);
            }
        }

        //for characters other than alphabets.
        else
        {
            ascii = (int) text[i];
            printf("%c", ascii);
        }
    }
    printf("\n");
}