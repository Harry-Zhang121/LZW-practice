#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

// The dictionary structure.
typedef struct dictionary
{
    int previous;
    int current;
} dic_str;

int ct;
int p;
dic_str *dic;


// Initialize the dictionary. Use first 255 ASCII values for index.
void ini_dic(dic_str *dic)
{

    for(int i=0; i<=255; i++)
    {
        dic[i].previous = -1;
        dic[i].current = i;
    }
    ct = 256;
    // Initialy p is -1.
    p = -1;
}

// A simple die function for printing the error message.
void die(char *message)
{
    if(errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

// Main compress function
void compress(char *inpath, char *outpath)
{
    dic = (dic_str*) malloc(65536*sizeof(dic_str));
    if(!dic)
        die("Memory allocation failed");

    ini_dic(dic);
    // Word is the temporary variable to store the current character for processing.
    int word;

    FILE *fpin = NULL;
    fpin = fopen(inpath, "r");

    FILE *fpout = NULL;
    fpout = fopen(outpath, "w");

    while(1)
    {
        // Read one character from the input file.
        word = fgetc(fpin);
        // Break if reached the end.
        if(feof(fpin))
            break;

        // A little switcher to replace If-else statements.
        // Beasuce the if statement is in the for loop.
        int sw = 0;
        // run the loop to check if the character is in the dictionary.
        for(int i=0; i<ct; i++)
        {
            // If in the dictionary, p = the index of dictionary.
            if(dic[i].previous == p && dic[i].current == word)
            {
                p = i;
                sw = 1;
            }
        }

        // If not in the dictionary, create a new dictionary element for the word.
        if(!sw)
        {
            dic[ct].previous = p;
            dic[ct].current = word;

            //output p in 4 digits hex format. 2^16 = 16^4 = 65536
            fprintf(fpout, "%04X", p);
            p = word;
            ct++;
      }
    }
    // We don't need to include the dictionary to the file.
    free(dic);
    fclose(fpin);
    fclose(fpout);
}

// Separate the function for recursion.
void charout(int symbol, FILE *fpout, int *letter, dic_str *dic)
{
    if(dic[symbol].previous != -1)
    {
        charout(dic[symbol].previous, fpout, letter, dic);
    }

    else
    {
        //return the first char of the word for creating the new dictionary element.
        *letter = dic[symbol].current;
    }

    fprintf(fpout, "%c", dic[symbol].current);
}

// Main decompress function.
void decompress(char *inpath, char *outpath)
{
    dic = (dic_str*) malloc(65536*sizeof(dic_str));
    ini_dic(dic);
    int symbol;

    FILE *fpin = NULL;
    fpin = fopen(inpath, "r");

    FILE *fpout = NULL;
    fpout = fopen(outpath, "w");

    while(fscanf(fpin,"%04X", &symbol) != EOF)
    {
        int first_letter;
        // Call the charout function to output the comolete word.
        charout(symbol, fpout, &first_letter, dic);


        if(p != -1)
        {
            dic[ct].previous = p;
            dic[ct].current = first_letter;
            ct++;
        }
        p = symbol;
    }
    free(dic);
    fclose(fpin);
    fclose(fpout);
}


int main(int argc, char *argv[])
{
    if(argc < 2)
        die("Not enough arguments, please type \"./LZW -h \" for help.");

    int cmd;
    char *inpath;
    char *outpath;

    // Use getopt function to process command line arguments.
    while((cmd = getopt(argc, argv, "hi:o:cd")) != -1)
    {
        switch(cmd)
        {
            case 'i':
                printf("input file:%s\n", optarg);
                inpath = optarg;
                break;

            case 'o':
                printf("output file:%s\n", optarg);
                outpath = optarg;
                break;

            case 'c':
                printf("compressing\n");
                compress(inpath, outpath);
                printf("success\n");
                break;

            case 'd':
                printf("decompressing\n");
                decompress(inpath, outpath);
                printf("success\n");
                break;

            case '?':
                die("arguments error, please type \"./LZW -h \" for help. ");
                break;

            case 'h':
                printf("Welcome to LZW.\nUsage: ./LZW -i [input_file] -o [output_file] [options] ");
                break;
        }
    }
}
