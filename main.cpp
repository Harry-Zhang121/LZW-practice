#include<iostream>
#include<fstream>
#include"LZW.h"

using namespace std;

int main()
{
    ifstream ins;
    ins.open("test.txt", ios::in);

    ofstream outs;
    outs.open("test_out.txt", ios::out);

    class LZW task1;
    task1.compress(ins, outs);
    

}