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
    long long pageFaults;
    long long pageHits;
    long long* lastUsed;
    int slot;
    long long useCounter;

    int hashTableSize;
    int* hashKeys;
    int* hashValues;
    bool* hashUsed;

    int hashFunc(int key)
    {
        unsigned int k = (unsigned int)key;
        return k % hashTableSize;
    }

    void hashInit(int capacity)
    {
        hashTableSize = capacity * 4 + 1;
        hashKeys = new int[hashTableSize];
        hashValues = new int[hashTableSize];
        hashUsed = new bool[hashTableSize];
        for (int i = 0; i < hashTableSize; i++)
        {
            hashUsed[i] = false;
        }
    }

    void hashInsert(int pageID, int slot)
    {
        int idx = hashFunc(pageID);
        while (hashUsed[idx] && hashKeys[idx] != pageID)
        {
            idx = (idx + 1) % hashTableSize;
        }
        hashKeys[idx] = pageID;
        hashValues[idx] = slot;
        hashUsed[idx] = true;
    }

    int hashFind(int pageID)
    {
        int idx = hashFunc(pageID);
        int start = idx;
        while (hashUsed[idx])
        {
            if (hashKeys[idx] == pageID)
            {
                return hashValues[idx];
            }
            idx = (idx + 1) % hashTableSize;
            if (idx == start) break;
        }
        return -1;
    }

    void hashRemove(int pageID)
    {
        int idx = hashFunc(pageID);
        int start = idx;
        while (hashUsed[idx])
        {
            if (hashKeys[idx] == pageID)
            {
                hashUsed[idx] = false;
                int next = (idx + 1) % hashTableSize;
                while (hashUsed[next])
                {
                    int tmpKey = hashKeys[next];
                    int tmpVal = hashValues[next];
                    hashUsed[next] = false;
                    hashInsert(tmpKey, tmpVal);
                    next = (next + 1) % hashTableSize;
                }
                return;
            }
            idx = (idx + 1) % hashTableSize;
            if (idx == start) break;
        }
    }

    void hashFree()
    {
        delete[] hashKeys;
        delete[] hashValues;
        delete[] hashUsed;
    }

    void writePage(int slot)
    {
        long pos = (long)pageIDs[slot] * pageSize * sizeof(int);

        fseek(file, pos, SEEK_SET);
        fwrite(pages[slot], sizeof(int), pageSize, file);
    }

    int findLRUslot()
    {
        int LRU = 0;
        for (int i = 0; i < pageCount; i++)
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
        if (pageIDs[LRUslot] != -1)
        {
            hashRemove(pageIDs[LRUslot]);
        }

        if (modified[LRUslot])
        {
            writePage(LRUslot);
        }

        long pos = (long)pageID * pageSize * sizeof(int);

        fseek(file, pos, SEEK_SET);
        fread(pages[LRUslot], sizeof(int), pageSize, file);

        modified[LRUslot] = false;
        pageIDs[LRUslot] = pageID;

        hashInsert(pageID, LRUslot);
    }

    int resolveSlot(long index)
    {
        int page = index / pageSize;
        int ramSlot = hashFind(page);

        if (ramSlot != -1)
        {
            pageHits++;
        }
        else
        {
            pageFaults++;
            int LRUslot = findLRUslot();
            loadPage(LRUslot, page);
            ramSlot = LRUslot;
        }

        lastUsed[ramSlot] = ++useCounter;
        return ramSlot;
    }

public:
    class Proxy
    {
    private:
        PagedArray& arr;
        long index;
    public:
        Proxy(PagedArray& a, long i) : arr(a), index(i) {}

        operator int() const
        {
            int ramSlot = arr.resolveSlot(index);
            int pageSlot = index % arr.pageSize;
            return arr.pages[ramSlot][pageSlot];
        }

        Proxy& operator=(int value)
        {
            int ramSlot = arr.resolveSlot(index);
            int pageSlot = index % arr.pageSize;
            arr.pages[ramSlot][pageSlot] = value;
            arr.modified[ramSlot] = true;
            return *this;
        }

        Proxy& operator=(const Proxy& other)
        {
            int value = (int)other;
            *this = value;
            return *this;
        }
    };

    PagedArray(char* filePath, int pageSize, int pageCount)
    {
        pageFaults = 0;
        pageHits = 0;
        useCounter = 0;

        file = fopen(filePath, "rb+");

        this->pageSize = pageSize;
        this->pageCount = pageCount;

        modified = new bool[pageCount];
        lastUsed = new long long[pageCount];
        pages = new int*[pageCount];
        pageIDs = new int[pageCount];

        hashInit(pageCount);

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

        hashFree();

        fclose(file);
    }

    Proxy operator[](long index)
    {
        return Proxy(*this, index);
    }

    void stats()
    {
        std::cout << "Page faults: " << pageFaults << "\n";
        std::cout << "Page hits: " << pageHits << "\n";
    }
};

#endif //P1_CE2103_PAGEDARRAYS_MAIN_H