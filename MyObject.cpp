//
// Created by Eric on 2/3/2018.
//

#include "MyObject.h"


    Pool* MyObject::memory = new Pool(sizeof(MyObject));
    void *MyObject::operator new(size_t sz) { return memory->allocate(); }


    MyObject *MyObject::create(int i, const std::string &n) {
        return new MyObject(i, n);
    }

    void MyObject::profile() { memory->profile(); }

    void MyObject::operator delete(void *loc) { memory->deallocate(loc); }
