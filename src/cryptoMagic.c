/*
* Filename:    cryptoMagic.c
* Project:     cryptoMagic
* Author:      Bakr Jasim
* Date:        2022-01-22
* Description: This file contains two functions, those functions are called in the main function in order to
* decrypt/encrypt the specified file depending on the command entered by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/cryptoMagic.h"

/*
* Function: encrypt_file
* Desription: This function is used to encrypt the specified file from the command line, it will be 
* encrypted and the outut will be in a the same name but ends with the ".crp" extension.
* Parameter: infile: is the text file that function will be reading from for encrypting
	     outfile: is the .crp file that the encrypted content will be written to
* Return: returns 0, which is success
*/

int encrypt_file(FILE *infile, FILE *outfile) 
{
    int ch;
    char hex[3];
    //while its not end of file
    while ((ch = fgetc(infile)) != EOF) 
    {
	//write it to output file
	if (ch == '\r') 
	{
	    fputc(ch, outfile);
	}
	//if it's a tab
        else if (ch == '\t') 
        {
            fputs("TT", outfile);
        } 
        //if its a carriage return
        else if (ch == '\n' || ch == '\r') 
        {
            fputc(ch, outfile);
        } 
        else 
        {
            int outChar = ch - 16;
            if (outChar < 32) 
            {
                outChar = (outChar - 32) + 144;
            }
            sprintf(hex, "%02X", outChar);
            fputs(hex, outfile);
        }
    }
    return 0;
}

/*
* Function: decrypt_file
* Desription: This function is used to decrypt the specified file from the command line, it will be 
* decrypted and the outut will be in a the same name but ends with the ".txt" extension.
* Parameter: input_file: is the .crp file that function will be reading from for decrypting
	     output_file: is the .txt file that the decrypted content will be written to
* Return: returns 0, which is success
*/
int decrypt_file( FILE *input_file, FILE *output_file) 
{
    char pair[3];   //pair array
    pair[2] = '\0';   
    //go through pairs of values, 2 each time
    while (fread(pair, sizeof(char), 2, input_file) == 2) 
    {
        if (pair[0] == 'T' && pair[1] == 'T') 
        {
           fputc(9, output_file);
        } 
        //I wasn't able to get inside this if statement and tried different techniques but didn't work
        // I believe it should work, and would appreciate it if I get some feedback on why it doesn't work
        //else if ((pair[0] == '1') && ((pair[1] == '3') || (pair[1] == '0')))
        else if (pair[0] == '\r')
        {
            fputc(13, output_file);
        }

        else if (pair[0] != '\r') 
        {
            int outChar = (pair[0] >= 'A' && pair[0] <= 'F' ? pair[0] - 'A' + 10 : pair[0] - '0') * 16;
            outChar += (pair[1] >= 'A' && pair[1] <= 'F' ? pair[1] - 'A' + 10 : pair[1] - '0');
            outChar += 16;
            if (outChar > 127) 
            {
                outChar = (outChar - 144) + 32;
            }
            if(outChar == '\r') fputc('\r', output_file);
            else fputc(outChar, output_file);
      } 
      else 
      {
         fputc('\r', output_file);
      }
    }
    return 0;
}





