#include <cstring>
#include <iostream>
#include <string.h>


int main(int argc, char* argv[])
{
    char *size = NULL;
    char *output = NULL;
    long totalInt;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--size") == 0 && i + 1 < argc)
        {
            size = argv[i + 1];
        }
        if (strcmp(argv[i], "--output") == 0 && i + 1 < argc)
        {
            output = argv[i + 1];
        }
    }

    if (size == NULL || output == NULL)
    {
        std::cout <<"size o output requerido";
        return 1;
    }
    if (strcmp(size, "SMALL") == 0)
    {
        totalInt = 128000000;
    }
    else if (strcmp(size, "MEDIUM") == 0)
    {
        totalInt = 256000000;
    }
    else if (strcmp(size, "LARGE") == 0)
    {
        totalInt = 512000000;
    }
    else
    {
        std::cout << "Error";
        return 1;
    }


    return 0;

}