#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unistd.h>

//Structure of the Dictionary.
class Node
{
    public:
        int previous;
        int current;
        Node(int prev, int curr): previous(prev), current(curr) {};
    
};

//Base class, contain file streams and dictionary.
class LZW
{
    protected:
    std::ifstream in_stream;
    std::ofstream out_stream;

    std::vector<Node> Dictionary;
    int counter;
    int previous_char;

    public:
    LZW();
    ~LZW();

};

// Compress class inhareted from LZW base class.
class Compress : public LZW
{
    public:
    //This constructor will open the output file determind by the name of the input file as a binary file.
    Compress(std::string path);

    void run_compress();

};

// Decompress class inhareted from LZW base class.
class Decompress : public LZW
{
    public:
    //This constructor will open the input file determind by the name of the output file as a binary file.
    Decompress(std::string path);


    void char_out(int symbol, int *letter);
    void run_decompress();
};
