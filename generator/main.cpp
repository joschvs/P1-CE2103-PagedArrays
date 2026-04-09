#include <cstring>
#include <iostream>
#include <random>
#include <climits>
#include <ctime>


int main(int argc, char* argv[])
{
    char *size = nullptr;
    char *output = nullptr;
    long totalInt;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-size") == 0 && i + 1 < argc)
        {
            size = argv[i + 1];
        }

        if (strcmp(argv[i], "-output") == 0 && i + 1 < argc)
        {
            output = argv[i + 1];
        }
    }

    if (size == nullptr || output == nullptr)
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

    else if (strcmp(size, "TEST") == 0)
    {
        totalInt = 32000000;
    }

    else
    {
        std::cout << "Error";
        return 1;
    }

    int block[4096];

    std::mt19937 rng(time(nullptr));
    std::uniform_int_distribution<int> dist(INT_MIN, INT_MAX);

    FILE *archivo = fopen(output, "wb");

    if (archivo == nullptr)
    {
        std::cout << "Error al abrir el archivo\n";
        return 1;
    }

    for (int j = 0; j < totalInt / 4096; j++)
    {
        for (int i = 0; i < 4096; i++)
        {
            block[i] = dist(rng);
        }

        fwrite(block, sizeof(int), 4096, archivo);
    }

    if (totalInt % 4096 != 0)
    {
        for (int i = 0; i < totalInt % 4096; i++)
        {
            block[i] = dist(rng);
        }
        fwrite(block, sizeof(int), totalInt % 4096, archivo);
    }

    fclose(archivo);

    return 0;
}