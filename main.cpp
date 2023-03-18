#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "jasonobject.h"

int main(int argc, char **argv)
{
    if(argc == 2)
    {
        std::string file = argv[1];

        std::fstream f(file, std::ios::in);
        f.seekg(0, std::ios::end);
        std::streampos size = f.tellg();
        f.seekg(0, std::ios::beg);

        char *p = new char(size);
        f.read(p, size);
        f.close();

        char *cur = p;
        char *end = p + size;

        JasonObject root;
        if (!root.Parse(cur, end, "", '}'))
        {
            std::cout << "invalid jason format!" << std::endl;
        }

        std::string out;
        root.tostring(out);

        std::cout << out;

        //root.tostring(std::cout);
    }
    else
        std::cout << "invalid parameter!" << std::endl;

    return 0;
}
