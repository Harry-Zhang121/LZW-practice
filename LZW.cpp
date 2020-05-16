#include "LZW.h"
#include <vector>
#include <fstream>
#include <string>


// Constructor of bass class to initialize dictionary:
LZW::LZW()
{
    for(int i=0; i<=255; i++)
    {
        Dictionary.push_back(Node(-1, i));
    }
    counter = 256;
    // Initialy there is no privous char so previous_char = -1.
    previous_char = -1;
    
}

// Destructor of bass class to clear the dictionary and close all files.
LZW::~LZW()
{
    Dictionary.clear();
    
    in_stream.close();
    out_stream.close();
}

Compress::Compress(std::string path)
{
    //----------------------------------Open files and setup in/out streams:
    in_stream.open(path, std::ios::in);

    try//This block takes the filename and open the filename.lzw
    {
        std::size_t filename_length = path.rfind('.');
        path.replace(filename_length, path.length()-filename_length, ".lzw");
    }
    // If we can not find '.' rfind will throw a std::out_of_range error.
    // '.'    >.<    *.*    ^.^    '."
    catch(std::out_of_range)
    {
        std::cerr << "Please provide a file with Filename extension" << std::endl;
        exit(1);
    }
    
    out_stream.open(path, std::ios::out | std::ios::binary);

}

Decompress::Decompress(std::string path)
{
    in_stream.open(path, std::ios::in | std::ios::binary);

    try//This block takes the filename and open the filename.txt
    {
        std::size_t filename_length = path.rfind(".lzw");
        path.replace(filename_length, 4, ".txt");
    }
    // If we can not find '.lzw' rfind will throw a std::out_of_range error.
    catch(std::out_of_range)
    {
        std::cerr << "Please provide a file with the extension '.lzw'." << std::endl;
        exit(1);
    }

    
    out_stream.open(path, std::ios::out);
}



void Compress::run_compress()
{
    char current_char;

    while(! in_stream.eof())
    {
        // Read one character from the input file.
        in_stream.get(current_char);
        
        // A little switcher to replace If-else statements.
        // Beasuce the if statement is in the for loop.
        bool sw = 0;
        // run the loop to check if the character is in the Dicttionary.
        for(int i=0; i<counter; i++)
        {
            // If in the Dicttionary, p = the index of Dicttionary.
            if(Dictionary[i].previous == previous_char && Dictionary[i].current == (int)current_char)
            {
                previous_char = i;
                sw = 1;
            }
        }

        

        // If not in the Dicttionary, create a new Dictionary element for the current_char.
        if(!sw)
        {
            Dictionary.push_back(Node(previous_char,current_char));
            
            //Write the last char to the binary file.
            out_stream.write((char*)&previous_char, sizeof(int));
            previous_char = (int)current_char;
            counter++;
      }
    } 
}

// Separate the function for recursion.
void Decompress::char_out(int current_symbol, int *letter)
{
    if(Dictionary[current_symbol].previous != -1)
    {
        char_out(Dictionary[current_symbol].previous, letter);
    }

    else
    {
        //return the first char of the current_char for creating the new dictionary element.
        *letter = Dictionary[current_symbol].current;
    }
    
    out_stream.put((char)Dictionary[current_symbol].current);
}

// Main decompress function.
void Decompress::run_decompress()
{
    int current_symbol;

    while(!in_stream.eof())
    {
        // Read one char from binary file and convert it into ascii.
        in_stream.read((char*)&current_symbol, sizeof(int));
        int first_letter;
        // Call the charout function to output the complete word.
        char_out(current_symbol, &first_letter);


        if(previous_char != -1)
        {
            Dictionary.push_back(Node(previous_char,first_letter));
            counter++;
        }
        previous_char = current_symbol;
    }
}