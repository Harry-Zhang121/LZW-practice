#include <iostream>
#include <bitset>
#include <fstream>
#include <math.h>

int conv(char *array)
{
    int result = 0;
    int temp =0;


    int p = 7;
    int i = 0;
    while(p>=0 && i<=7)
    {
        std::cout << array[i] << std::endl;
        temp = (int)array[i] * pow(2,p);
        std::cout << pow(2,p) <<std::endl;
        result += temp;
        std::cout << result <<std::endl;
        i++;
        p--;
    }

    return result;
}

int main()
{   
    
    
   // char *pTemp = temp.to_string();


    std::ofstream ouF;
    ouF.open("./me.dat", std::ofstream::binary);
    for(int symbol = 5; symbol<10; symbol++)
    {
    std::cout << std::bitset<8>(symbol) << std::endl;
    ouF.write((char*)&symbol, sizeof(symbol));
    }
    // ouF.write(temp.to_string(), sizeof(int)*5);
    ouF.close();
 
    std::ifstream inF;
    inF.open("./me.dat", std::ifstream::binary);

    

    // char in_temp[8];
    for (int i=0; i<5; i++)
    {
    int in_temp;
    // inF.read(reinterpret_cast<char*>(in_temp), 8);
    inF.read((char*)&in_temp, sizeof(int));
    // inF.close();
    //std::cout << "array:" << std::endl;
    std::cout << in_temp << std::endl;
    }


    // for(int i = 0; i<8; i++)
    // {
    //     std::cout << in_temp[i];
    // }
    std::cout << std::endl;

   // std::cout << conv(in_temp) << std::endl ;
}