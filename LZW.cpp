#include"LZW.h"
#include<vector>
#include<fstream>

LZW::LZW()
{
    std::cout << "ini";
    std::vector<struct node> Dict(1);
    for(int i=0; i<=255; i++)
    {
        Dict.push_back(node::make_node(-1,i));
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
    int word;

    // FILE *fpin = NULL;
    // fpin = fopen(inpath, "r");

    // FILE *fpout = NULL;
    // fpout = fopen(outpath, "w");

    while(1)
    {
        // Read one character from the input file.
        instream >> word;
        // Break if reached the end.
        if(instream.eof())
            break;

        // A little switcher to replace If-else statements.
        // Beasuce the if statement is in the for loop.
        int sw = 0;
        // run the loop to check if the character is in the Dicttionary.
        for(int i=0; i<ct; i++)
        {
            // If in the Dicttionary, p = the index of Dicttionary.
            if(Dict[i].previous == p && Dict[i].current == word)
            {
                p = i;
                sw = 1;
            }
        }

        // If not in the Dicttionary, create a new Dicttionary element for the word.
        if(!sw)
        {
            Dict[ct].previous = p;
            Dict[ct].current = word;

            //output p in 4 digits hex format. 2^16 = 16^4 = 65536
            outstream << p << '/n';
            //fprintf(fpout, "%04X", p);
            p = word;
            ct++;
      }
    }
    // We don't need to include the Dicttionary to the file.
   
}