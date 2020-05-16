#include<iostream>
#include<fstream>
#include<getopt.h>
#include"LZW.h"

using namespace std;

int main(int argc, char *argv[])
{
    // if(argc < 2)
    //     die("Not enough arguments, please type \"./LZW -h \" for help.");

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
                LZW task1;
                task1.file_to_open(inpath);
                task1.compress();
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
