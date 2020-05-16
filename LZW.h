#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "IAlgorithm.h"

class Node
{
    public:
        int previous;
        int current;
        Node(int prev, int curr): previous(prev), current(curr) {};
    
};

class LZW : public IAlgorithm
{
    std::vector<Node> Dictionary;
    int ct;
    int p;


    public:
    
    LZW();      //Initialize the dictionary
    LZW(std::string path);

    ~LZW();

    virtual void file_to_open(std::string path, bool open_mode);
    
    // void compress(std::ifstream &in_stream, std::ofstream &out_stream);

    // void char_out(int symbol, std::ofstream &out_stream, int *letter);
    // void decompress(std::ifstream &in_stream, std::ofstream &out_stream);

    void compress();

    void char_out(int symbol, int *letter);
    void decompress();

};
