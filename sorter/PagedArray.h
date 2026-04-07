//
// Created by HP on 02/04/2026.
//

#ifndef P1_CE2103_PAGEDARRAYS_MAIN_H
#define P1_CE2103_PAGEDARRAYS_MAIN_H
#include <cstdio>
#include <wchar.h>


class PagedArray
{
private:
    FILE* file;
    int pageSize;
    int pageCount;
    int** pages;
    int* pageIDs;
    bool* modified;
    int pageFaults;
    int pageHits;
    int* lastUsed;

public:
    PagedArray(char* filePath, int pageSize, int pageCount)
    {
        pageFaults = 0;
        pageHits = 0;

        file = fopen(filePath, "rb+");

        this->pageSize = pageSize;
        this->pageCount = pageCount;

        modified = new bool[pageCount];
        lastUsed = new int[pageCount];
        pages = new int*[pageCount];
        pageIDs = new int[pageCount];

        for (int i = 0; i < pageCount; i++)
        {
            modified[i] = false;
            lastUsed[i] = -1;
            pages[i] = new int[pageSize];
            pageIDs[i] = -1;
        }

    };
};




#endif //P1_CE2103_PAGEDARRAYS_MAIN_H