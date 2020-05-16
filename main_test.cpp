#include<iostream>
#include<fstream>
#include<string>
#include"LZW.h"

int main()
{
    // std::string inpath = "test.txt";
    // std::string outpath = "test.lzw";

    int chooes;
    std::cin >> chooes;
    if(chooes == 0)
    {
        LZW task1;
        task1.file_to_open("test.txt", 0);
        task1.compress();

    }
    else
    {
        LZW task2;
        task2.file_to_open("test.lzw", 1);
        task2.decompress();
    }
    
}
