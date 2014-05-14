#include <fstream>
#include<algorithm>
#include <string>
int ctline(std::string fn)
{
    std::ifstream aFile(fn);
    int lines_count =0;
    std::string line;
    while (std::getline(aFile , line))
        ++lines_count;
    return lines_count;
}
