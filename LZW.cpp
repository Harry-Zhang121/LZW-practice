#include"LZW.h"
#include<vector>
#include<fstream>

LZW::LZW()
{
    // std::vector<Node> Dict(0);
    for(int i=0; i<=255; i++)
    {
        Dict.push_back(Node(-1, i));
        // Dict[i] = node{1, i};
        //Dict[i].previous = -1;
        //Dict[i].current = i;
    }
    ct = 256;
    // Initialy p is -1.
    p = -1;
}
LZW::~LZW()
{
    Dict.clear();
}

void LZW::compress(std::ifstream &instream, std::ofstream &outstream)
{
    char word;

    while(! instream.eof())
    {
        // Read one character from the input file.
        instream.get(word);
        std::cout << word;
        
        // A little switcher to replace If-else statements.
        // Beasuce the if statement is in the for loop.
        bool sw = 0;
        // run the loop to check if the character is in the Dicttionary.
        for(int i=0; i<ct; i++)
        {
            // If in the Dicttionary, p = the index of Dicttionary.
            if(Dict[i].previous == p && Dict[i].current == (int)word)
            {
                p = i;
                sw = 1;
            }
        }

        

        // If not in the Dicttionary, create a new Dicttionary element for the word.
        if(!sw)
        {
            Dict.push_back(Node(p,word));
            // Dict[ct].previous = p;
            // Dict[ct].current = word;

            //output p in 4 digits hex format. 2^16 = 16^4 = 65536
            outstream.write((char*)&p, sizeof(int));
            //fprintf(fpout, "%04X", p);
            p = (int)word;
            ct++;
      }
    }
    std::cout << std::endl;
    // We don't need to include the Dicttionary to the file.
   
}

// Separate the function for recursion.
void LZW::char_out(int symbol, std::ofstream &outstream, int *letter)
{
    if(Dict[symbol].previous != -1)
    {
        char_out(Dict[symbol].previous, outstream, letter);
    }

    else
    {
        //return the first char of the word for creating the new dictionary element.
        *letter = Dict[symbol].current;
    }

    // outstream << (char)Dict[symbol].current;
    outstream.put((char)Dict[symbol].current);
}

// Main decompress function.
void LZW::decompress(std::ifstream &instream, std::ofstream &outstream)
{
    int symbol;

    while(! instream.eof())
    {
        instream.read((char*)&symbol, sizeof(int));
        int first_letter;
        // Call the charout function to output the comolete word.
        char_out(symbol, outstream, &first_letter);


        if(p != -1)
        {
            Dict.push_back(Node(p,first_letter));
            ct++;
        }
        p = symbol;
    }
}