#include<iostream>
#include<vector>
#include<fstream>

class Node
{
    public:
        int previous;
        int current;
        Node(int prev, int curr): previous(prev), current(curr) {};
    
    // static node make_node(int pre, int cur)
    // {
    //     class node temp;
    //     temp.previous = pre;
    //     temp.current = cur;
    //     return temp;
    // }
};

class LZW
{
    std::vector<Node> Dict;
    int ct;
    int p;

    public:
    LZW();      //Initialize the dictionary
    ~LZW();

    void p_test();
    void compress(std::ifstream &instream, std::ofstream &outstream);

    void char_out(int symbol, std::ofstream &outstream, int *letter);
    void decompress(std::ifstream &instream, std::ofstream &outstream);

};
