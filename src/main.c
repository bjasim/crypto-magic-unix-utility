/*
* Filename:    main.c
* Project:     cryptoMagic
* Author:      Bakr Jasim
* Date:        2022-01-22
* Description: This is the main function of the cryptoMagic utility, and the purpose of this main function * is to process command line arguments from the user and encrypt the specfied file or decrypt it depending * on the commands entered by user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../inc/cryptoMagic.h"

int main(int argc, char **argv) 
{
    int mode = ENCRYPT;    //encryption mode
    char *infile_name;     
    char *outfile_name;    
    FILE *infile;          //file will be writing from 
    FILE *outfile;         //file will be writing to

    if (argc < 2)  //if we have less than 2 args
    {
        printf("Usage: cryptoMagic [-encrypt|-decrypt] input_file\n");
        return 1;
    }

    //if 3 args
    if (argc == 3) 
    {
    	//if the second arg is "-dercrypt"
        if (strcmp(argv[1], "-decrypt") == 0) 
        {
            mode = DECRYPT;	// means the mode is decrypt
        } 
        // else if the second ars is not -encrypt, then it's an error
        else if (strcmp(argv[1], "-encrypt") != 0) 
        {
            printf("Invalid argument: %s\n", argv[1]);
            return 1;
        }
        infile_name = argv[2];  //the file name
    } 
    else 
    {
        infile_name = argv[1];  //if mode is not specified, then second arg is the file name
    }

    //if couldn't access the file specified
    if(access(infile_name, F_OK) == -1) 
    {
        printf("Error: Could not access input file %s\n", infile_name);
        return 1;
    }
    //read the file
    infile = fopen(infile_name, "r");
    if (infile == NULL) 
    {
        printf("Error: Could not open input file %s\n", infile_name);
        return 1;
    }

    if (mode == ENCRYPT) 
    {
    // if the file extension is not .crp
        if (strstr(infile_name, ".crp") == NULL) 
        {
        //if the file doesn't have an extension
            if (strstr(infile_name, ".") == NULL) 
            {
                outfile_name = malloc(strlen(infile_name) + 5);
                if(outfile_name == NULL)
                {
                    fclose(infile);
                    printf("Error: Memory allocation failed\n");
                    return 1;
                }
                sprintf(outfile_name, "%s.crp", infile_name);
            } 
            else 
            {
                outfile_name = malloc(strlen(infile_name) + 1);
                if(outfile_name == NULL)
                {
                    fclose(infile);
                    printf("Error: Memory allocation failed\n");
                    return 1;
                }
                strcpy(outfile_name, infile_name);
                char *dot = strstr(outfile_name, ".");
                if(dot == NULL)
                {
                    free(outfile_name);
                    fclose(infile);
                    printf("Error: Could not find dot in input file name\n");
                    return 1;
                }
                dot[1] = 'c';
                dot[2] = 'r';
                dot[3] = 'p';
            }
         } 
         else 
         {
            outfile_name = malloc(strlen(infile_name) + 1);
            if(outfile_name == NULL)
            {
                fclose(infile);// close the file once we're done
                printf("Error: Memory allocation failed\n");
                return 1;  //return failed
            }
         }
         outfile = fopen(outfile_name, "w");
         if (outfile == NULL) 
         {
              printf("Error: Could not open output file %s\n", outfile_name);
              fclose(infile);  //close the file
              free(outfile_name);
              return 1;    //return failure
         }
         if (encrypt_file(infile, outfile) == -1) 
         {
              printf("Error: Encryption failed\n");
              fclose(infile);
              fclose(outfile);
              free(outfile_name);
              remove(outfile_name);
              return 1;
         }
     }
     else {
        if (strstr(infile_name, ".txt") == NULL) {
            if (strstr(infile_name, ".") == NULL) {
                outfile_name = malloc(strlen(infile_name) + 5);
                if(outfile_name == NULL){
                    fclose(infile);
                    printf("Error: Memory allocation failed\n");
                    return 1;
                }
                sprintf(outfile_name, "%s.txt", infile_name);
            } else {
                outfile_name = malloc(strlen(infile_name) + 1);
                if(outfile_name == NULL){
                    fclose(infile);
                    printf("Error: Memory allocation failed\n");
                    return 1;
                }
                strcpy(outfile_name, infile_name);
                char *dot = strstr(outfile_name, ".");
                if(dot == NULL){
                    free(outfile_name);
                    fclose(infile);
                    printf("Error: Could not find dot in input file name\n");
                    return 1;
                }    dot[1] = 't';
                dot[2] = 'x';
                dot[3] = 't';
            }
        } else {
            outfile_name = malloc(strlen(infile_name) + 1);
            if(outfile_name == NULL){
                fclose(infile);
                printf("Error: Memory allocation failed\n");
                return 1;
            }
            strcpy(outfile_name, infile_name);
        }
        outfile = fopen(outfile_name, "w");
        if (outfile == NULL) {
            printf("Error: Could not open output file %s\n", outfile_name);
            fclose(infile);
            free(outfile_name);
            return 1;
        }
        if (decrypt_file(infile, outfile) == -1) {
            printf("Error: Decryption failed\n");
            fclose(infile);
            fclose(outfile);
            free(outfile_name);
            remove(outfile_name);
            return 1;
        }
    }
     
     //here where we will call the fucntions for encrypting, and decrypting based on the mode
     //if mode is ecrypt, then call the encryption function to encrypt the file
     if (mode == ENCRYPT) 
     {
          encrypt_file(infile, outfile);
     } 
     //else, the mode is not encrypt, so call the decryption function
     else 
     {
          decrypt_file(infile, outfile);
     }

     //make sure to close files after we're done using them
     fclose(infile);
     fclose(outfile);
     //and make sure to free the allocated memory
     free(outfile_name);
     return 0;   
}

            

