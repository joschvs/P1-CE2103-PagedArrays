//
// Created by HP on 02/04/2026.
//

#ifndef P1_CE2103_PAGEDARRAYS_MAIN_H
#define P1_CE2103_PAGEDARRAYS_MAIN_H
#include <cstdio>
#include <iostream>
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
    int slot;
    int useCounter;

    void writePage(int slot)
    {
        long pos = pageIDs[slot] * pageSize * sizeof(int);

        fseek(file, pos, SEEK_SET);
        fwrite(pages[slot], sizeof(int), pageSize, file);
    }

    int findLRUslot()
    {
        int LRU = 0;
        for (int i = 0; i < pageCount - 1; i++)
        {
            if (pageIDs[i] == -1)
            {
                return i;
            }
            else
            {
                if (lastUsed[i] < lastUsed[LRU])
                {
                    LRU = i;
                }
            }

        }
        return LRU;
    }

    void loadPage(int LRUslot, int pageID)
    {
        if (modified[LRUslot])
        {
            writePage(LRUslot);
        }

        long pos = pageID * pageSize * sizeof(int);

        fseek(file, pos, SEEK_SET);
        fread(pages[LRUslot], sizeof(int), pageSize, file);

        modified[LRUslot] = false;
        pageIDs[LRUslot] = pageID;

    }

    int& operator[](int index)
    {
        int page = index / pageSize;
        int pageSlot = index % pageSize;
        bool pageFault = false;
        int ramSlot = -1;

        for (int i = 0; i < pageCount; i++)
        {
            if (pageIDs[i] == page)
            {
                pageHits += 1;
                pageFault = false;
                ramSlot = i;
                break;

            }
            else
            {
                pageFault = true;
            }
        }

        if (pageFault)
        {
            pageFaults += 1;
            int LRUslot = findLRUslot();
            loadPage(LRUslot, page);
            ramSlot = LRUslot;
        }

        lastUsed[ramSlot] = ++useCounter;
        modified[ramSlot] = true;

        return pages[ramSlot][pageSlot];
    }

    void stats()
    {
        std::cout << "Page faults:" << pageFaults << "\n";
        std::cout << "Page hits:" << pageHits << "\n";
    }

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
        useCounter = 0;

        for (int i = 0; i < pageCount; i++)
        {
            modified[i] = false;
            lastUsed[i] = -1;
            pages[i] = new int[pageSize];
            pageIDs[i] = -1;
        }

    };
    ~PagedArray()
    {
        for (int i = 0; i < pageCount; i++)
        {
            if (modified[i])
            {
                writePage(i);
            }
        }

        delete[] modified;
        delete[] pageIDs;
        delete[] lastUsed;

        for (int i = 0; i < pageCount; i++)
        {
            delete[] pages[i];
        }

        delete[] pages;

        fclose(file);
    }
};




#endif //P1_CE2103_PAGEDARRAYS_MAIN_H