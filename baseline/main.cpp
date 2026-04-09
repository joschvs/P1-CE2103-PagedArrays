#include "QuickSort.h"
#include "HeapSort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
#include "SelectionSort.h"
#include <cstring>
#include <chrono>
#include <iostream>

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

    FILE *inputFile = fopen(input, "rb");

    if (inputFile == nullptr)
    {
        std::cout << "Error al abrir el archivo\n";
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long size = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    long totalInt = size / sizeof(int);

    int* arr = new int[totalInt];

    fread(arr, sizeof(int), totalInt, inputFile);

    fclose(inputFile);

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

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Algoritmo: " << alg << "\n";
    std::cout << "Tiempo: " << duration.count() << " segundos\n";

    FILE *outputFile = fopen(output, "wb");
    fwrite(arr, sizeof(int), totalInt, outputFile);
    fclose(outputFile);

    std::string textPath = std::string(output) + ".txt";
    FILE* txtFile = fopen(textPath.c_str(), "w");

    for (long i = 0; i < totalInt; i++)
    {
        fprintf(txtFile, "%d,", arr[i]);
    }

    fclose(txtFile);

    delete[] arr;

    return 0;
}
