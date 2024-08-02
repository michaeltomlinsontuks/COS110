#include <iostream>
#include <string>
#include <fstream>

#include "Function.h"
#include "Vector.h"
#include "Particle.h"
#include "PSO.h"
#include "SwarmGenerator.h"

using namespace std;

void studentExample(){
    SwarmGenerationProperties sgp;
    defaultSettings(sgp);
    toFile("studentExample.txt", generateSwarm(sgp, 110));
    PSO* pso1 = new PSO("studentExample.txt");
    pso1->setMaxV(10);
    cout << "Population" << endl;
    for(int i=0; i < 10; i++){
        cout << "Particle " << i << ": "<< pso1->getParticle(i)->toString() << endl;
    }
    cout << "Manual Loop" << endl;
    for(int i=0; i < 20; i++){
        cout << "Generation " << i << endl;
        Particle best = pso1->run(Function());
        for(int j=0; j < 10; j++){
            cout << "\tParticle " << j << ": " << pso1->getParticles()[j]->toString() << endl;
        }
        cout << "Best particle: " << best.toString() << endl;
        cout << endl;
    }
    delete pso1;
    pso1 = new PSO("studentExample.txt");
    pso1->setMaxV(10);
    Particle** results = pso1->run(20, Function());
    for(int i=0; i < 20; i++){
        cout << "Generation " << i << " best particle: " << results[i]->toString() << endl;
        delete results[i];
    }
    delete [] results;
    delete pso1;
}

int main(int argc, char const *argv[])
{
    studentExample();
}
