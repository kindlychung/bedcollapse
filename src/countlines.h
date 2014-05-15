#include <fstream>
#include<algorithm>
#include <string>
off_t countlines(std::string fn)
{
    std::ifstream aFile(fn);
    off_t lines_count =0;
    std::string line;
    while (std::getline(aFile , line))
        ++lines_count;
    return lines_count;
}
