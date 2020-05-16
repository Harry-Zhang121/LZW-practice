#include <fstream>

class IAlgorithm
{
    protected:
    std::ifstream in_stream;
    std::ofstream out_stream;

    bool file_open_mode;
    //open_mode 0: prepare file stream for compress.
    //opem_mode 1: prepare file stream for decompress.

    
};