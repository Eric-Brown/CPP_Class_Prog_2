//
// Created by Eric on 2/3/2018.
//

#include "Pool.h"
#include <iostream>
#include <cassert>

    const size_t Pool::DEFAULT_BLOCK_SIZE = 5;
    Pool::Pool(size_t elemSize, size_t blockSize)
            :elem_Size(elemSize), block_Size(blockSize), pool(nullptr), free(nullptr)
    {
        std::cout << "Initializing a pool with element size " << elemSize << " and block size " << blockSize << std::endl;
    }
    void Pool::resize()
    {
        std::cout << "Expanding pool..." << std::endl;
        unsigned char **temp  = new unsigned char*[num_Blocks + 1];
        for(size_t i = 0; i < num_Blocks; i++)
            temp[i] = pool[i];
        pool = temp;
        pool[num_Blocks] = new unsigned char[elem_Size * block_Size]; //allocating raw bytes for cells
        std::cout << "Linking cells starting at " << reinterpret_cast<void*>(pool[num_Blocks - 1]) << std::endl;
        for (size_t i = 0; i < block_Size - 1; ++i)//until the last cell, the front of the raw data + cells = next cell
        {
            new(pool[num_Blocks] + (i * elem_Size)) void *(pool[num_Blocks] + (i + 1) * elem_Size);
        }
        new(pool[num_Blocks] + (block_Size - 1) * elem_Size) void*(nullptr); //place a nullptr at the end
        free = reinterpret_cast<void*>(pool[num_Blocks]);
        freeCells += block_Size;
        ++num_Blocks;
    }
    void* Pool::allocate()
    {
        if(free == nullptr)
            resize();
        assert(free != nullptr);
        assert(freeCells > 0);
        --freeCells;
        void* toReturn = free;
        free = *reinterpret_cast<void**>(free);
        assert(free != toReturn);
        std::cout << "Cell allocated at " << toReturn << std::endl;
        return toReturn;
    }
    void Pool::deallocate(void *loc)
    {
        ++freeCells;
        std::cout << "Cell deallocated at " << loc << std::endl;
        new(loc) void*(free);
        void* debug = free;
        free = loc;
        assert(*reinterpret_cast<void**>(free) == debug);
    }
    Pool::~Pool()
    {
        std::cout << "Deleting " << num_Blocks << " blocks" << std::endl;
        for(size_t i = 0; i < num_Blocks; i++)
        {
            delete [] pool[i];
        }
        delete [] pool;
    }
    void Pool::profile()
    {
        size_t live = num_Blocks * block_Size - freeCells;
        std::cout << "Live Cells: " << live << ", Free Cells: " << freeCells << std::endl;
        std::cout << "Free list:" << std::endl;
        void* iterator = free;
        while (iterator)
        {
            std::cout << iterator << std::endl;
            iterator = *reinterpret_cast<void**>(iterator);
        }
    }

