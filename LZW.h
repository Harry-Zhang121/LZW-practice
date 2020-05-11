#include<iostream>
#include<vector>
#include<fstream>

class node
{
    public:
    int previous;
    int current;
    
    static node make_node(int pre, int cur)
    {
        class node temp;
        temp.previous = pre;
        temp.current = cur;
        return temp;
    }
};

class LZW
{
    private:
    std::vector<struct node> Dict;
    int ct;
    int p;

    public:
    LZW();      //Initialize the dictionary
    ~LZW();

    void compress(std::ifstream &instream, std::ofstream &outstream);
    void decompress(char *inpath, char *outpath);

};