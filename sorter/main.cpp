#include "PagedArray.h"
#include <cstring>

int main(int argc, char* argv[])
{
    char *input = NULL;
    char *output = NULL;
    char *alg = NULL;
    int pageSize = 0;
    int pageCount = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-input") == 0 && i + 1 < argc)
        {
            input = argv[i + 1];
        }

        if (strcmp(argv[i], "-output") == 0 && i + 1 < argc)
        {
            output = argv[i + 1];
        }

        if (strcmp(argv[i], "-alg") == 0 && i + 1 < argc)
        {
            alg = argv[i + 1];
        }

        if (strcmp(argv[i], "-pageSize") == 0 && i + 1 < argc)
        {
            pageSize = atoi(argv[i + 1]);
        }

        if (strcmp(argv[i], "-pageCount") == 0 && i + 1 < argc)
        {
            pageCount = atoi(argv[i + 1]);
        }
    }

    if (input == NULL)
    {
        std::cout <<"input requerido";
        return 1;
    }
    else if (output == NULL)
    {
        std::cout <<"output requerido";
        return 1;
    }
    else if (alg == NULL)
    {
        std::cout <<"algoritmo requerido";
        return 1;
    }
    else if (pageSize == 0)
    {
        std::cout <<"tamaño de page requerido";
        return 1;
    }
    else if (pageCount == 0)
    {
        std::cout <<"cantidad máxima de páginas requerida";
        return 1;
    }
}