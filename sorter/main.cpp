#include "PagedArray.h"
#include "QuickSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "SelectionSort.h"
#include <cstring>
#include <chrono>

int main(int argc, char* argv[])
{
    char *input = nullptr;
    char *output = nullptr;
    char *alg = nullptr;
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

    if (input == nullptr)
    {
        std::cout << "input requerido";
        return 1;
    }
    else if (output == nullptr)
    {
        std::cout << "output requerido";
        return 1;
    }
    else if (alg == nullptr)
    {
        std::cout << "algoritmo requerido";
        return 1;
    }
    else if (pageSize == 0)
    {
        std::cout << "tamaño de page requerido";
        return 1;
    }
    else if (pageCount == 0)
    {
        std::cout << "cantidad máxima de páginas requerida";
        return 1;
    }

    FILE *inputFile = fopen(input, "rb");

    if (inputFile == nullptr)
    {
        std::cout << "Error al abrir el archivo\n";
        return 1;
    }

    int block[4096];
    int read = fread(block, sizeof(int), 4096, inputFile);

    FILE *outputFile = fopen(output, "wb");

    while (read != 0)
    {
        fwrite(block, sizeof(int), read, outputFile);
        read = fread(block, sizeof(int), 4096, inputFile);
    }

    fclose(inputFile);

    fseek(outputFile, 0, SEEK_END);

    long totalInt = -1;
    long size = ftell(outputFile);

    totalInt = size / sizeof(int);

    fclose(outputFile);

    PagedArray arr(output, pageSize, pageCount);

    auto start = std::chrono::high_resolution_clock::now();

    if (strcmp(alg, "QUICK") == 0)
    {
        quickSort(arr, totalInt);
    }

    else if (strcmp(alg, "HEAP") == 0)
    {
        heapSort(arr, totalInt);
    }

    else if (strcmp(alg, "INSERTION") == 0)
    {
        insertionSort(arr, totalInt);
    }

    else if (strcmp(alg, "MERGE") == 0)
    {
        mergeSort(arr, totalInt);
    }

    else if (strcmp(alg, "SELECTION") == 0)
    {
        selectionSort(arr, totalInt);
    }

    else
    {
        std::cout << "Digite un algoritmo válido";
        return 1;
    }

    std::cout << "Algoritmo: " << alg << " SORT" << " \n";

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo: " << duration.count() << " segundos\n";

    std::string textPath = std::string(output) + ".txt";
    FILE* txtFile = fopen(textPath.c_str(), "w");

    for (int i = 0; i < totalInt; i++)
    {
        fprintf(txtFile, "%d,", arr[i]);
    }

    fclose(txtFile);

    arr.stats();

    return 0;
}