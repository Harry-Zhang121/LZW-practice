#include "LZW.h"
#include "compress_exception.h"
#include <vector>
#include <fstream>
#include <string>





LZW::LZW(std::string path)
{
    //----------------------------------Open files and setup in/out streams:

    if(!file_open_mode)
    //open_mode 0: prepare file stream for compress.
    //opem_mode 1: prepare file stream for decompress.
    {
        
        in_stream.open(path, std::ios::in);

        try
        {
            std::size_t filename_length = path.rfind('.');
            path.replace(filename_length, path.length()-filename_length, ".lzw");

        }
        // If we can not find '.' rfind will throw a std::out_of_range error.
        // '.'    >.<    *.*    ^.^    '."
        catch(std::out_of_range)
        {
            std::cerr << "Please provide a file with Filename extension" << '\n';
        }
       
        out_stream.open(path, std::ios::out | std::ios::binary);
    }
    else
    {
        in_stream.open(path, std::ios::in | std::ios::binary);

        try
        {
            std::size_t filename_length = path.rfind(".lzw");
            path.replace(filename_length, 4, ".txt");
        }
        catch(std::out_of_range)
        {
            std::cerr << "Please provide a file with the extension '.lzw'." << '\n';
        }

        
        out_stream.open(path, std::ios::out);
    }


    // --------------------------------------------Initialize dictionary:

    for(int i=0; i<=255; i++)
    {
        Dictionary.push_back(Node(-1, i));
    }
    ct = 256;
    // Initialy p is -1.
    p = -1;
    
    
}

// Destructor, clear the dictionary and close all files.
LZW::~LZW()
{
    Dictionary.clear();
    
    in_stream.close();
    out_stream.close();
}

void LZW::compress()
{
    // If compress function is called but file_open_mode is not set for compress, Throw an error.
    try{if(!file_open_mode) throw open_mode_error();}
    catch(std::exception &error)
    { std::cerr << error.what() << std::endl;}


    char word;

    while(! in_stream.eof())
    {
        // Read one character from the input file.
        in_stream.get(word);
        
        // A little switcher to replace If-else statements.
        // Beasuce the if statement is in the for loop.
        bool sw = 0;
        // run the loop to check if the character is in the Dicttionary.
        for(int i=0; i<ct; i++)
        {
            // If in the Dicttionary, p = the index of Dicttionary.
            if(Dictionary[i].previous == p && Dictionary[i].current == (int)word)
            {
                p = i;
                sw = 1;
            }
        }

        

        // If not in the Dicttionary, create a new Dicttionary element for the word.
        if(!sw)
        {
            Dictionary.push_back(Node(p,word));
            
            //Write the index number to the binary file.
            out_stream.write((char*)&p, sizeof(int));
            p = (int)word;
            ct++;
      }
    } 
}

// Separate the function for recursion.
void LZW::char_out(int symbol, int *letter)
{
    if(Dictionary[symbol].previous != -1)
    {
        char_out(Dictionary[symbol].previous, letter);
    }

    else
    {
        //return the first char of the word for creating the new dictionary element.
        *letter = Dictionary[symbol].current;
    }
    
    out_stream.put((char)Dictionary[symbol].current);
}

// Main decompress function.
void LZW::decompress()
{
    int symbol;

    while(! in_stream.eof())
    {
        in_stream.read((char*)&symbol, sizeof(int));
        int first_letter;
        // Call the charout function to output the comolete word.
        char_out(symbol, &first_letter);


        if(p != -1)
        {
            Dictionary.push_back(Node(p,first_letter));
            ct++;
        }
        p = symbol;
    }
}