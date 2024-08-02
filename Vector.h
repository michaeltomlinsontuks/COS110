#ifndef VECTOR_H
#define VECTOR_H

#include <sstream>
#include <string>
#include <iostream>

class Vector{
    private:
        double* array;
        int size;

    public:
        Vector(std::string array);
        Vector(const Vector& other);
        Vector(const double* array, int size);
        ~Vector();
        double* getArray() const;
        int getSize() const;
        static double fromStringToDouble(std::string v);
        static std::string fromDoubleToString(double v);
        const std::string toString() const;
        double get(int index) const;
        bool equal(const Vector& other) const;
};

#endif /*VECTOR_H*/