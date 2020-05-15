#include<iostream>
#include<fstream>
#include"LZW.h"

using namespace std;

void print_file(std::ifstream &instream)
{
    char word;
    while (!instream.eof())
    {
        instream >> word;
        std::cout << "Now reading:" << word;
    }
    
}

void comp()
{
    ifstream ins;
    ins.open("test.txt", ios::in);

    ofstream outs;
    outs.open("test_out_comp.lzw", ios::out | ios::binary);

    class LZW task1;
    // print_file(ins);
    //task1.p_test();
    task1.compress(ins, outs);
    

}

void decomp()
{
    ifstream ins;
    ins.open("test_out_comp.lzw", ios::in | ios::binary);

    ofstream outs;
    outs.open("test_out.txt", ios::out);

    class LZW task2;
    task2.decompress(ins, outs);
}

int main()
{
    int chooes;
    cin >> chooes;
    if(chooes == 1)
    comp();
    else
    decomp();
}