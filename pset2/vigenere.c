#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int shift(char c);
int main(int argc, string argv[])
{
    //Making a copy of the command-line argument to perform test on.
    string CPargv = argv[1];
    int key = 0;

    //If less than or greater than ONE command-line argument(s) is/are provided.
    if (argc != 2)
    {
        printf("./vigenere keyword\n");
        //Then exiting the program with exit code:1 & printing suitable error msg.
        exit(1);
    }
    //If Provided single command-line arguments as needed then checking if the string is purely alphabetic.
    else
    {
        for (int iter1 = 0, n = strlen(CPargv) ; iter1 < n; iter1++)
        {
            //Checking whether the command-line argument is purely alphabetic.
            if (isalpha(CPargv[iter1]))
                continue;
            //IF not then exiting the program with exit code:1 & printing suitable error msg.
            else
            {
                printf("./vigenere keyword\n");
                exit(1);
            }
        }//If we pass this loop then we're good to go.
    }

    int key_len = strlen(CPargv);

    //Prompting user for plaintext input.
    string text = get_string("plaintext: ");

    //Place holder for enciphered char output
    printf("ciphertext: ");

    int ascii,printer,iter3 = 0;
    for (int iter2 = 0, text_len = strlen(text); iter2 < text_len; iter2++)
    {
        if (iter3 >= key_len)
        {
            iter3 = 0;
            key = shift(CPargv[iter3]);
        }
        else
            key = shift(CPargv[iter3]);
        //for UPPERCASE letters.
        if(isupper(text[iter2]))
        {
            ascii = (int) text[iter2];
            printer = (ascii + key);

            //In case the ascci value exceed the last alphabet letter Z!
            if (printer > 'Z')
            {
                //Redirecting the ascii value stored into var:printer in the range of AtoZ i.e., making rotation!
                printer = printer - 'Z' + 'A' - 1;
                printf("%c",printer);
                iter3 += 1;
            }
            else
            {
                printf("%c",printer);
                iter3 += 1;
            }

        }

        //for LOWERCASE letters
        else if(islower(text[iter2]))
        {
            ascii = (int) text[iter2];
            printer = (ascii + key);
            if(printer > 'z')
            {
                printer = printer - 'z' + 'a' - 1;
                printf("%c",printer);
                iter3 += 1;
            }
            else
            {
                printf("%c",printer);
                iter3 += 1;
            }

        }

        //for characters other than alphabets.
        else
        {
            ascii = (int) text[iter2];
            printf("%c",ascii);
        }
    }
    printf("\n");

}



int shift(char c)
{
    if (isupper(c))
    {
        return (int) (c - 65);
    }
    else
        return (int) (c -97);
}