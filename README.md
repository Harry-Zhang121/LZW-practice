
# LZW compression developer Documentation
## About LZW algorithm
LZW algorithm is a loseless compression algorithm invented by Abraham Lempel, Jacob Ziv, and Terry Welch. The algorithm is named by there names. LZW is a lossless compression algorithm. Its compression relies on the dictionary. But the dictionary will not be included in the output file. Instead, the algorithm will generate/recreate the dictionary during the compression/decompression process.

### License
Unisys used to hold the patent for LZW. But The US patent that Unisys held expired in June 2003, and patents in other parts of the world had all expired by July 7, 2004.

## Usage
Aviliable command line arguments
| Arguments | Mining                      |
|-----------|-----------------------------|
| -h        | print the help message      |
| -i        | specify the input file path |
| -c        | compress the file           |
| -d        | decompress the file         |
The output file will be saved to the path will the program located in.


## code
### libraries
```cpp
#include "LZW.h"
#include "unistd.h"
#include <vector>
#include <fstream>
#include <string> 
```

``unistd`` libary is provided by the Linux for command line argument. *But it may not work on Windows platform*   

For windows platform ``io.h`` and ``process.h`` was used to replace unistd.h

### dictionary data structure
The only data struct I used is the dictionary node. 

```cpp
class Node
{
    public:
        int previous;
        int current;
        Node(int prev, int curr): previous(prev), current(curr) {};
    
};
```

#### example:
if the word "apple" appeared 4 times. This is how it looks like in the dictionary.
| index | previous | current |
|-------|----------|---------|
| 1.    | -1       | a       |
| 2.    | 1        | p       |
| 3.    | 2        | p       |
| 4.    | 3        | l       |
| 6.    | 4        | e       |

So next time "apple" appears. The algorithm will use 5 to represent it.

To output the whole word, simply use recursion
```cpp
charout(index)
{
	if(dic[index].previous != -1)
		charout(dic[index].previous);
	ofstream.put(dic[index].current);
}
```

