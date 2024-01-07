/*
* Filename:    cryptoMagic.h
* Project:     cryptoMagic
* Author:      Bakr Jasim
* Date:        2022-01-22
* Description: This is the header file that contains two function parameters, those functions are called in the main * function in order to decrypt/encrypt the specified file depending on the command entered by the user.
*/


#ifndef CRYPTOMAGIC_H
#define CRYPTOMAGIC_H

#define ENCRYPT 1
#define DECRYPT 0

int encrypt_file(FILE *infile, FILE *outfile);
int decrypt_file(FILE *infile, FILE *outfile);

#endif

