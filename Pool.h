//
// Created by Eric on 2/3/2018.
//

#ifndef PROGRAM_2_POOL_H
#define PROGRAM_2_POOL_H

#include <cstddef>

    class Pool {
    private:
        size_t num_Blocks{};
        size_t block_Size;
        size_t elem_Size;
        size_t freeCells{};
        unsigned char** pool;
        void* free;
        static const size_t DEFAULT_BLOCK_SIZE;
        void resize();
    public:
        Pool(const Pool& a) = delete;
        Pool(size_t elemSize, size_t blockSize = DEFAULT_BLOCK_SIZE);
        ~Pool();
        void* allocate();
        void deallocate(void* loc);
        Pool operator=(const Pool& a) = delete;
        void profile();
    };

#endif //PROGRAM_2_POOL_H
