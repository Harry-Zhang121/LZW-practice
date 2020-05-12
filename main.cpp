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

int main()
{
    ifstream ins;
    ins.open("test.txt", ios::in);

    ofstream outs;
    outs.open("test_out.txt", ios::out);

    class LZW task1;
    // print_file(ins);
    //task1.p_test();
    task1.compress(ins, outs);
    

}