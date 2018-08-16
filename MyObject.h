//
// Created by Eric on 2/3/2018.
//

#ifndef PROGRAM_2_MYOBJECT_H
#define PROGRAM_2_MYOBJECT_H

#include "Pool.h"
#include <string>
#include <iostream>


    class MyObject {
    private:
        int id;
        std::string name;
        static Pool* memory;

        MyObject(int i, const std::string &n) : id(i), name(n) {}

        static void *operator new(size_t sz);

    public:
        MyObject(const MyObject &a) = delete;


        static MyObject *create(int i, const std::string &n);

        static void profile();

        static void operator delete(void *loc);

        MyObject operator=(const MyObject &a) = delete;

        friend std::ostream &operator<<(std::ostream &out, const MyObject &a) {
            out << "Name: " << a.name << " ID: " << a.id << std::endl;
            return out;
        }
    };



#endif //PROGRAM_2_MYOBJECT_H
