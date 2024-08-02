#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>

#include "Function.h"
#include "Vector.h"
#include "SwarmGenerator.h"

class Particle
{
private:
    Vector *position;
    Vector *velocity;
    Vector *pBest;
    double w;
    double c1;
    double c2;
    double vMax;

public:
    //|[attr1,...,attrN]|[v1,...,vN]|w|c1|c2|
    Particle(std::string line);
    Particle(const Particle &other);
    ~Particle();
    void updateParticle(const Particle &gBest);
    const Vector& getPosition() const;
    const Vector& getVelocity() const;
    const Vector *getPBest() const;
    void setVMax(double vMax);
    double evaluate(const Function& function);
    bool equal(const Particle& other) const;
    const std::string toString() const
    {
        std::string result = "P: " + (position != NULL ? position->toString() : "NULL") + "\tV: " + (velocity != NULL ? velocity->toString() : "NULL");
        return result;
    }
    double getW() const;
    double getC1() const;
    double getC2() const;
    double getVMax() const;
};

#endif /*PARTICLE_H*/