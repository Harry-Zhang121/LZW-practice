#include<iostream>
#include<fstream>
#include<io.h>
#include<process.h>
#include"LZW.h"


int main(int argc, char **argv)
{
    if(argc < 2)
        std::cerr << "Not enough arguments, please type \"./LZW -h \" for help." << std::endl;

    int cmd;
    char *inpath;
    char *outpath;

    // Use getopt function to process command line arguments.
    while((cmd = getopt(argc, argv, "hf:cd")) != -1)
    {
        switch(cmd)
        {
            case 'f':
                std::cout << "input file:" << optarg << std::endl;
                inpath = optarg;
                break;

            case 'c':
            {
                std::cout << "compressing" << std::endl;
                Compress task1(inpath);
                task1.run_compress();
                printf("success\n");
                break;
            }

            case 'd':
            {
                std::cout << "decompressing" << std::endl;
                Decompress task2(inpath);
                task2.run_decompress();
                printf("success\n");
                break;
            }

            case '?':
                std::cerr << "arguments error, please type \"./LZW -h \" for help." << std::endl;
                break;

            case 'h':
                std::cout << "Welcome to LZW.\nUsage: ./LZW -i [input_file] -o [output_file] [options]" << std::endl;
                break;
        }
    }
}
